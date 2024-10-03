#!/bin/bash

# Function to perform addition
addition() {
    result=$(($1 + $2))
    echo "Result of addition: $result"
}

# Function to perform subtraction
subtraction() {
    result=$(($1 - $2))
    echo "Result of subtraction: $result"
}

# Function to perform multiplication
multiplication() {
    result=$(($1 * $2))
    echo "Result of multiplication: $result"
}

# Function to perform division
division() {
    if [ $2 -eq 0 ]; then
        echo "Error: Division by zero is not allowed."
    else
        result=$(($1 / $2))
        echo "Result of division: $result"
    fi
}

# Function to perform modulus
modulus() {
    if [ $2 -eq 0 ]; then
        echo "Error: Modulus by zero is not allowed."
    else
        result=$(($1 % $2))
        echo "Result of modulus: $result"
    fi
}

# Main script
echo "Enter two numbers:"
read num1
read num2

addition $num1 $num2
subtraction $num1 $num2
multiplication $num1 $num2
division $num1 $num2
modulus $num1 $num2
