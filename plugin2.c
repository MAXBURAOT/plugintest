#include "plugin.h"

#include <stdio.h>

#define PLUGINNAME "plugin2"

/**
 * This is a static variable, global to the plugin, to store the interface
 * address retrieved from the core. It matches the exported interfaces from the
 * core, in order to use the same syntax inside the plugin.
 */
int *foo;

void fun2(void);

/**
 * This function is a test-case against FreeBSD mixing up functions with the
 * same name in core and plugin.
 */
HPMEXPORT void fun(void)
{
	printf("This is fun from "PLUGINNAME"\n");
	if (foo)
		printf("("PLUGINNAME") foo++: %d.\n", (*foo)++);
	else
		printf("("PLUGINNAME") foo is null.\n");
	fun2();
}


