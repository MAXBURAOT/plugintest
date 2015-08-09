CC = gcc
PLUGINEXT = so

HEADERS = $(shell ls *.h)

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	PLUGINEXT = dylib
endif

ifeq ($(UNAME),FreeBSD)
	CC = clang
endif

ifneq ($(UNAME),FreeBSD)
	EXTRACFLAGS = -ldl
endif

all: core plugins

core: main

plugins: plugin1.$(PLUGINEXT) plugin2.$(PLUGINEXT)

%.$(PLUGINEXT): %.c $(HEADERS)
	$(CC) -DPLUGINEXT=$(PLUGINEXT) $(CFLAGS) $(EXTRACFLAGS) -g -rdynamic -fPIC -shared -o $@ $<

%: %.c %.h
	$(CC) -DPLUGINEXT=$(PLUGINEXT) $(CFLAGS) $(EXTRACFLAGS) -g -o $@ $<

clean:
	rm -rf main *.$(PLUGINEXT) *.dSYM *.core
