#include "plugin.h"

#include <stdio.h>

#define PLUGINNAME "plugin2"

/**
 * This function is a test-case against FreeBSD mixing up functions with the
 * same name in core and plugin.
 */
void fun(void)
{
	printf("This is fun from "PLUGINNAME"\n");
	if (foo)
		printf("("PLUGINNAME") foo++: %d.\n", (*foo)++);
	else
		printf("("PLUGINNAME") foo is null.\n");
}


