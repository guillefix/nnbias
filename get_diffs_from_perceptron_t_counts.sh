#!/bin/bash

# same but for neural net samples I got
#cat nn_t_counts/* | awk '{F[$1]+=$2} END { for (i in F) print i,F[i]}' > 2_7_1hl_t_counts.txt
cat nn_t_counts/* | awk '{F[$1]+=$2} END { for (i in F) print i,F[i]}' > 2_5_1hl_t_counts.txt

#get differences
awk '{print $2}' 2_5_1hl_t_counts.txt | awk '
    NR == 1{old = $1; next}     # if 1st line
    {print $1 - old; old = $1}  # else...
' > n5_t_diffs_1hl_1e10.txt #head -n 64

