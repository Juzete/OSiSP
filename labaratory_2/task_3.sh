#!/bin/bash
array=$(find $1 -name $2)
for i in ${array[@]};
do 
echo $i
cp $i $3
cp $i $4
done