#include <stdio.h>

extern int *foo;

/**
 * This function is a test-case against FreeBSD mixing up functions with the
 * same name in core and plugin.
 */
void fun2(void)
{
	printf("This is fun2\n");
	if (foo)
		printf("foo++: %d.\n", (*foo)++);
	else
		printf("foo is null.\n");
}

