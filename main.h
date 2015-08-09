#ifndef PLUGINEXT
#define PLUGINEXT so
#endif

#define QUOTE(x) #x
#define EXPAND_AND_QUOTE(x) QUOTE(x)
#define NOEXPORT __attribute__((visibility ("hidden")))

/// This symbol is exported by the core.
extern int *foo;
