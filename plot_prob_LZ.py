#!/usr/bin/python3
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import sys

d=pd.read_csv(sys.argv[1],delim_whitespace=True, header=None)
#print(d[0])
LZs = d[int(sys.argv[2])]
freqs = d[int(sys.argv[3])]
probs = freqs/sum(freqs)
plt.scatter(LZs,probs)
plt.yscale("log")
plt.ylabel("Probability")
plt.xlabel("LZ complexity")
plt.ylim([probs.min()*0.9, probs.max()*1.1])
plt.xlim([LZs.min()*0.9, LZs.max()*1.1])
plt.savefig(sys.argv[1]+"_prob_LZ_plot.png")
