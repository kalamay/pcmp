#ifndef PCMP_RANGE_H
#define PCMP_RANGE_H

#include "common.h"

# ifdef __SSE4_2__

#include "range16.h"

/**
 * Finds the the first character matching the range string.
 *
 * The range string is a sequence of character pairs where the range
 * is a value inclusively between the pair of characters.
 *
 * @param  cmp   string to search
 * @param  clen  length of search string
 * @param  rng   range string
 * @param  rlen  length of range string
 * @return  pointer to match or NULL
 */
static inline const uint8_t *
pcmp_range (const uint8_t *cmp, int clen,
            const uint8_t *rng, int rlen)
{
	if (rlen <= 16) {
		return pcmp_range16 (cmp, clen, rng, rlen);
	}

	do {
		/* load string */
		const __m128i s2 = _mm_lddqu_si128 ((const __m128i *)cmp);

		/* mark range values */
		const uint8_t *rngp = rng;
		int rplen = rlen;

		do {
			/* load range */
			const __m128i s1 = _mm_lddqu_si128 ((const __m128i *)rngp);

			/* compare strings and find the first matched index */
			int c = _mm_cmpestri (s1, rplen, s2, clen, _SIDD_CMP_RANGES);

			/* return the offset if an index was found */
			if (pcmp_unlikely (c != 16)) {
				return cmp + c;
			}

			rngp += 16;
			rplen -= 16;
		} while (rplen > 0);

		/* update positions */
		cmp += 16;
		clen -= 16;
	} while (clen > 0);

	return NULL;
}

# else

#include <stddef.h>

static inline const uint8_t *
pcmp_range (const uint8_t *cmp, int clen,
            const uint8_t *rng, int rlen)
{
	for (int i = 0; i < clen; i++, cmp++) {
		for (int r = 0; r < rlen; r += 2) {
			if (*cmp >= rng[r] && *cmp <= rng[r+1]) {
				return cmp;
			}
		}
	}
	return NULL;
}

# endif

#endif

