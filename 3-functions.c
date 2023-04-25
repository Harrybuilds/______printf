#include "main.h"

/* function to print non printable */

/**
 * print_non_printable - Prints ascii codes in hexa of non printable characters
 * @buffer: Buffer array to handle print
 * @width: get width
 * @size: Size specifier
 * @types: list of arguments
 * @flags: Calculates active flags
 * @precision: Precision specification
 * Return: Number of characters printed
 */
int print_non_printable(va_list types, char buffer[], int flags, int width,
	int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	UNUSED(flags);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/************************ PRINT A STRING IN ROT13 *************************/

/**
 * print_rot13string - Print a string in rot13.
 * @types: list of arguments
 * @flags: Calculates active flags
 * @precision: Precision specification
 * @buffer: Buffer array to handle print
 * @size: Size specification
 * @width: get width
 * Return: Numbers of characters printed
 */
int print_rot13string(va_list types, char buffer[], int flags, int width,
	int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] =
	"NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(width);
	UNUSED(size);
	UNUSED(flags);
	UNUSED(precision);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);

}

/* function to print pointer */

/**
 * print_pointer - Prints the value of a pointer variable
 * @width: get width
 * @size: Size specifier
 * @precision: Precision specification
 * @flags: Calculates active flags
 * @buffer: Buffer array to handle print
 * @types: list of arguments
 * Return: Number of characters printed.
 */
int print_pointer(va_list types, char buffer[], int flags, int width,
	int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length = 2 for '0x */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(size);
	UNUSED(width);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];

		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))

		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/* return (write(1, &buffer[i], BUFF_SIZE - i - 1)); */
	return (write_pointer(buffer, ind, length, width, flags,
	padd, extra_c, padd_start));
}

/* function to print reverse */

/**
 * print_reverse - Prints reverse string.
 * @buffer: Buffer array to handle print
 * @precision: Precision specification
 * @size: size specifier
 * @types: list of arguments
 * @width: get width
 * @flags: calculates active flags
 * Return: returns numbers of characters printed
 */
int print_reverse(va_list types, char buffer[], int flags, int width,
	int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(size);
	UNUSED(width);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")NULL(";
	}
	for (i =  0; str[i]; i++)
		;
	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
