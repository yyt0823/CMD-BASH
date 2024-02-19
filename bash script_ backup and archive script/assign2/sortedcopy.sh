#! /bin/bash
#name: yantian yin
#student id: 261143026
#question 3 exit code 1(missing arguments)
if [ "$#" -ne 2 ];then
	echo "Error: Expected two input parameters."
	echo "Usage: $0 <sourcedirectory> <targetdirectory>"
	exit 1
fi

#question 4 exit code 2(input parameter not directory)
if [ ! -d "$1" ];then
	echo "Error: Input parameter #1 '$1' is not a directory."
	echo "Usage: $0 <sourcedirectory> <targetdirectory>"
	exit 2
fi


#question 5 exit code 3(dir already exist)
if [ -e "$2" ];then
	echo "Directory 'sorted_dir' already exists. Overwrite? (y/n)"
	read input
	if [ "$input" = "y" ];then
		rm -r "$2"
		mkdir "$2"
	else
		exit 3
	fi
fi

#main
#creat dir
if [ ! -e "$2" ];then 
	mkdir "$2"
fi
#set counter
counter=1
#sort file in reverse order cancatenate counter and file and cp to target directory
for file in $(ls "$1" | sort -r);do
	if [ -f "$1/$file" ];then
		cp "$1/$file" "$2/$counter.$file"
		#update counter
		counter=$((counter + 1))
	fi
done
