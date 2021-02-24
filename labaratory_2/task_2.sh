#!/bin/bash
array=$(find $1 -name *.$2)
for i in ${array[@]};
do 
echo $i
rm $i
done