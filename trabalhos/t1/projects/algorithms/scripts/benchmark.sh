#!/bin/sh

output_dir=results

default_start_size=0
default_end_size=10000000

limited_start_size=0
limited_end_size=100000

step=100000
samples=100

benchmark() {
    algorithm=$1
    source=$2
    start_size=$3
    end_size=$4
    step=$5
    samples=$6

    mkdir -p "$output_dir/$source"

    echo "Benchmarking $algorithm with $source data..."
    ./bin benchmark "$algorithm" "$source" "$start_size" "$end_size" "$step" "$samples" \
        1> "$output_dir/$source/$algorithm.txt"
}

benchmark recursive_mergesort ascending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark iterative_mergesort ascending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark parallel_mergesort ascending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark insertionsort ascending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark quicksort ascending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark quicksert ascending "$default_start_size" "$default_end_size" "$step" "$samples"

benchmark recursive_mergesort descending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark iterative_mergesort descending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark parallel_mergesort descending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark insertionsort descending "$limited_start_size" "$limited_end_size" "$step" "$samples"
benchmark quicksort descending "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark quicksert descending "$default_start_size" "$default_end_size" "$step" "$samples"

benchmark recursive_mergesort random "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark iterative_mergesort random "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark parallel_mergesort random "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark insertionsort random "$limited_start_size" "$limited_end_size" "$step" "$samples"
benchmark quicksort random "$default_start_size" "$default_end_size" "$step" "$samples"
benchmark quicksert random "$default_start_size" "$default_end_size" "$step" "$samples"
