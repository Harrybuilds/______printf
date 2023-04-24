#ifndef  MAIN_H
#define MAIN_H
#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#define UNUSED(x) (void) (x)
#define BUFF_SIZE 1024

/* sizes */
#define S_LONG 2
#define S_SHORT 1

/* flags */
#define F_PLUS 2
#define F_HASH 8
#define F_MINUS 1
#define F_ZERO 4
#define F_SPACE 16


/**
 * struct fmt - Struct op
 *
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct fmt fmt_t - Struct op
 *
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt fmt_t;


void print_buffer(char buffer[], int *buff_ind);
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i,va_list list,
	    char buffer[], int flags, int width, int precision, int size);




#endif
