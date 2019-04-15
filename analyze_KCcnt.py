import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
%matplotlib

'''LOAD DATA'''
n = 7
disc_bits = 3
nI = disc_bits*(n+1)
d = pd.read_csv("KCcnt_"+str(disc_bits)+"_full_enum_discrete_weights_net_0hl.txt", header=None, names=["Kout","KInMin","KInMax","KInMean","freq"],delim_whitespace=True)
d = pd.read_csv("KCcnt_plus_"+str(disc_bits)+"_full_enum_discrete_weights_net_0hl.txt", header=None, dtype={"out":"str","minIn":"str","maxIn":"str"}, names=["out","minIn","maxIn","Kout","KInMin","KInMax","KInMean","freq"],delim_whitespace=True)
d = d.sort_values(by="Kout",ascending=False)

d["KIMin-KInMax"] = d["KInMax"] - d["KInMin"]
d["Kout-KInMax+n"] = d["Kout"] - d["KInMax"] + nI
d["KInMax-Kout-n"] = -d["Kout-KInMax+n"]
d["Kout-KInMin"] = d["Kout"] - d["KInMin"]
d["n-KInMax"] = nI - d["KInMax"]
##upper bound
a=0.13; b=3
d["logP0-logP"] = -a*d["Kout"] - b - np.log2(d["freq"]) + nI
d["P0"] = 2**(-a*d["Kout"] - b)


### CUMULATIVE PROB VS DELTAP
d["prob"] = d["freq"]/sum(d["freq"])
# sum(d["prob"])
# d["prob"]
d = d.sort_values(by="logP0-logP",ascending=False)
d["cumprob"] = d["prob"].cumsum()
plt.axes([0.15, 0.1, .75, .8])
plt.plot(list(d["logP0-logP"]),list(d["cumprob"]))
plt.yscale("log")
delmax = max(d["logP0-logP"])
delmin = min(d["logP0-logP"])
plt.xlim(delmax*1.05,delmin)
plt.xlabel("$\\Delta$")
plt.ylabel("$\\sum_{x\\in\mathcal{D}(f)}P(x)$")
plt.savefig("logP0-logP_cumprob_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
c=1
plt.plot([delmax,delmin],[2**(-delmax+c),2**(-delmin+c)])

d["KInMax"].min()
plt.hist(d["KInMax"])

# plt.scatter()



### FREQUENCY - RANK PLOT
freqs = d.sort_values(by="freq", ascending=False)["freq"]

N = len(freqs)
plt.plot(range(1,len(freqs)+1),freqs/len(freqs))
plt.yscale("log")
plt.xscale("log")
A = 1/np.log(N)
plt.plot([1,N],[A/1,A/N])

d.dtypes

outs = list(d[d["freq"]==1].sort_values(by="Kout").head(17)["out"])
ins = list(d[d["freq"]==1].sort_values(by="Kout").head(17)["minIn"])
outs
ins

#convert geno bitstring to weight (+ bias) vector of perceptron.
# i=0
# x = np.array([int(b) for b in ins[i]])
# x=x.reshape(disc_bits,n+1,order='F').T
# x = np.matmul(x,np.array([[1],[2]]))
# shift = (2**disc_bits-1)/2
# x = (x-shift)/shift
# x

'''MAIN PLOTS'''

d = d.sort_values(by="KInMax",ascending=False)
d1b = d.groupby(["Kout","freq","KInMax"],as_index=False).min()
d1b = d1b.sort_values(by="KInMax",ascending=False)
d1 = d.groupby(["Kout","freq"],as_index=False).min()
d1 = d1.sort_values(by="KInMax",ascending=False)

d1 = d.groupby(["Kout","freq"],as_index=False).mean()
d2 = d.groupby(["Kout-KInMax+n","freq"],as_index=False).mean()
d3 = d.groupby(["KIMin-KInMax","freq"],as_index=False).mean()
d4 = d.groupby(["n-KInMax","logP0-logP"],as_index=False).mean()
d4 = d.groupby(["KInMean","logP0-logP"],as_index=False).mean()
d4 = d.groupby(["Kout","logP0-logP"],as_index=False).mean()

d1.plot.scatter("Kout","prob",s=3,c="KInMax",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMax_largeKInMaxlast_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")

# d.head(1000000)
%matplotlib
len(d)
d1.plot.scatter("Kout","prob",s=3,c="KInMax",colormap='viridis',logy=True)
d1.plot.scatter("Kout","P0",s=7,c="KInMax",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="KInMean",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMean_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="KInMin",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="KIMin-KInMax",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMax-KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="Kout-KInMin",colormap='viridis',logy=True)
plt.savefig("Kout_freq_Kout-KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="Kout-KInMax+n",colormap='viridis',logy=True)
plt.savefig("Kout_freq_Kout-KInMax+n_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d2.plot.scatter("Kout-KInMax+n","freq",s=7,c="Kout",colormap='viridis',logy=True)
plt.savefig("Kout-KInMax+n_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d2.plot.scatter("KInMax-Kout-n","freq",s=7,c="Kout",colormap='viridis',logy=True)
plt.savefig("KInMax-Kout-n_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d3.plot.scatter("KIMin-KInMax","freq",s=7,c="Kout",colormap='viridis',logy=True)
plt.savefig("KIMin-KInMax_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
plt.savefig("logP0-logP_n-KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d4.plot.scatter("n-KInMax","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])

d1["n-KInMax"] = nI - d1["KInMax"]
d1.plot.scatter("n-KInMax","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
plt.savefig("logP0-logP_mean_n-KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
# d4.plot.scatter("Kout","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
d4.plot.scatter("KInMean","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
d4.plot.scatter("Kout","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])

import matplotlib.pyplot as plt

d1 = d.groupby(["Kout","freq"],as_index=False).mean()
plt.scatter(d1["Kout"],d1["prob"])
plt.scatter(d1["Kout"],d1["P0"])
plt.yscale("log")
plt.ylim([1e-8,1])

plt.hist2d(d["n-KInMax"],d["logP0-logP"],bins=50)
# plt.scatter(d["Kout"],d["freq"],c=d["KInMean"])
# plt.scatter(dhead["Kout"],dhead["freq"],c=dhead["KInMax"])
# plt.yscale("log")
# plt.xscale("linear")

import seaborn as sns

# sns.set(style="whitegrid")
ax = sns.violinplot(x=d["n-KInMax"],y=d["logP0-logP"])
# import numpy as np

# plt.hist2d(d.head(10000)["Kout"],np.log(d.head(10000)["freq"]),bins=(50, 50),weights=)#,c=d["KInMean"])
