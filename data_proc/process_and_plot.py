import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import numpy as np
import tables as tb
import pandas as pd

import sys
filename = sys.argv[1]

tot_num = 1e10
#probs = []
#
#with open(filename, "r") as f:
#    for line in f:
#        linearr = line.split("\t")
#        probs.append(float(linearr[1])/tot_num)
#data_types = [('fun', 'S128'), ('freq', 'uint64')]
##data = np.memmap(filename, mode='r', dtype=data_types)
#tb_name = "full_sample.h5t"
#h5 = tb.open_file(tb_name, "w")
#
#tab = h5.create_table(
#    "/", "funs",
#    description=data_types)

it = pd.read_csv(filename, dtype={'fun': 'S128', 'freq': 'uint64'}, header=None, iterator=True, delim_whitespace=True, names=["fun","freq"], chunksize=100000)
#it = pd.read_csv(filename, dtype={'freq': 'uint64'}, header=None, iterator=True, delim_whitespace=True, names=["freq"], chunksize=1000000)
#for chunk in it:
#    tab.append(chunk.to_records(index=False))
#tab.flush()

rank_tot = 0
for chunk in it:
    plt.plot(range(rank_tot,rank_tot+len(chunk)),chunk['freq']/tot_num,'b,')
    rank_tot+=len(chunk)

#num_singlesamples = 1767085190 - 67382635
#plt.plot(range(rank_tot,rank_tot+num_singlesamples),num_singlesamples*[1]/tot_num,'b,')

plt.yscale("log")
plt.xscale("log")
plt.xlabel("Rank")
plt.ylabel("Probability")
plt.savefig("test_prob_rank_1e10_nn_7_40_40_1_LecunDist.png")
