#!/bin/sh

case `uname` in
	Darwin)
		PLUGINEXT=dylib
		;;
	*)
		PLUGINEXT=so
		;;
esac

echo "main exports"
nm "main"|egrep "foo|HPM_shared_symbols|import_symbol"
echo "plugin1 exports"
nm "plugin1.$PLUGINEXT"|egrep "foo|HPM_shared_symbols|import_symbol"
echo "plugin2 exports"
nm "plugin2.$PLUGINEXT"|egrep "foo|HPM_shared_symbols|import_symbol"
