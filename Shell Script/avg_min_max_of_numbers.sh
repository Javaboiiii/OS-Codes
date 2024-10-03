#!/bin/bash
function calculate_average() {
  sum=0
  count=0
  for num in "$@"; do
    sum=$((sum + num))
    count=$((count + 1))
  done
  if [ $count -gt 0 ]; then
    average=$((sum / count))
    echo $average
  else
    echo "No numbers provided."
  fi
}
function find_max() {
  max=$1
  for num in "$@"; do
    if [ $num -gt $max ]; then
      max=$num
    fi
  done
  echo $max
}
function find_min() {
  min=$1
  for num in "$@"; do
    if [ $num -lt $min ]; then
      min=$num
    fi
  done
  echo $min  # Adding the echo statement to print the minimum value
}
average=$(calculate_average "$@")
max=$(find_max "$@")
min=$(find_min "$@")
echo "Average of numbers: $average"
echo "Maximum number: $max"
echo "Minimum number: $min"
