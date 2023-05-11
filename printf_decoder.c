
#include "printf_decoder.h"

#include <string.h>
#include <stdio.h>

#define skip_copy(a,b) (*a++ = *b++)
#define skip_ncopy(a, b, n) (a = (char*)memcpy(a, b, (n)) + (n))

static int clean_length_format(char* fmt_end)
{
	int len = 4;
	if (*(fmt_end-1) == 'h') {
		len = 2;
		if (*(fmt_end-2) == 'h') {
			len = 1;
		}
	}
	else {
		// deferred printf may not adhere to other length qualifiers but printf sure does
		// since we get to dictate the "out of contract" behaviour I say the easiest
		// route is to just remove any immediate length characters from the format string
		// and let the printf proceed
		do {
			switch(*(fmt_end-1)) {
				case 'l':
				case 'h':
				case 'L':
				case 'z':
				case 'j':
				case 't':
					len = -1;
					*(fmt_end-1) = *fmt_end;
					*fmt_end-- = '\0';
			}
		}
		while (len < 0);
		len = 4;
	}

	return len;
}

int printf_df_decode(char* dst, const char* data, int len)
{
	int size_add, val_len;

	int val;
	unsigned int uval;

	char fmt[32];	// print format buffer - currently set to 32 bytes for simplicity
					// could be a vector for error, but until then .......

	char* fmt_str = fmt;
	char* str = dst;

	const char* data_start = data;

    while (((data-data_start) < len)) {
		if (*data != 0xA5) {
			skip_copy(str, data);
			continue;
		}
		
		fmt_str = fmt;
		*fmt_str++ = *data++ - 128;

		while (((fmt_str-fmt) < sizeof(fmt))) {
			char c = *data;
			skip_copy(fmt_str, data);

			switch (c) {
			case 'c':
				*fmt_str = '\0';
				if ((size_add = sprintf(str, fmt, *data++)) > 0) {
					str += size_add;
				}
				break;
			case 's':
				*fmt_str = '\0';
				const char* s = data;
				val_len = strlen(s);	// @todo should definitely use a safe version
				if ((size_add = sprintf(str, fmt, s)) > 0) {
					str += size_add;
				}
				data += val_len+1;
				break;
			case 'e':
			case 'E':
			case 'f':
			case 'F':
			case 'g':
			case 'G':
				*fmt_str = '\0';
				float fval = *(float*)data;
				if ((size_add = sprintf(str, fmt, fval)) > 0) {
					str += size_add;
				}
				data += 4;
				break;
			case 'd':
			case 'i':
				*fmt_str = '\0';
				val_len = clean_length_format(fmt_str-1);
				
				val = 0;
				if (val_len == 1) {
					val = (int)*(signed char*)data;
				}
				else if (val_len == 2) {
					val = (int)*(signed short*)data;
				}
				else {
					val = *(int*)data;
				}

				if ((size_add = sprintf(str, fmt, val)) > 0) {
					str += size_add;
				}
				data += val_len;
				break;
			case 'o':
			case 'x':
			case 'X':
			case 'u':
				*fmt_str = '\0';
				val_len = clean_length_format(fmt_str-1);

				if (val_len == 1) {
					uval = (unsigned int)*(unsigned char*)data;
				}
				else if (val_len == 2) {
					uval = (unsigned int)*(unsigned short*)data;
				}
				else {
					uval = *(unsigned int*)data;
				}

				if ((size_add = sprintf(str, fmt, uval)) > 0) {
					str += size_add;
				}
				data += val_len;
				break;
			case (char)0xE4:	// 'd' + 128
			case (char)0xE9:	// 'i' + 128
			case (char)0xEF:	// 'o' + 128
			case (char)0xF8:	// 'x' + 128
			case (char)0xD8:	// 'X' + 128
			case (char)0xF5:	// 'u' + 128
				*fmt_str = '\0';
				*(fmt_str-1) -= 128;

				uval = (unsigned int)*(unsigned char*)data;
				if ((size_add = sprintf(str, fmt, uval)) > 0) {
					str += size_add;
				}
				data += 1;
				break;
			case '%':
				*str++ = '%';
			case '\0':
				break;
			case '*':
				// replace wild card with converted value
				fmt_str += sprintf(--fmt_str, "%d", (int)*data++);	
			default:
				continue;
			}

			break;
		}
	}

	*str = '\0';
	return str-dst;
}