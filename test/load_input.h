#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <err.h>

__unused static uint8_t *
load_input (const char *name, size_t *len)
{
	char path[4096] = __FILE__;
	path[sizeof(__FILE__) - sizeof("load_input.h")] = '\0';
	strcat (path, "input/");
	strcat (path, name);

	FILE *f = fopen (path, "r");
	if (f == NULL) { err (1, "%s", path); }
	if (fseek (f, 0, SEEK_END) < 0) { err (1, "%s", path); }
	long size = ftell (f);
	if (size < 0) { err (1, "%s", path); }
	if (fseek (f, 0, SEEK_SET) < 0) { err (1, "%s", path); }

	uint8_t *buf = malloc (size + 1);
	if (fread (buf, size, 1, f) != 1) { err (1, "%s", path); }
	while (isspace (buf[size-1])) {
		size--;
	}
	*len = size;
	buf[size] = '\0';
	return buf;
}

