#!/bin/bash
echo "Enter length of array:"
read n

echo "Enter numbers in the array: "
for (( i = 0; i < n; i++ ))
do
    read arr[$i]
done

echo "Numbers in the array are: "
for ((i = 0; i < n; i++))
do
    echo ${arr[$i]}
done

for ((i = 0; i < n; i++))
do
    for ((j = i+1; j < n; j++))
    do
        if [ ${arr[$i]} -gt ${arr[$j]}  ]; then
            temp=${arr[$i]}
            arr[$i]=${arr[$j]}
            arr[$j]=$temp
        fi
    done
done

echo -e "\nSorted Numbers: "
for ((i=0; i < n; i++))
do
    echo ${arr[$i]}
done

