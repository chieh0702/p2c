#!/bin/bash

if [ $# -ne 1 ]; then
    echo "請提供文件名作為參數"
    exit 1
fi

echo >> "$1"

regex="(.*)alerting(.*)':([0-9]+): (.*)"

output_filename="out.file"

while IFS= read -r line; do
    if [[ $line =~ $regex ]]; then

        hand1="${BASH_REMATCH[1]}"
        hand2="${BASH_REMATCH[2]}"
        old_line_number="${BASH_REMATCH[3]}"
        tail="${BASH_REMATCH[4]}"
        
        new_line_number=$(grep -n "alerting" "$1" | grep "$tail" | cut -d: -f1)
        
        modified_line="${hand1}alerting$hand2':$new_line_number: $tail"
        
        echo "$modified_line" >> $output_filename
    else
        echo "$line" >> $output_filename
    fi
done < "$1"

diff --color -uw "$1" "$output_filename"

echo "approve change (y/n)"
read key
if [ $key = "y" ]; then
    mv "$output_filename" "$1"
else
    rm "$output_filename"
fi