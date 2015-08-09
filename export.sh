#!/bin/sh

echo "main exports"
nm "main"|grep "foo"
echo "plugin1 exports"
nm "plugin1.dylib"|grep "foo"
echo "plugin2 exports"
nm "plugin2.dylib"|grep "foo"
