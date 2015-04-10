#!/bin/bash
# Reads poem from yandex. Give it url like:
# ./poetread.sh http://autopoet.yandex.ru/limerik/18/
# Yandex Poem Styles are: limerik, onegin, other, monorim, poroshki
python poetread.py $1 > poem1.txt

while read line; do
tt=${line// /+}
echo "$line"
cvlc "http://translate.google.com/translate_tts?ie=UTF-8&tl=ru&q=$tt" vlc://quit &> /dev/null
done < poem1.txt
