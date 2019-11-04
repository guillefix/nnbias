#!/users/guillefix/anaconda3/bin/python3
import numpy as np
import sys
num_inputs = int(sys.argv[1])
i=0
output = ""
lines = []
for line in sys.stdin:
    #print(line)
    linearr = line.split("\t")
    this_output = linearr[1].strip()
    if this_output != output:
        #if len(lines)>=5:
        if len(lines)!=i and i<100:
            break
        if i>=5:
            for ll in lines:
                print(ll+" "+str(i))
        #if output == 123*"0"+5*"1":
        #    print(len(lines),i)
        #    break
        output = this_output
        lines = []
        i = 0
    i+=1
    if i <=num_inputs:
        #print(line)
        lines.append(line[:-1])
