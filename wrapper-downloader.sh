#!/bin/bash
# Parallel wrapper for convert.sh avif-converter

# Specify the file with image URLs
urlfile=image-list.txt
# Number of parallel processes
processes=3

totallines=$(cat $urlfile | wc -l)

echo "total lines: $totallines"

for ((i=1;i<=$totallines;i+=$processes)); do
    # take the i-element, i+1 and ... and up to i+processes-1
    limit=$((($processes - 1)))
    for ((x=0;x<=$limit;x++)); do
        current=$(($i + $x))
        if [ $current -gt $totallines ]
        then
            # do nothing
            echo skip
        else
            echo cycle $i iternation $x line $current
            url=$(sed -n $current'p' < $urlfile)
            ./convert.sh $url
        fi
    done
done

echo end
