#include "main.h"

/* function to write */
/**
 * handle_write_char - function to prints a string
 * @c: char types.
 * @buffer: array buffer to handle print
 * @flags:  tracks number of active flags.
 * @width: gets width.
 * @precision: gets precision specifier
 * @size: Size specifier
 *
 * Return: returns number of chars printed.
 */
int handle_write_char(char c, char buffer[], int flags,
		      int width, int precision, int size)
{
	/* char is stored at left and paddind at buffer's right */
	char padd = ' ';
	int j = 0;

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
        padd = '0';

	buffer[j++] = c;
	buffer[j] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (; j < width - 1; j++)
			buffer[BUFF_SIZE - j - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
				write(1, &buffer[BUFF_SIZE - j - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - j - 1], width - 1) +
                    write(1, &buffer[0], 1));
    }

    return (write(1, &buffer[0], 1));
}



/* function to write number */
/**
 * write_number - prints a string
 * @is_negative: list of arguments
 * @ind: char data-types.
 * @buffer: array buffer to handle print
 * @flags:  tracks number of active flags
 * @width: gets width.
 * @precision: gets precision specifier
 * @size: size specifier
 *
 * Return: returns number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
		 int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width, precision,
			  length, padd, extra_ch));
}

/**
 * write_num - function to write a number using a bufffer
 * @ind: the index at which the number starts on the buffer
 * @buffer: buffer
 * @flags: flags
 * @width: width
 * @prec: precision specifier
 * @length: number length
 * @padd: pading char
 * @extra_c: extra char
 *
 * Return: returns number of printed chars.
 */
int write_num(int ind, char buffer[], int flags, int width,
	      int prec, int length, char padd, char extra_c)
{
	int k, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0'
	    && width == 0)

		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
        padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (k = 1; k < width - length + 1; k++)
			buffer[k] = padd;
		buffer[k] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) +
				write(1, &buffer[1], k - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], k - 1) +
				write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], k - padd_start) +
				write(1, &buffer[ind], length -
				      (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}


/**
 * write_unsigned - function to write an unsigned number
 * @is_negative: number indicating if the num is negative
 * @ind: index at which the number starts in the buffer
 * @buffer: array of chars
 * @flags: flags specifiers
 * @width: width specifier
 * @precision: gets precision specifier
 * @size: gets size specifier
 *
 * Return: returns number of written chars.
 */
int write_unsigned(int is_negative, int ind,char buffer[],
		 int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position i */

	char padd = ' ';
	int len = BUFF_SIZE - ind -1, j = 0;

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < len)
		padd = ' ';

	while (precision > len)
	{
		buffer[--ind] = '0';
		len++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > len)
	{
		for (j = 0; j < width - len; j++)
			buffer[j] = padd;

		buffer[j] = '\0';

		if (flags & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], len) +
				write(1, &buffer[0], j));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], j) +
				write(1, &buffer[ind], len));
		}
	}

	return (write(1, &buffer[ind], len));
}


/* function to write memory address */
/**
 * write_pointer - writes a memory address
 * @buffer: Arrays of chars
 * @ind: index at which the number starts in the buffer
 * @length: the length of number
 * @width: the width specifier
 * @flags: the flags specifier
 * @padd: char representing the padding
 * @extra_c: char representing extra char
 * @padd_start: index at which padding should start
 *
 * Return: returns number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,int width,
		  int flags, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
        if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
        {
            buffer[--ind] = 'x';
            buffer[--ind] = '0';
            if (extra_c)
		    buffer[--ind] = extra_c;
	    return (write(1, &buffer[ind], length) +
		    write(1, &buffer[3], i - 3));
        }
        else if (!(flags & F_MINUS) && padd == ' ')
/* extra char to left of buffer */
        {
		buffer[--ind] = 'x';
		buffer[--ind] = '0';
		if (extra_c)
			buffer[--ind] = extra_c;
		return (write(1, &buffer[3], i - 3) +
			write(1, &buffer[ind], length));
        }
        else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
        {
		if (extra_c)
			buffer[--padd_start] = extra_c;
		buffer[1] = '0';
		buffer[2] = 'x';
		return (write(1, &buffer[padd_start], i - padd_start) +
			write(1, &buffer[ind], length - (1 - padd_start) - 2));
        }
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
