#include "mu.h"
#include "../leq.h"
#include "../leq16.h"

int
main (void)
{
	const uint8_t s1[] = "short";
	const uint8_t s2[] = "Short";
	const uint8_t s3[] = "some longer value with a different word";
	const uint8_t s4[] = "some longer value with a different Word";

	mu_assert_int_eq (1, pcmp_leq (s1, s1, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_leq (s2, s1, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_leq16 (s1, s1, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_leq16 (s2, s1, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_leq (s3, s3, sizeof s3 - 1));
	mu_assert_int_eq (1, pcmp_leq (s4, s3, sizeof s3 - 1));

	mu_exit ("leq");
}

