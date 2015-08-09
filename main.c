#include "main.h"

#include <dlfcn.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int foo_s; /// Interface source
int *foo;  /// Interface pointer

struct plugin_data {
	void *handle;
	void (*fun) (void);
};

/**
 * Symbol importer. Called by plugins, it returns a pointer to the requested
 * interface (here we have only one, foo).
 */
HPMEXPORT void *plugin_import_symbol(void)
{
	return foo;
}

/**
 * Convenience function. Prints the value of foo and increases it.
 */
void printfoo(void)
{
	if (foo)
		printf("(main) foo++: %d.\n", (*foo)++);
	else
		printf("(main) foo is null.\n");
}

/**
 * This function is a test-case against FreeBSD mixing up functions with the
 * same name in core and plugin.
 */
void fun(void)
{
	printf("This is fun from main.\n");
}

/**
 * Plugin loader. Loads a plugin by name.
 */
struct plugin_data *load_plugin(const char *name, struct plugin_data *data)
{
	void **pimport = NULL;
	void (*pinit) (void) = NULL;
	char buf[256];
	snprintf(buf, 256, "./%s.%s", name, EXPAND_AND_QUOTE(PLUGINEXT));
	data->handle = dlopen(buf, RTLD_NOW);
	if (!data->handle) {
		printf("%s: dlopen error: %s\n", name, dlerror());
		return NULL;
	}
	pimport = dlsym(data->handle, "import_symbol");
	if (!pimport) {
		printf("%s: missing symbol import_symbol\n", name);
		return NULL;
	}
	*pimport = plugin_import_symbol;
	pinit = dlsym(data->handle, "HPM_shared_symbols");
	if (!pinit) {
		printf("%s: missing symbol HPM_shared_symbols\n", name);
		return NULL;
	}
	pinit();
	data->fun = dlsym(data->handle, "fun");
	if (!data->fun) {
		printf("%s: missing symbol fun\n", name);
		return NULL;
	}
	printf("Plugin %s.%s loaded.\n", name, EXPAND_AND_QUOTE(PLUGINEXT));
	return data;
}

int main(int argc, char *argv[])
{
	int i;
	struct plugin_data *handles = malloc(sizeof(struct plugin_data) * (argc-1));

	if (argc < 2) {
		printf("Usage: %s plugin1 plugin2 ...\n", argv[0]);
		return EXIT_FAILURE;
	}

	// Connect and initialize symbols
	foo = &foo_s;
	*foo = 1;

	// Show initial values
	fun();
	printfoo();
	printf("--------------\n");

	// Load plugins
	for (i = 0; i < argc - 1; ++i) {
		if (!load_plugin(argv[i+1], &handles[i])) {
			return EXIT_FAILURE;
		}
	}

	printf("--------------\n");

	// Execute plugin functions
	for (i = 0; i < argc - 1; ++i) {
		printf("Plugin: %s\n", argv[i+1]);
		handles[i].fun();
		printfoo();
		printf("--------------\n");
	}

	// Show final values again
	fun();
	printfoo();

	// Unload plugins
	for (i = 0; i < argc - 1; ++i) {
		dlclose(handles[i].handle);
	}
	free(handles);

	return EXIT_SUCCESS;
}
