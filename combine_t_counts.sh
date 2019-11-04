#!/bin/bash

prefix=$1
arch=$2

cat nn_t_counts/${prefix}*${arch}* | awk '{F[$1]+=$2} END { for (i in F) print i,F[i]}' > ${prefix}_${arch}_t_counts.txt
