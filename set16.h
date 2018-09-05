#ifndef PCMP_SET16_H
#define PCMP_SET16_H

#include "common.h"

# ifdef __SSE4_2__

/**
 * Finds the index of the first character matching any character in the set string.
 *
 * @param  cmp   string to search
 * @param  clen  length of search string
 * @param  set   set string limited to 16 characters
 * @param  slen  length of set string
 * @return  pointer to match or NULL
 */
static inline const uint8_t *
pcmp_set16 (const uint8_t *cmp, int clen,
            const uint8_t *set, int slen)
{
	/* load set */
	const __m128i s1 = _mm_lddqu_si128 ((const __m128i *)set);

	do {
		/* load string */
		const __m128i s2 = _mm_lddqu_si128 ((const __m128i *)cmp);

		/* compare strings and find the first matched index */
		int c = _mm_cmpestri (s1, slen, s2, clen, _SIDD_CMP_EQUAL_ANY);

		/* return the offset if an index was found */
		if (pcmp_unlikely (c != 16)) {
			return cmp + c;
		}

		/* update positions */
		cmp += 16;
		clen -= 16;
	} while (clen > 0);

	return NULL;
}

# else

#include "set.h"

#define pcmp_set16 pcmp_set

# endif

#endif

