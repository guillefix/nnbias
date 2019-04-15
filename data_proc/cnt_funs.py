
import sys
from collections import Counter

N = int(sys.argv[1])

cnt = Counter()

for i in range(N):
	with open("0_"+str(i)+"_full_sample_net_0hl.txt","r") as f:
		for line in f:
			cnt[line.strip()] += 1

with open("full_sample_0hl.txt","w") as f:
	for fun,freq in cnt.most_common():
		f.write(fun+"\t"+str(freq)+"\n")
