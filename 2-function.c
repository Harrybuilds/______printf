 #include "main.h"

/* print unsigned number */
/**
 * print_unsigned - function to prints an unsigned number
 * @types: list of all arguments
 * @buffer: array buffer to handle print
 * @flags: keeps track of all active flags
 * @width: get width
 * @precision:placeholder for precision specification
 * @size: placeholder for size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
		   int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);
	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	for (; num > 0; j++)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/* prints unsigned number in octal form */
/**
 * print_octal - function to prints an unsigned number in octal notation
 * @types: list of arguments
 * @buffer: array buffer to handle print
 * @flags:  tracks active flags
 * @width: grabs width
 * @precision: gets precision specification
 * @size: gets size specifier
 * Return: returns number of chars printed
 */
int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);
	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';
	buffer[BUFF_SIZE - 1] = '\0';
	for (; num > 0; i++)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
		if (flags & F_HASH && init_num != 0)
			buffer[i--] = '0';
	}
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/* function to print unsigned number in hexadecimal form */
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: list of arguments
 * @buffer: array buffer to handle print
 * @flags: tracks number of active flags
 * @width: placeholder to get width
 * @precision: placeholder to get precision specification
 * @size: gets size specifier
 * Return: returns number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
		      int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
			   flags, 'x', width, precision, size));
}

/* print unsigned number in upper hexadecimal */
/**
 *print_hexa_upper - funct 2 prints an unsigned number in upper hexa notation
 *@types: list of arguments
 * @buffer: array buffer to handle print
 * @flags:  tracks number of active flags
 * @width: get width
 * @precision: precision specification
 * @size: Size specifier
 * Return: returns number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
		     int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
			   flags, 'X', width, precision, size));
}

/* print hexa number in lower or upper */
/**
 * print_hexa - function to prints a hexadecimal number in lower or upper
 * @types: list of arguments
 * @map_to: The array of values to map the number to
 * @buffer: array buffer to handle print
 * @flags:  tracks number of  active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	       int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
		if (flags & F_HASH && init_num != 0)
		{
			buffer[i--] = flag_ch;
			buffer[i--] = '0';
		}
		i++;
	}

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
