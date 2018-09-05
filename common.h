/*
 * common.h
 * https://github.com/kalamay/pcmp
 *
 * Copyright (c) 2017, Jeremy Larkin
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
#ifndef PCMP_COMMON_H
#define PCMP_COMMON_H

#define pcmp_likely(x) __builtin_expect(!!(x), 1)
#define pcmp_unlikely(x) __builtin_expect(!!(x), 0)

#if !defined(PCMP_AVX2) && defined(__AVX2__)
# define PCMP_AVX2 1
#endif
#if !defined(PCMP_SSE42) && defined(__SSE4_2__)
# define PCMP_SSE42 1
#endif

#include <stdint.h>

#ifdef __AVX2__
# include <immintrin.h>

# define PCMP_AVX2_ILP(pipeline, sz, res) \
	for (; n >= 32*sz; n -= 32*sz, s1 += 32*sz, s2 += 32*sz) { \
		for (int i = 0; i < sz; i++) { pipeline (i, res); } \
		for (int i = 0; i < sz; i++) { \
			if (res[i] != UINT32_MAX) { return 0; } \
		} \
	}
#endif

#ifdef __SSE4_2__
# include <nmmintrin.h>

# define PCMP_SSE42_ILP(pipeline, sz, res) \
	for (; n >= 16*sz; n -= 16*sz, s1 += 16*sz, s2 += 16*sz) { \
		for (int i = 0; i < sz; i++) { pipeline (i, 16, res); } \
		for (int i = 0; i < sz; i++) { \
			if (res[i] != 16) { return 0; } \
		} \
	}
#endif

#endif
