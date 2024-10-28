#!/bin/bash

sources="0 1 2"
methods="0 1 2"

start_size=0
end_size=100000
step=1000

for method in $methods; do
    for source in $sources; do
        mkdir -p "results/${source}"

        ./bin "${method}" "${source}" "${start_size}" "${end_size}" "${step}" \
            1> "results/${source}/${method}.txt"
    done
done