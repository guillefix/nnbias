#!/bin/bash

#cat results_full_enum/3_full_enum_discrete_weights_net_0hl.txt | shuf | sort --parallel=16 -sk2 > sorted_3bit_perceptron_full_enum.txt

#LANG=C; cat sorted_3bit_perceptron_full_enum.txt | uniq -cf1 | mawk '{for (i = 1; i <= 5; ++i) printf s+int($1*rand())"\n"; s+=$1}' | sort --parallel=15 -sn > indices
#cat sorted_3bit_perceptron_full_enum.txt | awk '{print $1}' | cut -f1 |./get_random_lines_from_freqs.py > indices

#cat sorted_3bit_perceptron_full_enum.txt | awk 'i<100 {print $0; i=i+1} output""!=$2"" {i=0;output=$2""}' > random_inputs_3bit_perceptron.txt
cat sorted_3bit_perceptron_full_enum.txt | ./get_random_inputs.py 100

#cat sorted_3bit_perceptron_full_enum.txt | awk 'BEGIN {getline line < indices} NR==line {getline line < indices; print $0}'
