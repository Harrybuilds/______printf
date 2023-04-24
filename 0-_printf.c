#include "main.h"

/**
 * _printf - function that emulates printf function in c
 * @format: format pointer.
 * Return: prints characters to the standard output.
 */
int _printf(const char *format, ...)
{
	int i = 0, output_len = 0;
	int flags, width, precision, size, buff_ind = 0, printed = 0;
	va_list arguments;
	char buffer[BUFF_SIZE];

	if (format == 0)
		return (-1);
	va_start(arguments, format);

	while (format && format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buffer(buffer, &buff_ind);
			/* write(1, &format[i], 1);*/
			output_len++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buffer,
					       flags, width, precision, size);
			if (printed == -1)
				return (-1);
			output_len += printed;
		}
		i++;
	}
	print_buffer(buffer, &buff_ind);
	va_end(arguments);
	return (output_len);
}

/**
 * print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffer_ind: Index at which to add next char, represents the length.
 */
void print_buffer(char buffer[], int *buffer_ind)
{
	if (*buffer_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buffer_ind = 0;
}
