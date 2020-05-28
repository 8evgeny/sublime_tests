#!/bin/sh
A=0;
for i in $(find $1 | grep -E '.*\.h$'\|'.*\.cpp$'\|'.*\.hpp$'); do
	let "A+=$(cat "$i" | wc -l)";
done
echo $A
