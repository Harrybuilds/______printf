#include "main.h"

/* function to print character */

/**
 * print_char - function to prints a character
 * @size: gets size specifier
 * @width: gets width
 * @precision: gets precision specification
 * @flags: Calculates active flags
 * @buffer: array buffer to handle print
 * @types: list of arguments
 * Return: returns number of characters printed
 */

int print_char(va_list types, char buffer[], int flags,
	       int width,int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/* function to print a string */

/**
 * print_string - Prints a string
 * @buffer: Buffer array to handle print
 * @precision: Precision specification
 * @width: get width
 * @types: List of arguments
 * @size: Size specifier
 * @flags: Calculates active flags
 * Return: Number of characters printed
 */
int print_string(va_list types, char buffer[], int flags, int width,
	int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = " ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/* function to print percent sign */

/**
 * print_percent - Prints a percent sign
 * @flags: Calculates active flags
 * @precision: Precision specification
 * @width: get width.
 * @size: Size specification
 * @buffer: array buffer to handle print
 * @types: list of arguments
 * Return: returns number of characters printed
 */
int print_percent(va_list types, char buffer[], int flags,
		  int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* function to print binary */

/**
 * print-binary - Prints an unsigned number
 * @buffer: Buffer array to handle print
 * @width: get width.
 * @size: Size specifier
 * @types: list of arguments
 * @flags: tracks of active flags
 * @precision: Precision specification
 * Return: returns number of character printed
 */
int print_binary(va_list types, char buffer[], int flags,
		 int width,int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);
	UNUSED(precision);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

/* function to print an integer */

/**
 * print_int - Print integer
 * @width: get width
 * @size: Size specifier
 * @types: list of arguments
 * @precision: Precision specification
 * @flags: tracks number of active flags
 * @buffer: array buffer to handle print
 * Return: returns number of characters printed
 */
int print_int(va_list types, char buffer[], int flags,
	      int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer,
			     flags, width, precision, size));
}
