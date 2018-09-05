#include "load_input.h"

#include <ctype.h>

static const uint8_t *short_str;
static const uint8_t *short_upper0;
static const uint8_t *med_str;
static const uint8_t *med_upper35;
static const uint8_t *lorem;
static const uint8_t *lorem2;
static const uint8_t *lorem_lower;
static const uint8_t *lorem_lower2;
static const uint8_t *lorem_bang;
static const uint8_t *lorem_upper15;
static const uint8_t *lorem_upper16;
static const uint8_t *lorem_upper31;
static const uint8_t *lorem_upper32;
static const uint8_t *lorem_upper47;
static const uint8_t *lorem_upper48;
static const uint8_t *lorem_upper64;
static const uint8_t *lorem_diff15;
static const uint8_t *lorem_diff16;
static const uint8_t *lorem_diff31;
static const uint8_t *lorem_diff32;
static const uint8_t *lorem_diff47;
static const uint8_t *lorem_diff48;
static const uint8_t *lorem_diff64;

static size_t short_str_len;
static size_t short_upper1_len;
static size_t med_str_len;
static size_t med_upper35_len;
static size_t lorem_len;
static size_t lorem2_len;
static size_t lorem_lower_len;
static size_t lorem_lower2_len;
static size_t lorem_bang_len;
static size_t lorem_upper15_len;
static size_t lorem_upper16_len;
static size_t lorem_upper31_len;
static size_t lorem_upper32_len;
static size_t lorem_upper47_len;
static size_t lorem_upper48_len;
static size_t lorem_upper64_len;
static size_t lorem_diff15_len;
static size_t lorem_diff16_len;
static size_t lorem_diff31_len;
static size_t lorem_diff32_len;
static size_t lorem_diff47_len;
static size_t lorem_diff48_len;
static size_t lorem_diff64_len;

static void
load_all (void)
{
	short_str = load_input ("short_str.txt", &short_str_len);
	short_upper0 = load_input ("short_upper0.txt", &short_upper1_len);
	med_str = load_input ("med_str.txt", &med_str_len);
	med_upper35 = load_input ("med_upper35.txt", &med_upper35_len);
	lorem = load_input ("lorem.txt", &lorem_len);
	lorem2 = load_input ("lorem.txt", &lorem2_len);
	lorem_lower = load_input ("lorem_lower.txt", &lorem_lower_len);
	lorem_lower2 = load_input ("lorem_lower.txt", &lorem_lower2_len);
	lorem_bang = load_input ("lorem_bang.txt", &lorem_bang_len);
	lorem_upper15 = load_input ("lorem_upper15.txt", &lorem_upper15_len);
	lorem_upper16 = load_input ("lorem_upper16.txt", &lorem_upper16_len);
	lorem_upper31 = load_input ("lorem_upper31.txt", &lorem_upper31_len);
	lorem_upper32 = load_input ("lorem_upper32.txt", &lorem_upper32_len);
	lorem_upper47 = load_input ("lorem_upper47.txt", &lorem_upper47_len);
	lorem_upper48 = load_input ("lorem_upper48.txt", &lorem_upper48_len);
	lorem_upper64 = load_input ("lorem_upper64.txt", &lorem_upper64_len);
	lorem_diff15 = load_input ("lorem_diff15.txt", &lorem_diff15_len);
	lorem_diff16 = load_input ("lorem_diff16.txt", &lorem_diff16_len);
	lorem_diff31 = load_input ("lorem_diff31.txt", &lorem_diff31_len);
	lorem_diff32 = load_input ("lorem_diff32.txt", &lorem_diff32_len);
	lorem_diff47 = load_input ("lorem_diff47.txt", &lorem_diff47_len);
	lorem_diff48 = load_input ("lorem_diff48.txt", &lorem_diff48_len);
	lorem_diff64 = load_input ("lorem_diff64.txt", &lorem_diff64_len);
}

static void
unload_all (void)
{
	free ((void *)short_str);
	short_str = NULL;
	free ((void *)short_upper0);
	short_upper0 = NULL;
	free ((void *)med_str);
	med_str = NULL;
	free ((void *)med_upper35);
	med_upper35 = NULL;
	free ((void *)lorem);
	lorem = NULL;
	free ((void *)lorem2);
	lorem2 = NULL;
	free ((void *)lorem_lower);
	lorem_lower = NULL;
	free ((void *)lorem_lower2);
	lorem_lower2 = NULL;
	free ((void *)lorem_bang);
	lorem_bang = NULL;
	free ((void *)lorem_upper15);
	lorem_upper15 = NULL;
	free ((void *)lorem_upper16);
	lorem_upper16 = NULL;
	free ((void *)lorem_upper31);
	lorem_upper31 = NULL;
	free ((void *)lorem_upper32);
	lorem_upper32 = NULL;
	free ((void *)lorem_upper47);
	lorem_upper47 = NULL;
	free ((void *)lorem_upper48);
	lorem_upper48 = NULL;
	free ((void *)lorem_upper64);
	lorem_upper64 = NULL;
	free ((void *)lorem_diff15);
	lorem_diff15 = NULL;
	free ((void *)lorem_diff16);
	lorem_diff16 = NULL;
	free ((void *)lorem_diff31);
	lorem_diff31 = NULL;
	free ((void *)lorem_diff32);
	lorem_diff32 = NULL;
	free ((void *)lorem_diff47);
	lorem_diff47 = NULL;
	free ((void *)lorem_diff48);
	lorem_diff48 = NULL;
	free ((void *)lorem_diff64);
	lorem_diff64 = NULL;

	short_str_len = 0;
	short_upper1_len = 0;
	med_str_len = 0;
	med_upper35_len = 0;
	lorem_len = 0;
	lorem_lower_len = 0;
	lorem_bang_len = 0;
	lorem_upper15_len = 0;
	lorem_upper16_len = 0;
	lorem_upper31_len = 0;
	lorem_upper32_len = 0;
	lorem_upper47_len = 0;
	lorem_upper48_len = 0;
	lorem_upper64_len = 0;
	lorem_diff15_len = 0;
	lorem_diff16_len = 0;
	lorem_diff31_len = 0;
	lorem_diff32_len = 0;
	lorem_diff47_len = 0;
	lorem_diff48_len = 0;
	lorem_diff64_len = 0;
}

