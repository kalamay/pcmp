#ifndef PCMP_RANGE16_H
#define PCMP_RANGE16_H

#include "common.h"

# ifdef __SSE4_2__

/**
 * Finds the index of the first character matching the range string.
 *
 * The range string is a sequence of character pairs where the range
 * is a value inclusively between the pair of characters.
 *
 * @param  cmp   string to search
 * @param  clen  length of search string
 * @param  rng   range string limited to 8 range pairs
 * @param  rlen  length of range string
 * @return  pointer to match or NULL
 */
static inline const uint8_t *
pcmp_range16 (const uint8_t *cmp, int clen,
              const uint8_t *rng, int rlen)
{
	/* load range */
	const __m128i s1 = _mm_lddqu_si128 ((const __m128i *)rng);

	do {
		/* load string */
		const __m128i s2 = _mm_lddqu_si128 ((const __m128i *)cmp);

		/* compare strings and find the first matched index */
		int c = _mm_cmpestri (s1, rlen, s2, clen, _SIDD_CMP_RANGES);

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

#include "range.h"

#define pcmp_range16 pcmp_range

# endif

#endif

