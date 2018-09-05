static void
assert_all (void)
{
	mu_assert_ptr_ne (short_str, NULL);
	mu_assert_ptr_ne (short_upper0, NULL);
	mu_assert_ptr_ne (med_str, NULL);
	mu_assert_ptr_ne (med_upper35, NULL);
	mu_assert_ptr_ne (lorem, NULL);
	mu_assert_ptr_ne (lorem2, NULL);
	mu_assert_ptr_ne (lorem_lower, NULL);
	mu_assert_ptr_ne (lorem_lower2, NULL);
	mu_assert_ptr_ne (lorem_bang, NULL);
	mu_assert_ptr_ne (lorem_upper15, NULL);
	mu_assert_ptr_ne (lorem_upper16, NULL);
	mu_assert_ptr_ne (lorem_upper31, NULL);
	mu_assert_ptr_ne (lorem_upper32, NULL);
	mu_assert_ptr_ne (lorem_upper47, NULL);
	mu_assert_ptr_ne (lorem_upper48, NULL);
	mu_assert_ptr_ne (lorem_upper64, NULL);
	mu_assert_ptr_ne (lorem_diff15, NULL);
	mu_assert_ptr_ne (lorem_diff16, NULL);
	mu_assert_ptr_ne (lorem_diff31, NULL);
	mu_assert_ptr_ne (lorem_diff32, NULL);
	mu_assert_ptr_ne (lorem_diff47, NULL);
	mu_assert_ptr_ne (lorem_diff48, NULL);
	mu_assert_ptr_ne (lorem_diff64, NULL);

	mu_assert_uint_eq (short_str_len, short_upper1_len);
	mu_assert_uint_eq (med_str_len, med_upper35_len);
	mu_assert_uint_eq (lorem_len, lorem2_len);
	mu_assert_uint_eq (lorem_len, lorem_lower_len);
	mu_assert_uint_eq (lorem_len, lorem_bang_len);
	mu_assert_uint_eq (lorem_len, lorem_upper15_len);
	mu_assert_uint_eq (lorem_len, lorem_upper16_len);
	mu_assert_uint_eq (lorem_len, lorem_upper31_len);
	mu_assert_uint_eq (lorem_len, lorem_upper32_len);
	mu_assert_uint_eq (lorem_len, lorem_upper47_len);
	mu_assert_uint_eq (lorem_len, lorem_upper48_len);
	mu_assert_uint_eq (lorem_len, lorem_upper64_len);
	mu_assert_uint_eq (lorem_len, lorem_diff15_len);
	mu_assert_uint_eq (lorem_len, lorem_diff16_len);
	mu_assert_uint_eq (lorem_len, lorem_diff31_len);
	mu_assert_uint_eq (lorem_len, lorem_diff32_len);
	mu_assert_uint_eq (lorem_len, lorem_diff47_len);
	mu_assert_uint_eq (lorem_len, lorem_diff48_len);
	mu_assert_uint_eq (lorem_len, lorem_diff64_len);

	mu_assert_str_ne (short_str, short_upper0);
	mu_assert_str_ne (med_str, med_upper35);
	mu_assert_str_eq (lorem, lorem2);
	mu_assert_str_ne (lorem, lorem_lower);
	mu_assert_str_ne (lorem, lorem_lower2);
	mu_assert_str_ne (lorem, lorem_bang);
	mu_assert_str_ne (lorem, lorem_upper15);
	mu_assert_str_ne (lorem, lorem_upper16);
	mu_assert_str_ne (lorem, lorem_upper31);
	mu_assert_str_ne (lorem, lorem_upper32);
	mu_assert_str_ne (lorem, lorem_upper47);
	mu_assert_str_ne (lorem, lorem_upper48);
	mu_assert_str_ne (lorem, lorem_upper64);
	mu_assert_str_ne (lorem, lorem_diff15);
	mu_assert_str_ne (lorem, lorem_diff16);
	mu_assert_str_ne (lorem, lorem_diff31);
	mu_assert_str_ne (lorem, lorem_diff32);
	mu_assert_str_ne (lorem, lorem_diff47);
	mu_assert_str_ne (lorem, lorem_diff48);
	mu_assert_str_ne (lorem, lorem_diff64);

	mu_assert_uint_ne (short_str[0], short_upper0[0]);
	mu_assert_uint_ne (med_str[35], med_upper35[35]);
	mu_assert_uint_ne (lorem[15], lorem_upper15[15]);
	mu_assert_uint_ne (lorem[16], lorem_upper16[16]);
	mu_assert_uint_ne (lorem[31], lorem_upper31[31]);
	mu_assert_uint_ne (lorem[32], lorem_upper32[32]);
	mu_assert_uint_ne (lorem[47], lorem_upper47[47]);
	mu_assert_uint_ne (lorem[48], lorem_upper48[48]);
	mu_assert_uint_ne (lorem[64], lorem_upper64[64]);

	mu_assert_uint_eq (lorem[15], tolower (lorem_upper15[15]));
	mu_assert_uint_eq (lorem[16], tolower (lorem_upper16[16]));
	mu_assert_uint_eq (lorem[31], tolower (lorem_upper31[31]));
	mu_assert_uint_eq (lorem[32], tolower (lorem_upper32[32]));
	mu_assert_uint_eq (lorem[47], tolower (lorem_upper47[47]));
	mu_assert_uint_eq (lorem[48], tolower (lorem_upper48[48]));
	mu_assert_uint_eq (lorem[64], tolower (lorem_upper64[64]));

	mu_assert_uint_ne (lorem[15], lorem_diff15[15]);
	mu_assert_uint_ne (lorem[16], lorem_diff16[16]);
	mu_assert_uint_ne (lorem[31], lorem_diff31[31]);
	mu_assert_uint_ne (lorem[32], lorem_diff32[32]);
	mu_assert_uint_ne (lorem[47], lorem_diff47[47]);
	mu_assert_uint_ne (lorem[48], lorem_diff48[48]);
	mu_assert_uint_ne (lorem[64], lorem_diff64[64]);

	mu_assert_uint_ne (lorem[15], tolower (lorem_diff15[15]));
	mu_assert_uint_ne (lorem[16], tolower (lorem_diff16[16]));
	mu_assert_uint_ne (lorem[31], tolower (lorem_diff31[31]));
	mu_assert_uint_ne (lorem[32], tolower (lorem_diff32[32]));
	mu_assert_uint_ne (lorem[47], tolower (lorem_diff47[47]));
	mu_assert_uint_ne (lorem[48], tolower (lorem_diff48[48]));
	mu_assert_uint_ne (lorem[64], tolower (lorem_diff64[64]));
}

