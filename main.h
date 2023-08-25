#ifndef _MAIN_H_
#define _MAIN_H_

/**
 * struct State - _printf(..) state
 * @fmt_idx: the current index of the format string parameter.
 * @has_space: boolean indicates if the % is followed by a space char.
 * @counter: nnumber of chars been printed.
 * @is_no_specifier: boolean indicates wheter the % is followed by no specifier
 *			except the space char and the null char.
 * @specifier: the char followed the %
 *
 * Description: state of the _printf function.
 */
typedef struct State
{
	unsigned int fmt_idx, has_space, is_no_specifier;
	int counter;
	char specifier;
} state_t;

unsigned int _strlen(const char *);
int _putchar(char);
int _printf(const char *format, ...);

#endif
