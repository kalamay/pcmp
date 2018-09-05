#ifndef PCMP_LEQ_H
#define PCMP_LEQ_H

#include "common.h"

/**
 * Compares the equality of a mixed case string to a lower case string.
 *
 * @name   pcmp_leq
 * @param  s1  mixed case string to compare
 * @param  s2  lower case string
 * @param  n   length of strings
 * @return  1 if the strings are equal, 0 otherwise
 */
#if PCMP_LEQ_AVX2
# define pcmp_leq pcmp_leq_avx2
#elif PCMP_LEQ_SSE42
# define pcmp_leq pcmp_leq_sse42
#elif PCMP_LEQ_X86
# define pcmp_leq pcmp_leq_x86
#endif
#if !defined(pcmp_leq)
# if PCMP_AVX2
#  define PCMP_LEQ_AVX2 1
#  define pcmp_leq pcmp_leq_avx2
# elif PCMP_SSE42
#  define PCMP_LEQ_SSE42 1
#  define pcmp_leq pcmp_leq_sse42
# else
#  define PCMP_LEQ_X86 1
#  define pcmp_leq pcmp_leq_x86
# endif
#endif

#define PCMP_LEQ_BYTE(b1, b2) \
	(b1 == b2 || b1 + ('a'-'A') == b2)

#if PCMP_LEQ_AVX2

static inline int
pcmp_leq_avx2 (const uint8_t *s1, const uint8_t *s2, int n)
{
	__m256i min = _mm256_set1_epi8 ('A'-1);
	__m256i max = _mm256_set1_epi8 ('Z');
	__m256i zer = _mm256_set1_epi8 (0);
	__m256i add = _mm256_set1_epi8 ('a'-'A');
	__m256i mask[4]; /* case-conversion mask */
	__m256i mix[4]; /* mixed case input which gets converted to lower case */
	__m256i low[4]; /* lower case input */
	uint32_t r[4]; /* comparison results */

# define PIPELINE(i, res) \
	/* load mixed case string */ \
	mix[i] = _mm256_loadu_si256 ((const __m256i *)(s1+32*i)); \
	/* find all bytes >= 'A' (use register temporarily) */ \
	low[i] = _mm256_cmpgt_epi8 (mix[i], min); \
	/* find all bytes <= 'Z' (use register temporarily) */ \
	mask[i] = _mm256_cmpgt_epi8 (max, mix[i]);  \
	/* create mask with 255 for upper case characters and 0 for the rest */ \
	mask[i] = _mm256_and_si256 (low[i], mask[i]); \
	/* change mask so each 255 is now 32 */ \
	mask[i] = _mm256_blendv_epi8 (zer, add, mask[i]); \
	/* add mask to string to changes upper case to lower */ \
	mix[i] = _mm256_add_epi8 (mix[i], mask[i]); \
	/* load lower case string */ \
	low[i] = _mm256_loadu_si256 ((const __m256i *)(s2+32*i)); \
	/* compare strings and to create matching mask */ \
	mask[i] = _mm256_cmpeq_epi8 (mix[i], low[i]); \
	/* condense mask bytes into bits and extract as 32-bit integer */ \
	res[i] = (uint32_t)_mm256_movemask_epi8 (mask[i]); \

	PCMP_AVX2_ILP (PIPELINE, 4, r); /* compare 128 bytes at a time */
	PCMP_AVX2_ILP (PIPELINE, 2, r); /* compare 64 bytes at a time */
	PCMP_AVX2_ILP (PIPELINE, 1, r); /* compare 32 bytes at a time */

#undef PIPELINE

	/* compare remaining bytes individually */
	for (; n > 0; n--, s1++, s2++) {
		if (!PCMP_LEQ_BYTE (*s1, *s2)) { return 0; }
	}
	return 1;
}

#endif

#if PCMP_LEQ_SSE42

static inline int
pcmp_leq_sse42 (const uint8_t *s1, const uint8_t *s2, int n)
{
	__m128i rng = _mm_set1_epi32 (0x5a41); /* 'A' and 'Z' little endian */
	__m128i add = _mm_set1_epi8 ('a'-'A');
	__m128i zer = _mm_setzero_si128 ();
	__m128i mask[4]; /* case-conversion mask */
	__m128i mix[4]; /* mixed case input which gets converted to lower case */
	__m128i low[4]; /* lower case input */
	int r[4]; /* comparison results */

#define PIPELINE(i, n, res) \
	/* load mixed case string */ \
	mix[i] = _mm_lddqu_si128 ((const __m128i *)(s1+16*i)); \
	/* load lower case string */ \
	low[i] = _mm_lddqu_si128 ((const __m128i *)(s2+16*i)); \
	/* create mask with 255 for upper case characters and 0 for the rest */ \
	mask[i] = _mm_cmpestrm (rng, 2, mix[i], n, _SIDD_CMP_RANGES|_SIDD_UNIT_MASK); \
	/* change mask so each 255 is now 32 */ \
	mask[i] = _mm_blendv_epi8 (zer, add, mask[i]); \
	/* add mask to string to changes upper case to lower */ \
	mix[i] = _mm_add_epi8 (mix[i], mask[i]); \
	/* compare strings and find the last matched index */ \
	res[i] = _mm_cmpestri (mix[i], n, low[i], n, \
			_SIDD_CMP_EQUAL_EACH|_SIDD_MASKED_NEGATIVE_POLARITY); \

	PCMP_SSE42_ILP (PIPELINE, 4, r); /* compare 64 bytes at a time */
	PCMP_SSE42_ILP (PIPELINE, 2, r); /* compare 32 bytes at a time */
	PCMP_SSE42_ILP (PIPELINE, 1, r); /* compare 16 bytes at a time */

#undef PIPELINE

	/* compare remaining bytes individually */
	for (; n > 0; n--, s1++, s2++) {
		if (!PCMP_LEQ_BYTE (*s1, *s2)) { return 0; }
	}
	return 1;
}

#endif

#if PCMP_LEQ_X86

static inline int
pcmp_leq_x86 (const uint8_t *s1, const uint8_t *s2, int n)
{
	// compare 8 bytes at a time using 64-bit integers
	for (; n >= 8; n -= 8, s1 += 8, s2 += 8) {
		if (*(uint64_t *)s1 != *(uint64_t *)s2 && (
				!PCMP_LEQ_BYTE (s1[0], s2[0]) ||
				!PCMP_LEQ_BYTE (s1[1], s2[1]) ||
				!PCMP_LEQ_BYTE (s1[2], s2[2]) ||
				!PCMP_LEQ_BYTE (s1[3], s2[3]) ||
				!PCMP_LEQ_BYTE (s1[4], s2[4]) ||
				!PCMP_LEQ_BYTE (s1[5], s2[5]) ||
				!PCMP_LEQ_BYTE (s1[6], s2[6]) ||
				!PCMP_LEQ_BYTE (s1[7], s2[7]))) {
			return 0;
		}
	}
	// compare remaining bytes individually
	for (; n > 0; n--, s1++, s2++) { if (!PCMP_LEQ_BYTE (*s1, *s2)) { return 0; } }
	return 1;
}

#endif

#endif
