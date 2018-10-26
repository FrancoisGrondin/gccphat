#!/bin/bash

# $1: files to process
# $2: folder to receive results
# $3: executable path
# $4: method ('f', 'q', 'm','s')
# $5: interpolation rate

subfolder="$2$4-$5/"
mkdir $subfolder

for f in $1
do
	filename=$(basename -- "$f")
	filename="${filename%.*}"
	eval "cat $f | $3 -c 343 -d 0.05 -i $5 -m $4 -N 512 -o -Q 181 -r 16000 > $subfolder$filename.txt"
done
