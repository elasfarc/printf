#include <stdio.h>
#include <limits.h>
#include "main.h"

int main(void)
{
	int len, len2;
	/*unsigned int ui;
	void *addr;*/

	len = _printf("Let's try to printf a simple sentence.\n");
	len2 = printf("Let's try to printf a simple sentence.\n");
	/*ui = (unsigned int)INT_MAX + 1024;
	addr = (void *)0x7ffe637541f0;*/
       	_printf("Length:[%d, %i]\n", len, len);
	printf("Length:[%d, %i]\n", len2, len2);
	printf("\n");
	_printf("%d", 0);
	printf("\n");
	_printf("%d", INT_MIN);
	_printf("\n");
	return (0);
}

