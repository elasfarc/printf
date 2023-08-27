#include <stdlib.h>
#include "main.h"

#define IS_NEGATIVE(n) ((n) < 0)
/**
 * modulo - get the remainder operation
 * @n1: first number.
 * @n2: second number.
 *
 * Return: int - the remainder.
 */
int modulo(int n1, int n2) { return n1 % n2; }

/**
 * divide - get the divition operation
 * @n1: first number.
 * @n2: second number.
 *
 * Return: int - the result of the division.
 */
int divide(int n1, int n2) { return n1 / n2; }

/**
 * operation - get the function pointer to the @op.
 * @op: the operation sign. (currently '/' or '%')
 *
 * Return: function pointer to the associated @op.
 */
int (*operation(char op))(int, int)
{
	return (op == '/' ? &divide : &modulo);
}

/**
 * get_digits_len - get number of chars
 *  required to represent a number into a string.
 * @num: the number to be represented.
 * @tag: determine the base by which a divisor is obtained.
 *              ('b'-> for binary, 'd' or 'i' -> for decimel)
 * @is_negative: a flag to represent wheter or not the @num is negative.
 *
 * Return: int -> the number of chars required.
 */
int get_digits_len(double num, short tag, short is_negative)
{
	int len = 0, temp;
	short divisor = tag == 'b' ? 2 : 10;

	if (num == 0)
		len = 1;
	else
		for (temp = (int)num; temp != 0;
				temp = operation('/')(temp, divisor))
			len++;

	len = len + is_negative + 1; /* +1 for the null char */

	return (len);
}

/**
 * itoASCII - convert an integer to it's ASCII representaion.
 * @s: pointer to the string to save the convertion at.
 * @len: length of @s.
 * @num: the number to be converted.
 * @is_negative: a flag to represent wheter or not @num is negative.
 *
 * Return: a pointer to string (@s)
 */
char *itoASCII(char *s, int len, int num, short is_negative)
{
	short i, rmder;

	s[len - 1] = '\0';
	if (is_negative)
		s[0] = '-';
	for (i = len - 2; (is_negative ? i > 0 : i >= 0); i--)
	{
		rmder = num % 10;
		s[i] = is_negative ? ('0' - rmder) : (rmder + '0');
		num /= 10;
	}
	return (s);
}

/**
 * handle_numbers - handle the %d, %i, %b specifiers
 * @n: number to be printed.
 * @tag: tag of the number
 *		'd' or 'i' for int, 'b' for binary
 *
 * Return: number of digits in @n
 */
int handle_numbers(double n, char tag)
{
	int counter = 0, len = 0;
	char *digits;
	short is_negative;

	is_negative = IS_NEGATIVE(n);

	len = get_digits_len(n, tag, is_negative);
	digits = malloc(sizeof(char) * len);
	digits = !digits ? NULL : itoASCII(digits, len, n, is_negative);

	counter += handle_string(digits);
	free(digits);
	return (counter);
}

/*
*int deci(int n, char op) { return operation(op)(n, 10); }
*int binary(int n, char op) { return operation(op)(n, 2); }
*int perform_operation(char op, int n1, int n2)
*{
*	return (operation(op)(n1, n2));
*}
*/

