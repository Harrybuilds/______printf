#include "main.h"

/**
 * get_size - Checks the size to cast the argument
 *
 * @format: formatted string in which to print the arguments
 * @i: list of all arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
	int c_i = *i + 1;
	int size = 0;

	if (format[c_i] == 'l')
		size = S_LONG;
	else if (format[c_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = c_i - 1;
	else
		*i = c_i;

	return (size);
}
