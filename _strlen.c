/**
 * _strlen - gives the length of a string.
 * @str: string to get it's length
 *
 * Return: the length of the string
 */

unsigned int _strlen(const char *str)
{
	return (str[0] != '\0'
		 ? 1 + _strlen(str + 1)
		 : 0);
}

