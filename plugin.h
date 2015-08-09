#include <stdio.h>
#include <dlfcn.h>
#include <stdbool.h>

/**
 * This is a static variable, global to the plugin, to store the interface
 * address retrieved from the core. It matches the exported interfaces from the
 * core, in order to use the same syntax inside the plugin.
 */
static int *foo;

/**
 * Function pointer to the symbol importer in the core. This function returns a
 * pointer to the requested symbol/interface. It's automatically initialized
 * upon plugin load.
 */
void *(*import_symbol) (void);

/**
 * Function that the core will call after the plugin is loaded (this is to
 * automate symbol import into the plugin). Relies on import_symbol being
 * already set.
 */
bool HPM_shared_symbols(int server_type)
{
	foo = (int *)import_symbol();
	return foo ? true : false;
}
