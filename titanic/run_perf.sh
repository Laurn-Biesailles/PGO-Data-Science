#!/bin/bash

echo "data/train.csv" | perf record -g a.out
echo "data/dataset1.csv" | perf record -g a.out
echo "data/dataset2.csv" | perf record -g a.out
echo "data/dataset3.csv" | perf record -g a.out
echo "data/dataset4.csv" | perf record -g a.out
echo "data/dataset5.csv" | perf record -g a.out
echo "data/fakeset.csv" | perf record -g a.out
