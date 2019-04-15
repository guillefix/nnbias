
import sys
from collections import Counter
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
print(rank)
# num_inits_per_task = 1
first_task = int(sys.argv[1])
num_tasks = int(sys.argv[2])

num_tasks_per_job = num_tasks//size
tasks = list(range(first_task+rank*num_tasks_per_job,first_task+(rank+1)*num_tasks_per_job))

if rank < num_tasks%size:
    tasks.append(size*num_tasks_per_job+rank)


#i = int(sys.argv[1])

cnt = Counter()

import time

start_time = time.time()

for i in tasks:
    with open("sampled_funs/1_"+str(i)+"_full_sample_net_2hl.txt","r") as f:
            for line in f:
                    cnt[line.strip()] += 1


with open(str(first_task)+"_"+str(rank)+"_full_sample_2hl.txt","w") as f:
	for fun,freq in cnt.most_common():
		f.write(fun+"\t"+str(freq)+"\n")

print("--- %s seconds ---" % (time.time() - start_time))

