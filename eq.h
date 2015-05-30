/*
 * eq.h
 * pcmp
 *
 * Copyright (c) 2015, Jeremy Larkin
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef PCMP_EQ_H
#define PCMP_EQ_H

#include "common.h"

# ifdef __SSE4_2__

/**
 * Compares the case-sensitive equality of two strings.
 *
 * @param  s1  first memory sequence to compare
 * @param  s2  second memory sequence to compare
 * @param  n   length of sequence
 * @return  1 if the values are equal, 0 otherwise
 */
static inline int
pcmp_eq (const uint8_t *restrict s1, const uint8_t *restrict s2, int n)
{
	int c, result = 0;

	do {
		// load strings
		__m128i m1 = _mm_lddqu_si128 ((const __m128i *)s1);
		__m128i m2 = _mm_lddqu_si128 ((const __m128i *)s2);
		// compare strings and find the last matched index
		c = _mm_cmpestri (m1, n - result, m2, 16, _SIDD_CMP_EQUAL_EACH | _SIDD_MASKED_NEGATIVE_POLARITY);
		// update positions
		s1 += 16;
		s2 += 16;
		result += c;
	} while (c == 16);

	return result == n;
}

# else

static inline int
pcmp_eq (const uint8_t *restrict s1, const uint8_t *restrict s2, int n)
{
	for (; n && *s1 == *s2; n--, s1++, s2++);
	return n == 0;
}

# endif

#endif

