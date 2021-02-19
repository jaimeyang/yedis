#!/bin/bash
path=/home/jaime/code/yedis/lib/lua/src
files=$(ls $path)
for filename in $files
do
   echo lib/lua/src/$filename >> filename.txt
done