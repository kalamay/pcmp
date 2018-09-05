#ifndef PCMP_SET_H
#define PCMP_SET_H

#include "common.h"

# ifdef __SSE4_2__

#include "set16.h"

/**
 * Finds the the first character matching any character in the set string.
 *
 * @param  cmp   string to search
 * @param  clen  length of search string
 * @param  set   set string
 * @param  slen  length of set string
 * @return  pointer to match or NULL
 */
static inline const uint8_t *
pcmp_set (const uint8_t *cmp, int clen,
          const uint8_t *set, int slen)
{
	if (slen <= 16) {
		return pcmp_set16 (cmp, clen, set, slen);
	}

	do {
		/* load string */
		const __m128i s2 = _mm_lddqu_si128 ((const __m128i *)cmp);

		/* mark set values */
		const uint8_t *setp = set;
		int splen = slen;

		do {
			/* load set */
			const __m128i s1 = _mm_lddqu_si128 ((const __m128i *)setp);

			/* compare strings and find the first matched index */
			int c = _mm_cmpestri (s1, splen, s2, clen, _SIDD_CMP_EQUAL_ANY);

			/* return the offset if an index was found */
			if (pcmp_unlikely (c != 16)) {
				return cmp + c;
			}

			setp += 16;
			splen -= 16;
		} while (splen > 0);

		/* update positions */
		cmp += 16;
		clen -= 16;
	} while (clen > 0);

	return NULL;
}

# else

#include <stddef.h>

static inline const uint8_t *
pcmp_set (const uint8_t *cmp, int clen,
          const uint8_t *set, int slen)
{
	for (int i = 0; i < clen; i++, cmp++) {
		for (int s = 0; s < slen; s++) {
			if (*cmp == set[s]) {
				return cmp;
			}
		}
	}
	return NULL;
}

# endif

#endif

