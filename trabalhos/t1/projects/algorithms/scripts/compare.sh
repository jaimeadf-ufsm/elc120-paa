#!/bin/sh

python scripts/plot.py time -o time_ascending.png results/ascending/*
python scripts/plot.py time -o time_descending.png results/descending/*
python scripts/plot.py time -o time_random.png results/random/*

python scripts/plot.py complexity -o complexity_ascending_recursive_mergesort.png results/ascending/recursive_mergesort.txt
python scripts/plot.py complexity -o complexity_ascending_iterative_mergesort.png results/ascending/iterative_mergesort.txt
python scripts/plot.py complexity -o complexity_ascending_parallel_mergesort.png results/ascending/parallel_mergesort.txt

python scripts/plot.py complexity -o complexity_descending_recursive_mergesort.png results/descending/recursive_mergesort.txt
python scripts/plot.py complexity -o complexity_descending_iterative_mergesort.png results/descending/iterative_mergesort.txt
python scripts/plot.py complexity -o complexity_descending_parallel_mergesort.png results/descending/parallel_mergesort.txt

python scripts/plot.py complexity -o complexity_random_recursive_mergesort.png results/random/recursive_mergesort.txt
python scripts/plot.py complexity -o complexity_random_iterative_mergesort.png results/random/iterative_mergesort.txt
python scripts/plot.py complexity -o complexity_random_parallel_mergesort.png results/random/parallel_mergesort.txt
