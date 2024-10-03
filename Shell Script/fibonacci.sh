#!/bin/bash

# Function to generate Fibonacci series
generate_fibonacci() {
    n=$1
    a=0
    b=1

    echo "Fibonacci series up to $n terms:"
    echo -n "$a "

    for ((i = 1; i < n; i++)); do
        echo -n "$b "
        fn=$((a + b))
        a=$b
        b=$fn
    done
    echo ""
}

# Main script
echo "Enter the number of terms for Fibonacci series:"
read num_terms

generate_fibonacci $num_terms
