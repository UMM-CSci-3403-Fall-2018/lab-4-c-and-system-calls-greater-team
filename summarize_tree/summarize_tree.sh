#!/bin/bash

path=$1
num_dirs=$(find $path -type d | wc -l)
num_reg=$(find $path -type f | wc -l)

echo There were $num_dirs directories.
echo There were $num_reg regular files.

