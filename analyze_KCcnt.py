import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
%matplotlib

'''LOAD DATA'''
n = 7
disc_bits = 3
nI = disc_bits*(n+1)
d = pd.read_csv("results/KCcnt_"+str(disc_bits)+"_full_enum_discrete_weights_net_0hl.txt", header=None, names=["Kout","KInMin","KInMax","KInMean","freq"],delim_whitespace=True)
# d = pd.read_csv("KCcnt_plus_"+str(disc_bits)+"_full_enum_discrete_weights_net_0hl.txt", header=None, dtype={"out":"str","minIn":"str","maxIn":"str"}, names=["out","minIn","maxIn","Kout","KInMin","KInMax","KInMean","freq"],delim_whitespace=True)
d = d.sort_values(by="Kout",ascending=False)

# d["KIMin-KInMax"] = d["KInMax"] - d["KInMin"]
# d["Kout-KInMax+n"] = d["Kout"] - d["KInMax"] + nI
# d["KInMax-Kout-n"] = -d["Kout-KInMax+n"]
# d["Kout-KInMin"] = d["Kout"] - d["KInMin"]
# d["n-KInMax"] = nI - d["KInMax"]

## quantities using Kamal's normalized complexities, and also nicer LaTeX variables
nO = np.log2(len(d))
d["$K(x)$"] = nO*(d["Kout"] - d["Kout"].min())/(d["Kout"].max() - d["Kout"].min())
d["$K_{max}(p|x)$"] = nI*(d["KInMax"] - d["KInMax"].min())/(d["KInMax"].max() - d["KInMax"].min())
d["$K(x)-K_{max}(p|x) + n$"] = d["$K(x)$"] - d["$K_{max}(p|x)$"] + nI
##upper bound
a=0.13; b=3
# a=0.1; b=8
d["logP0-logP"] = -a*d["Kout"] - b - np.log2(d["freq"]) + nI
d["P0"] = 2**(-a*d["Kout"] - b)
d["prob"] = d["freq"]/sum(d["freq"])
d["$P(x)$"] = d["prob"]
#%%

### CUMULATIVE PROB VS DELTAP
# sum(d["prob"])
# d["prob"]
# d = d[d["prob"]<10**(-2)]
d = d.sort_values(by="logP0-logP",ascending=False)
d["cumprob"] = d["prob"].cumsum()
plt.axes([0.15, 0.1, .75, .8])
plt.plot(list(d["logP0-logP"]),list(d["cumprob"]),label="data")
plt.yscale("log")
delmax = max(d["logP0-logP"])
delmin = min(d["logP0-logP"])
plt.xlim(delmax*1.05,delmin)
plt.xlabel("$\\Delta$")
plt.ylabel("$\\sum_{x\\in\mathcal{D}(f)}P(x)$")
#%%
c=1
plt.plot([delmax,delmin],[2**(-delmax+c),2**(-delmin+c)], c="red", label="Prediction")
# cumprobs = np.array(sorted(d["cumprob"]))
index = d[d["cumprob"] >= 0.1]["cumprob"].index[0]
xval=d.loc[index]["logP0-logP"]
yval=d.loc[index]["cumprob"]
plt.plot([max(d["logP0-logP"]),xval],[yval,yval], "--", c="green", label="10% line")
plt.plot([xval,xval],[min(d["cumprob"]),yval], "--", c="green")
plt.legend()
#%%
# plt.savefig("logP0-logP_cumprob_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
plt.savefig("cumprob_perceptron.png")


# d["KInMax"].min()
# plt.hist(d["KInMax"])

#%%

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

#%%

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

# d1 = d.groupby(["Kout","freq"],as_index=False).mean()
d1 = d.groupby(["$K(x)$","$P(x)$"],as_index=False).mean()
# d2 = d.groupby(["Kout-KInMax+n","freq"],as_index=False).mean()
d2 = d.groupby(["$K(x)-K_{max}(p) + n$","$P(x)$"],as_index=False).mean()
d2.to_csv("normalized_Kout-KInMax+n_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.csv")
d3 = d.groupby(["KIMin-KInMax","freq"],as_index=False).mean()
d4 = d.groupby(["n-KInMax","logP0-logP"],as_index=False).mean()
d4 = d.groupby(["KInMean","logP0-logP"],as_index=False).mean()
d4 = d.groupby(["Kout","logP0-logP"],as_index=False).mean()
d5= d.groupby(["Kout","KInMin"],as_index=False).mean()

d1.plot.scatter("Kout","prob",s=3,c="KInMax",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMax_largeKInMaxlast_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")

# d.head(1000000)
d5.plot.scatter("Kout","KInMin",s=3,c="freq",colormap='viridis')
plt.savefig("Kout_KInMean_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")

%matplotlib
# import matplotlib
# font = {'family' : 'normal',
#         'weight' : 'normal',
#         'size'   : 12}
#
# matplotlib.rc('font', **font)
len(d1)
# d1.plot.scatter("Kout","prob",s=3,c="KInMax",colormap='viridis',logy=True)
ax = plt.gca()
d1.plot.line(x="$K(x)$",y="P0",c="black", ax=ax,logy=True, label="bound (fit)")
plt.xlim([-0.5, 23.5])
# plt.savefig("Kout_freq_KInMax_bound1_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
plt.savefig("K_P_perceptron.png")
# d1.plot.scatter("Kout","freq",s=7,c="KInMean",colormap='viridis',logy=True)
d1.plot.scatter("$K(x)$","$P(x)$",s=7,c="$K_{max}(p|x)$",colormap='viridis',logy=True)
plt.savefig("normalized_Kout_freq_KInMean_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="KInMin",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="KIMin-KInMax",colormap='viridis',logy=True)
plt.savefig("Kout_freq_KInMax-KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="Kout-KInMin",colormap='viridis',logy=True)
plt.savefig("Kout_freq_Kout-KInMin_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d1.plot.scatter("Kout","freq",s=7,c="Kout-KInMax+n",colormap='viridis',logy=True)
plt.savefig("Kout_freq_Kout-KInMax+n_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
# d2.plot.scatter("Kout-KInMax+n","freq",s=7,c="Kout",colormap='viridis',logy=True)
#%%
d2["Predict. (sum P)"] = 2**(-d2["$K(x)-K_{max}(p|x) + n$"])/sum(2**(-d["$K(x)-K_{max}(p|x) + n$"]))
d2["bound"] = 2**(-d2["$K(x)-K_{max}(p|x) + n$"])/sum(2**(-d2["$K(x)-K_{max}(p|x) + n$"]))/2**(12)
d2.plot.scatter("$K(x)-K_{max}(p|x) + n$","$P(x)$",s=7,c="$K_{max}(p|x)$",colormap='viridis',logy=True)
ax = plt.gca()
d2.plot.line("$K(x)-K_{max}(p|x) + n$","Predict. (sum P)", ax=ax, logy=True, c="orange", alpha=0.7, linewidth=3)
d2.plot.line("$K(x)-K_{max}(p|x) + n$","bound", ax=ax, logy=True, c="black", alpha=0.7, linewidth=3)
plt.ylim([10**(-7.5),10^(-1)])
plt.xlim([-0.5,40.5])
#%%
plt.savefig("normalized_with_bounds_Kout-KInMax+n_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d2.plot.scatter("KInMax-Kout-n","freq",s=7,c="Kout",colormap='viridis',logy=True)
plt.savefig("KInMax-Kout-n_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d3.plot.scatter("KIMin-KInMax","freq",s=7,c="Kout",colormap='viridis',logy=True)
plt.savefig("KIMin-KInMax_freq_Kout_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
plt.savefig("logP0-logP_n-KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
d4.plot.scatter("n-KInMax","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])

d4.to_csv("logP0-logP_n-KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.csv")

d1["n-KInMax"] = nI - d1["KInMax"]
d1.plot.scatter("n-KInMax","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
plt.savefig("logP0-logP_mean_n-KInMax_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
# d4.plot.scatter("Kout","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
d4.plot.scatter("KInMean","logP0-logP",s=7,c="Kout",colormap='viridis',logy=False)#,ylim=[min(d["logP0-logP"]),1])
plt.savefig("logP0-logP_n-KInMean_perceptron_"+str(n)+"_"+str(disc_bits)+"bitweights_bias_full_enum.png")
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
