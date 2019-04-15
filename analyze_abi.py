import numpy as np
# import pandas as pd
# import os

# os.system('scp $hydra:~/bias/nn_bias/bias_cpp/big_sample/* ABI/')


# comp=49.0

# for comp in [38.5, 45.5, 49.0, 52.5, 56.0, 59.5, 63.0]:
#     for i in range(20):
#         with open("ABI/"+str(comp)+"/0_"+str(i)+"_"+str(comp)+"_abi_sample_net.txt", "r") as f:

# np.mean(gen_accsss[4])

gen_accsss = []
# funsss = []
abi_comps = [38.5, 45.5, 56.0, 59.5, 63.0, 70.0, 66.5]
# abi_comps = [7.0, 17.5, 24.5, 21.0, 28.0, 31.5, 35.0, 42.0, 38.5, 45.5, 49.0, 52.5, 56.0, 59.5, 63.0]
for comp in abi_comps:
    print(comp)
    # for comp in [63.0]:
    # training_sets = []
    gen_accss = []
    # funss = []
    for i in range(250):
        # print(i)
        filename = "0_"+str(i)+"_"+str(comp)+"_abi_sample_net_2hl.txt"
        with open(filename, "r") as f:
            j = 0
            gen_accs = []
            funs = []
            for line in f:
                if j == 0:
                    # training_sets.append(line[1:-1])
                    pass
                elif j == 1:
                    pass
                else:
                    # print(i)
                    linearr = line.split("\t")
                    fun = linearr[0]
                    # funs.append(fun)
                    genacc = linearr[1]
                    gen_accs.append(2*float(genacc[:-1]))
                    #the generrors need to be multiplied by 2 as they are not off-sample
                j+=1
        gen_accss.append(gen_accs)
        # funss.append(funs)
    gen_accsss.append(sum(gen_accss,[]))
    # funsss.append(

# gen_accsss[-1] = sum(gen_accss,[])

len(gen_accsss)
len(abi_comps)

# training_sets
# gen_accss
# funss

'''advSGD results'''

import pickle
path = "learning/7_40_40_1/"

funs = []
fun_comps = []
with open(path+"funs.txt","r") as f:
    for line in f:
        linearr = line.split("\t")
        funs.append(linearr[0])
        fun_comps.append(float(linearr[1]))

generalization_errors = pickle.load(open(path+"generalization_errors.p","rb"))

abi_gen_errors = []
for comp in fun_comps:
    if comp in abi_comps:
        abi_gen_errors.append(gen_accsss[abi_comps.index(comp)])
    else:
        abi_gen_errors.append([])

gen_accsss[abi_comps.index(49.0)]

# abi_gen_errors[0]

import imp
import plots
imp.reload(plots)
from plots import shaded_std_plot_double_scatter,shaded_std_plot, shaded_std_plot_double

shaded_std_plot_double(fun_comps,generalization_errors,fun_comps,abi_gen_errors,"ABI_vs_advSGD_generror_vs_comp"+".png","Target function LZ complexity", "Generalization error")

# 00000000100000000000000010100000000000000000000000000000000000000000000010100000000000001011000000000000000000000000000000000000 63.0

np.mean(sum(gen_accss,[]))
np.std(sum(gen_accss,[]))

len(sum(gen_accss,[]))
