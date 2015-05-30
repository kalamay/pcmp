#include "mu/mu.h"
#include "../eq.h"
#include "../eq16.h"

int
main (void)
{
	const uint8_t s1[] = "short";
	const uint8_t s2[] = "Short";
	const uint8_t s3[] = "some longer value with a different word";
	const uint8_t s4[] = "some longer value with a different Word";

	mu_assert_int_eq (1, pcmp_eq (s1, s1, sizeof s1 - 1));
	mu_assert_int_eq (0, pcmp_eq (s1, s2, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_eq16 (s1, s1, sizeof s1 - 1));
	mu_assert_int_eq (0, pcmp_eq16 (s1, s2, sizeof s1 - 1));
	mu_assert_int_eq (1, pcmp_eq (s3, s3, sizeof s3 - 1));
	mu_assert_int_eq (0, pcmp_eq (s3, s4, sizeof s3 - 1));

	mu_exit ("eq");
}

