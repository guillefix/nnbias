set term png
set output system("echo ${file2}")
set datafile separator "\t"
set logscale xy
plot '<cat' using 1 with lines

