import pandas as pd

d = pd.read_csv("big_chonker.txt", skiprows=7, skipfooter=6, delim_whitespace=True, header=None, names=["fun","freq"])

d = d.sort_values(by="freq",inplace=True,ascending=False)

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

d.tp_hdf("full_sample.h5",'funs')

plt.plot(range(len(d)),d['freq'],'b,')
plt.xlabel("Rank")
plt.ylabel("Probability")
plt.savefig("prob_rank_1e10_nn_7_40_40_1_LecunDist.p")


