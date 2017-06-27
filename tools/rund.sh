#!/bin/sh

set -e

mkdir -p $1_dir
cp $1 $1_dir/main.d
cd $1_dir

if which rdmd > /dev/null; then
    rdmd main.d
elif which gdc > /dev/null; then
    gdc -o main main.d > /dev/null && ./main
else
    ldc2 -of=main main.d > /dev/null && ./main
fi
