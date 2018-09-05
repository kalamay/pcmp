#include "mu/mu.h"
#include "../eq.h"

#include "load_all.h"
#include "assert_all.h"

int
main (void)
{
	mu_init ("eq");

	load_all ();
	assert_all ();

	mu_assert_int_eq (1, pcmp_eq (short_str, short_str, short_str_len));
	mu_assert_int_eq (1, pcmp_eq (short_str+1, short_str+1, short_str_len-1));
	mu_assert_int_eq (0, pcmp_eq (short_str, short_upper0, short_str_len));
	mu_assert_int_eq (1, pcmp_eq (short_str+1, short_upper0+1, short_str_len-1));
	mu_assert_int_eq (1, pcmp_eq (med_str, med_str, med_str_len));
	mu_assert_int_eq (1, pcmp_eq (med_str+1, med_str+1, med_str_len-1));
	mu_assert_int_eq (0, pcmp_eq (med_str, med_upper35, med_str_len));
	mu_assert_int_eq (0, pcmp_eq (med_str+1, med_upper35+1, med_str_len-1));

	mu_assert_int_eq (1, pcmp_eq (lorem, lorem, lorem_len));
	mu_assert_int_eq (1, pcmp_eq (lorem+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_lower, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_lower+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_bang, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_bang+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper15, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper15+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper16, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper16+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper31, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper31+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper32, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper32+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper47, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper47+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper48, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper48+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper64, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_upper64+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff15, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff15+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff16, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff16+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff31, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff31+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff32, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff32+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff47, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff47+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff48, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff48+1, lorem+1, lorem_len-1));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff64, lorem, lorem_len));
	mu_assert_int_eq (0, pcmp_eq (lorem_diff64+1, lorem+1, lorem_len-1));

	unload_all ();

	mu_exit ();
}

