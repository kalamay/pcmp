#include "mu/mu.h"
#include "../leq.h"

#include "load_all.h"
#include "assert_all.h"

int
main (void)
{
	mu_init ("leq");

	load_all ();
	assert_all ();

	mu_assert_int_eq (1, pcmp_leq (short_str, short_str, short_str_len));
	mu_assert_int_eq (1, pcmp_leq (short_str+1, short_str+1, short_str_len-1));
	mu_assert_int_eq (1, pcmp_leq (short_upper0, short_str, short_str_len));
	mu_assert_int_eq (1, pcmp_leq (short_upper0+1, short_str+1, short_str_len-1));
	mu_assert_int_eq (1, pcmp_leq (med_str, med_str, med_str_len));
	mu_assert_int_eq (1, pcmp_leq (med_str+1, med_str+1, med_str_len-1));
	mu_assert_int_eq (1, pcmp_leq (med_upper35, med_str, med_str_len));
	mu_assert_int_eq (1, pcmp_leq (med_upper35+1, med_str+1, med_str_len-1));

	mu_assert_int_eq (1, pcmp_leq (lorem_lower, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_lower+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_bang, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_bang+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper15, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper15+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper16, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper16+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper31, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper31+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper32, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper32+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper47, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper47+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper48, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper48+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper64, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (1, pcmp_leq (lorem_upper64+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff15, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff15+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff16, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff16+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff31, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff31+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff32, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff32+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff47, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff47+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff48, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff48+1, lorem_lower+1, lorem_lower_len-1));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff64, lorem_lower, lorem_lower_len));
	mu_assert_int_eq (0, pcmp_leq (lorem_diff64+1, lorem_lower+1, lorem_lower_len-1));

	unload_all ();

	mu_exit ();
}

