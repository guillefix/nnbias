#!/users/guillefix/anaconda3/bin/python3
import numpy as np
import sys
tot=0
for line in sys.stdin:
    N=int(line)
    try:
        idxs = np.random.choice(range(N),size=20,replace=False)
        idxs = sorted(idxs)
        for idx in idxs:
            print(tot+idx)
        tot+=N
    except:
        tot+=N
