#!/bin/awk -f
BEGIN {s="";cum=0}
{
    if ($1 != s) {
        if (NR!=1) {print s,cum};
        s=$1; cum=$2
    } else { 
        cum+=$2
    }
    #i=(i+1)%3
}
END { print s,cum }

