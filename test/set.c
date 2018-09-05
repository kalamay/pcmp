#include "mu/mu.h"
#include "../set.h"
#include "../set16.h"

int
main (void)
{
	mu_init ("set");

	const uint8_t sATZ[] = { 'A', 'T', 'Z' };
	const uint8_t s059[] = { '0', '5', '9' };

	const uint8_t sfull[] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z'
	};

	const uint8_t s1[] = "this is a Test Value";
	const uint8_t s2[] = "this is a longer string Test Value";

	mu_assert_str_eq ("Test Value", pcmp_set (s1, sizeof s1 - 1, sATZ, sizeof sATZ));
	mu_assert_str_eq ("Test Value", pcmp_set16 (s1, sizeof s1 - 1, sATZ, sizeof sATZ));
	mu_assert_str_eq ("Test Value", pcmp_set (s2, sizeof s2 - 1, sATZ, sizeof sATZ));
	mu_assert_str_eq ("Test Value", pcmp_set16 (s2, sizeof s2 - 1, sATZ, sizeof sATZ));
	mu_assert_str_eq ("Test Value", pcmp_set (s1, sizeof s1 - 1, sfull, sizeof sfull));
	mu_assert_str_eq ("Test Value", pcmp_set (s2, sizeof s2 - 1, sfull, sizeof sfull));
	mu_assert_ptr_eq (NULL, pcmp_set (s1, sizeof s1 - 1, s059, sizeof s059));
	mu_assert_ptr_eq (NULL, pcmp_set16 (s1, sizeof s1 - 1, s059, sizeof s059));
	mu_assert_ptr_eq (NULL, pcmp_set (s2, sizeof s2 - 1, s059, sizeof s059));
	mu_assert_ptr_eq (NULL, pcmp_set16 (s2, sizeof s2 - 1, s059, sizeof s059));
	mu_assert_ptr_eq (NULL, pcmp_set (s1, 0, sATZ, sizeof sATZ));
	mu_assert_ptr_eq (NULL, pcmp_set16 (s1, 0, sATZ, sizeof sATZ));
	mu_assert_ptr_eq (NULL, pcmp_set (s1, 0, sfull, sizeof sfull));
	
	mu_exit ();
}

