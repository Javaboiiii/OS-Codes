#!/bin/bash

# Function to check if a number is prime
is_prime() {
    num=$1
    if [ $num -lt 2 ]; then
        return 1  # Not prime
    fi

    # Loop to check divisibility from 2 to sqrt(num)
    for ((i = 2; i * i <= num; i++)); do
        if [ $((num % i)) -eq 0 ]; then
            return 1  # Not prime
        fi
    done

    return 0  # Prime
}

# Main script
echo "Enter a number to check if it's prime:"
read number

if is_prime $number; then
    echo "$number is a prime number."
else
    echo "$number is not a prime number."
fi
