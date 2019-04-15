
import sys
from collections import Counter
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()
print(rank)
# num_inits_per_task = 1
prefix = sys.argv[1]
files = sys.argv[2:]
num_tasks = len(files)
first_task = 0

num_tasks_per_job = num_tasks//size
tasks = list(range(first_task+rank*num_tasks_per_job,first_task+(rank+1)*num_tasks_per_job))

if rank < num_tasks%size:
    tasks.append(size*num_tasks_per_job+rank)


#i = int(sys.argv[1])

cnt = Counter()

import time

start_time = time.time()

for i in tasks:
    with open(files[i],"r") as f:
            for line in f:
                    linearr = line.split("\t")
                    cnt[linearr[0]] += int(linearr[1])

if rank == 0:
    #bigcnt = Counter()
    #comm.Reduce(cnt,bigcnt,root=0,op=MPI.SUM)
    with open(prefix+"_"+str(rank)+"_full_sample_2hl.txt","w") as f:
            for fun,freq in cnt.items():
                    f.write(fun+"\t"+str(freq)+"\n")

    print("--- %s seconds ---" % (time.time() - start_time))

