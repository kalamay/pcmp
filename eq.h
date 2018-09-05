#ifndef PCMP_EQ_H
#define PCMP_EQ_H

#include "common.h"

/**
 * Compares the case-sensitive equality of two strings.
 *
 * @name   pcmp_eq
 * @param  s1  first memory sequence to compare
 * @param  s2  second memory sequence to compare
 * @param  n   length of sequence
 * @return  1 if the values are equal, 0 otherwise
 */
#if PCMP_EQ_AVX2
# define pcmp_eq pcmp_eq_avx2
#elif PCMP_EQ_SSE42
# define pcmp_eq pcmp_eq_sse42
#elif PCMP_EQ_X86
# define pcmp_eq pcmp_eq_x86
#endif
#if !defined(pcmp_eq)
# if PCMP_AVX2
#  define PCMP_EQ_AVX2 1
#  define pcmp_eq pcmp_eq_avx2
# elif PCMP_SSE42
#  define PCMP_EQ_SSE42 1
#  define pcmp_eq pcmp_eq_sse42
# else
#  define PCMP_EQ_X86 1
#  define pcmp_eq pcmp_eq_x86
# endif
#endif

#if PCMP_EQ_AVX2

static inline int
pcmp_eq_avx2 (const uint8_t *s1, const uint8_t *s2, int n)
{
	__m256i m1[4]; /* register for segment of first string */
	__m256i m2[4]; /* register for segment of second string */
	__m256i mask[4]; /* comparison mask */
	uint32_t r[4]; /* comparison results */

#define PIPELINE(i, res) \
	/* load first string */ \
	m1[i] = _mm256_loadu_si256 ((const __m256i *)(s1+32*i)); \
	/* load second string */ \
	m2[i] = _mm256_loadu_si256 ((const __m256i *)(s2+32*i)); \
	/* compare strings and to create matching mask */ \
	mask[i] = _mm256_cmpeq_epi8 (m1[i], m2[i]); \
	/* condense mask bytes into bits and extract as 32-bit integer */ \
	res[i] = (uint32_t)_mm256_movemask_epi8 (mask[i]); \

	PCMP_AVX2_ILP (PIPELINE, 4, r); /* compare 128 bytes at a time */
	PCMP_AVX2_ILP (PIPELINE, 2, r); /* compare 64 bytes at a time */
	PCMP_AVX2_ILP (PIPELINE, 1, r); /* compare 32 bytes at a time */

#undef PIPELINE

	/* compare remaining bytes individually */
	for (; n > 0; n--, s1++, s2++) { if (*s1 != *s2) { return 0; } }
	return 1;
}

#endif

#if PCMP_EQ_SSE42

static inline int
pcmp_eq_sse42 (const uint8_t *s1, const uint8_t *s2, int n)
{
	__m128i m1[4]; /* register for segment of first string */
	__m128i m2[4]; /* register for segment of second string */
	int r[4]; /* comparison results */

#define PIPELINE(i, n, res) \
	/* load first string */ \
	m1[i] = _mm_lddqu_si128 ((const __m128i *)(s1+16*i)); \
	/* load second string */ \
	m2[i] = _mm_lddqu_si128 ((const __m128i *)(s2+16*i)); \
	/* compare strings and find the last matched index */ \
	res[i] = _mm_cmpestri (m1[i], n, m2[i], n, \
			_SIDD_CMP_EQUAL_EACH|_SIDD_MASKED_NEGATIVE_POLARITY); \

	PCMP_SSE42_ILP (PIPELINE, 4, r); /* compare 64 bytes at a time */
	PCMP_SSE42_ILP (PIPELINE, 2, r); /* compare 32 bytes at a time */
	PCMP_SSE42_ILP (PIPELINE, 1, r); /* compare 16 bytes at a time */

#undef PIPELINE

	/* compare remaining bytes individually */
	for (; n > 0; n--, s1++, s2++) { if (*s1 != *s2) { return 0; } }
	return 1;
}

#endif

#if PCMP_EQ_X86

static inline int
pcmp_eq_x86 (const uint8_t *s1, const uint8_t *s2, int n)
{
	// compare 32 bytes at a time using 64-bit integers and SIMD
	for (; n >= 32; n -= 32, s1 += 32, s2 += 32) {
		int r =
			(((uint64_t *)s1)[0] != ((uint64_t *)s2)[0]) +
			(((uint64_t *)s1)[1] != ((uint64_t *)s2)[1]) +
			(((uint64_t *)s1)[2] != ((uint64_t *)s2)[2]) +
			(((uint64_t *)s1)[3] != ((uint64_t *)s2)[3]) ;
		if (r != 0) { return 0; }
	}
	// compare 8 bytes at a time using 64-bit integers
	for (; n >= 8; n -= 8, s1 += 8, s2 += 8) {
		if (*(uint64_t *)s1 != *(uint64_t *)s2) {
			return 0;
		}
	}
	// compare remaining bytes individually
	for (; n > 0; n--, s1++, s2++) { if (*s1 != *s2) { return 0; } }
	return 1;
}

#endif

#endif

