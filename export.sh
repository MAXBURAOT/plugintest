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
nm "main"|grep "foo"
echo "plugin1 exports"
nm "plugin1.$PLUGINEXT"|grep "foo"
echo "plugin2 exports"
nm "plugin2.$PLUGINEXT"|grep "foo"
