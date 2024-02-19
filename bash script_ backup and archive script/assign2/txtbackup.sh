#1
#! /bin/bash
#name: yantian yin
#student_id:261143026
#2
echo $(pwd)
ls *.txt
#3
mkdir backup
cd backup
echo "Moved to backup directory"
echo $(pwd)
#4
cp ../*.txt .
echo "Copied all text files to backup directory"
#5
echo "Current backup:" > date.txt
echo $(date) >> date.txt
cat date.txt
#6
tar -czvf txtarchive.tgz *.txt
echo "Created archive txtarchive.tgz"
ls -l
