#include "main.h"
#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

#define IS_VALID_SPECIFIER(c)                                          \
	((c) == '%' || (c) == 'c' || (c) == 's' || (c) == 'd' ||       \
	 (c) == 'i' || (c) == 'b' || (c) == 'u' || (c) == 'o')


void set_specifier(const char *format, state_t *state);
void handle_specifier(const char *format, va_list args, state_t *state);
int handle_string(char *s);

/**
 * _printf - produces output according to a format
 * @format: string contaionig the format.
 *
 * Return: the number of chars printed excluding the null char.
 */

int _printf(const char *format, ...)
{
	va_list ap;
	unsigned int len;
	state_t state;

	if (format == NULL)
		return (-1);

	len = _strlen(format);
	va_start(ap, format);

	for (state.fmt_idx = 0; state.fmt_idx < len; state.fmt_idx++)
	{
		if (format[state.fmt_idx] == '%')
		{
			handle_specifier(format, ap, &state);
		} else
			state.counter += _putchar(format[state.fmt_idx]);
	}

	va_end(ap);
	return (state.counter == 0 && state.is_no_specifier ? -1 : state.counter);
}

/**
 * set_specifier - set the specifier in state after the %
 * @format: string passed to the _printf function.
 * @state: state of the program.
 *
 * Return: always void
 */
void set_specifier(const char *format, state_t *state)
{
	unsigned int i = state->fmt_idx + 1, has_space = 0;

	if (format[i] == ' ')
		has_space = 1;
	while (format[i] == ' ' && format[i] != '\0')
		i++;

	state->has_space = has_space;
	state->specifier = format[i];
	state->fmt_idx = i;
}
/**
 * handle_specifier - handle the specifier after the % in @format
 *		(determine wheter or not to print, consume the args va_list)
 * @format: the string passed to the _printf(..).
 * @args: va_list of all args passed to the function.
 * @state: the state of the progra.
 *
 * Return:always void.
 */
void handle_specifier(const char *format, va_list args, state_t *state)
{
	char specifier;

	set_specifier(format, state);
	specifier = state->specifier;
	if (!specifier)
	{
		state->is_no_specifier = 1;
		return;
	}

	/* '% %' || '%  k' */
	if (!IS_VALID_SPECIFIER(specifier) || specifier == '%')
		state->counter += _putchar('%');

	if (specifier != '%')
	{
		if (specifier == 'c')
		{
			state->counter += _putchar(va_arg(args, int));
		} else if (specifier == 's')
		{
			state->counter += handle_string(va_arg(args, char *));
		} else
		{
			/* handle spaces between % and specifier */
			if (state->has_space)
				state->counter += _putchar(' ');
			if (specifier == 'd' || specifier == 'i')
				state->counter += handle_numbers(va_arg(args, int), 1);
			else if (
					specifier == 'b' ||
					specifier == 'u' ||
					specifier == 'o')
				state->counter += handle_numbers(va_arg(args, unsigned int), specifier);
			else
				state->counter += _putchar(specifier);
		}
	}
}

/**
 * handle_string - handles the %s specifier
 *	write to stdout the string
 *	if the string is NULL then it's converted to (null)
 * @s: string to be handled
 *
 * Return: number of characters in s.
 */
int handle_string(char *s)
{
	unsigned int counter;

	counter = write(1, (s == NULL ? "(null)" : s),
			sizeof(char) * (s == NULL ? 6 : _strlen(s)));
	return (counter);
}

