from math import log
#import numpy as np
####################

import os
import sys
from collections import Counter
filenames = sys.argv[1:]

import time

start_time = time.time()


# os.environ["SPARK_HOME"] = "/usr/local/Cellar/apache-spark/1.5.1/"
# os.environ["PYSPARK_PYTHON"]="/usr/bin/python3"
# os.environ["PYSPARK_DRIVER_PYTHON"]="/usr/bin/python3"

os.environ["PYSPARK_PYTHON"]="/usr/local/shared/python/3.6.3/bin/python3"
os.environ["PYSPARK_DRIVER_PYTHON"]="/usr/local/shared/python/3.6.3/bin/python3"

from pyspark import SparkContext
sc = SparkContext.getOrCreate()
print(sc._jsc.sc().getExecutorMemoryStatus())
print(sc)
print("Ready to go!")

#data = sc.emptyRDD()
#for filename in filenames:
#    data += sc.textFile(filename) #returns an rdd
data = sc.textFile(filename)

#data = data.map(Counter).reduce(lambda x, y: x + y)

data = data.map(lambda x: x.split("\t"))

data = data.zipWithIndex()

data = data.filter(lambda x: x[1][0] == 128*"0" or x[1][1] == 129*"1")

data = data.map(lambda x: x[0]).collect()

print(data)

#with open("full_sample_2hl.txt","w") as f:
#    for fun,freq in data.most_common():
#            f.write(fun+"\t"+str(freq)+"\n")

print("--- %s seconds ---" % (time.time() - start_time))

