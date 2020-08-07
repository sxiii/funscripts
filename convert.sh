#!/bin/bash
# Auto-downscale images if they are "larger than X" script
# All tasks are sent to background to allow working in parallel
# Requirements: Linux, Bash, Imagemagick
# By SecurityXIII @ Aug 2020

maxsize=4096         # Maximum image size
resizeto=1920x1080   # Resize to this, if larger than $maxsize
convertto=".avif"    # Target format

temp=$(mktemp -d)

wget --no-check-certificate $1 -O $temp/img

ConvertInParallel () {
    local f=$1
    width=$(identify -format "%w" $f 2>/dev/null)
    height=$(identify -format "%h" $f 2>/dev/null)

    if [ -z "$width" ] || [ -z "$height" ] ; then
        echo "Cannot identify file $f size, skipping."
    else
       if [ $width -ge $maxsize ] || [ $height -ge $maxsize ]; then
          echo "File $f has width $width and is larger than 4096, downscaling"
          convert -scale $resizeto $f $f$convertto
       elif [ $width -lt $maxsize ]; then
          echo "File $f has width $width and is smaller than 4096, keeping"
       fi
    fi
}

ConvertInParallel $temp/img &

exit
