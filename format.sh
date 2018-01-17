#!/usr/bin/env bash
files=`find ./ -name \*.h` > /dev/null
for file in $files
do
    astyle --style=ansi  -p -U -S -w -t2 $file
done

files=`find ./ -name \*.orig` > /dev/null
rm -f $files

files=`find ./ -name \*.c` > /dev/null
for file in $files
do
    astyle --style=ansi  -p -U -S -w -t2 $file
done

files=`find ./ -name \*.orig` > /dev/null
rm -f $files
