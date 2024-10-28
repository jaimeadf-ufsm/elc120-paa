#!/bin/bash

python scripts/plot.py -o ascending.png results/0/*
python scripts/plot.py -o descending.png results/1/*
python scripts/plot.py -o random.png results/2/*