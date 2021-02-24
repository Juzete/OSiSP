#!/bin/bash
array=$(find $1 -name *[0-9]*[0-9]*[0-9]*[0-9]*)
for i in ${array[@]};
do 
echo $i
mv $i $2
done
