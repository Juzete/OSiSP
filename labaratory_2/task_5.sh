#!/bin/bash
for file in "$1"/*; do
  [ "$file" != ".//task_5.sh" ] && [[ -x "$file" ]] && sh $file
done