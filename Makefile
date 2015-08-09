CC = gcc
PLUGINEXT = dylib

HEADERS = $(shell ls *.h)

all: core plugins

core: main

plugins: plugin1.$(PLUGINEXT) plugin2.$(PLUGINEXT)

%.$(PLUGINEXT): %.c $(HEADERS)
	$(CC) -DPLUGINEXT=$(PLUGINEXT) -g -rdynamic -fPIC -shared -o $@ $<

%: %.c %.h
	$(CC) -DPLUGINEXT=$(PLUGINEXT) -g -o $@ $<

clean:
	rm -rf main *.$(PLUGINEXT) *.dSYM *.core
