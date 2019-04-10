#!/bin/bash
echo expected results: -4033.151304 108682305.051810 -164176073.349746 -263485118585367000000 -314940386395426000
for i in mat3.txt mat4.txt mat5.txt mat6.txt mat7.txt; do
  echo Processing file $i 
  ./det < $i
done
