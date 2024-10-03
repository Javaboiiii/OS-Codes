#!/bin/bash

# Function to calculate the length of a string
calculate_length() {
    string="$1"
    echo "Length of the string '$string' is ${#string} characters."
}

# Function to concatenate two strings
concatenate_strings() {
    string1="$1"
    string2="$2"
    concatenated="$string1$string2"
    echo "Concatenated string: $concatenated"
}

# Function to extract a substring from a string
extract_substring() {
    string="$1"
    start="$2"
    length="$3"
    substring="${string:start:length}"
    echo "Substring from position $start with length $length: $substring"
}

# Function to convert a string to uppercase
to_uppercase() {
    string="$1"
    uppercase="${string^^}"
    echo "Uppercase version of the string '$string': $uppercase"
}

# Function to convert a string to lowercase
to_lowercase() {
    string="$1"
    lowercase="${string,,}"
    echo "Lowercase version of the string '$string': $lowercase"
}

# Main script
echo "Enter a string:"
read input_string

calculate_length "$input_string"
echo

echo "Enter another string to concatenate with the first one:"
read second_string
concatenate_strings "$input_string" "$second_string"
echo

echo "Enter the starting position to extract a substring from the first string:"
read start_position
echo "Enter the length of the substring:"
read substring_length
extract_substring "$input_string" "$start_position" "$substring_length"
echo

to_uppercase "$input_string"
echo

to_lowercase "$input_string"
