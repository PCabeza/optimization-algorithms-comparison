#! /bin/bash
# this script processes the csv to print it in a more readable way 
# (similar to column)

# call it as: ./bin/pcg | ./prettyprint.sh

awk '
BEGIN { FS = ";" } 
NF==1 {print} 
NF!=1 { for(i=1;i<=NF;++i) printf("%s   \t",$i); printf("\n") }'
