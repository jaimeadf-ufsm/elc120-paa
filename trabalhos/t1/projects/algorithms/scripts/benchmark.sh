#!/bin/sh

output_dir=results

sources="ascending descending random"

default_start_size=0
default_end_size=10000

limited_start_size=0
limited_end_size=1000000

step=1000
samples=1

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

for source in $sources; do
    benchmark recursive_mergesort "$source" "$default_start_size" "$default_end_size" "$step" "$samples"
    benchmark iterative_mergesort "$source" "$default_start_size" "$default_end_size" "$step" "$samples"
    benchmark parallel_mergesort "$source" "$default_start_size" "$default_end_size" "$step" "$samples"
    benchmark insertionsort "$source" "$limited_start_size" "$limited_end_size" "$step" "$samples"
    benchmark quicksort "$source" "$default_start_size" "$default_end_size" "$step" "$samples"
    benchmark quicksert "$source" "$default_start_size" "$default_end_size" "$step" "$samples"
done
