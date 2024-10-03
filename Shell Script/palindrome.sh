#!/bin/bash

is_palindrome() {
  local str="$1"
  local reverse_str=$(echo "$str" | rev)
  if [ "$str" = "$reverse_str" ]; then
    return 0 
  else
    return 1 
  fi
}

if [ $# -ne 1 ]; then
  echo "Usage: $0 <string>"
  exit 1
fi

input_string="$1"

if is_palindrome "$input_string"; then
  echo "The entered string is a palindrome."
else
  echo "The entered string is not a palindrome."
fi
