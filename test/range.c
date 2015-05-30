#include "mu/mu.h"
#include "../range.h"

int
main (void)
{
	// efficient range for upper case and numbers
	const uint8_t rA_Z[] = { 'A', 'Z' };
	const uint8_t r0_9[] = { '0', '9' };

	// this is a dumb way to represent A-Z
	const uint8_t rfull[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z'
	};

	const uint8_t s1[] = "this is a Test Value";
	const uint8_t s2[] = "this is a longer string Test Value";

	mu_assert_str_eq ("Test Value", pcmp_range (s1, sizeof s1 - 1, rA_Z, sizeof rA_Z));
	mu_assert_str_eq ("Test Value", pcmp_range (s2, sizeof s2 - 1, rA_Z, sizeof rA_Z));
	mu_assert_str_eq ("Test Value", pcmp_range (s1, sizeof s1 - 1, rfull, sizeof rfull));
	mu_assert_str_eq ("Test Value", pcmp_range (s2, sizeof s2 - 1, rfull, sizeof rfull));
	mu_assert_ptr_eq (NULL, pcmp_range (s1, sizeof s1 - 1, r0_9, sizeof r0_9));
	mu_assert_ptr_eq (NULL, pcmp_range (s2, sizeof s2 - 1, r0_9, sizeof r0_9));
	mu_assert_ptr_eq (NULL, pcmp_range (s1, 0, rA_Z, sizeof rA_Z));
	mu_assert_ptr_eq (NULL, pcmp_range (s1, 0, rfull, sizeof rfull));
	
	mu_exit ("range");
}

