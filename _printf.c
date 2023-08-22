#include <unistd.h>
#include <stdarg.h>
#include <stddef.h>
#include "main.h"

#define IS_SPECIFIER(c) ((c) == '%' || (c) == 'c' || (c) == 's')

/**
 * _printf - produces output according to a format
 * @format: string contaionig the format.
 *
 * Return: the number of chars printed excluding the null char.
 */

int _printf(const char *format, ...)
{
	va_list ap;
	unsigned int i, len, counter = 0;
	char *next_str;
	size_t next_str_size;

	if (format == NULL)
		return (-1);

	len = _strlen(format);
	va_start(ap, format);

	for (i = 0; i < len; i++)
	{
		if (format[i] == '%')
		{
			switch (format[i + 1])
			{
				case '%':
					counter += _putchar('%');
					i++;
					break;
				case 'c':
					counter += _putchar(va_arg(ap, int));
					i++;
					break;
				case 's':
					next_str = va_arg(ap, char *);
					next_str_size = sizeof(char) * _strlen(next_str);
					counter += write(1, next_str, next_str_size);
					i++;
					break;
			}
		}
		else
			counter += _putchar(format[i]);
	}

	va_end(ap);
	return (counter);
}

