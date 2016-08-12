#Script is written by Sanjay Chaudhary
#This shell scripts mergers files from two directories into one
#In case of common it will copy last modified file
printf "Enter the name of first directory with complete path : \n"
read dir_1
#Check whether the directory is existing or not
printf "Enter the name of second directory with complete path : \n"
read dir_2
#Check whether the itemporary file is existing or not
if [ -f merge_dirs.dat ]
then
rm merge_dirs.dat
fi
set `ls -lt $dir_1`
#To ignore the first line of output of ls -l command
shift 2
slash=/
while true
do
fl_nm=$dir_1$slash$9
	if [ -f $fl_nm ]
	then
	printf "%-30s\t%-3s\t%2s\t%-5s\t%-55s\n" $9 $6 $7 $8 $dir_1 >> merge_dirs.dat
#       printf "%-30s\t%-3s\t%2s\t%-5s\t%-55s\n" $9 $6 $7 $8 $dir_1
	fi
#To get next line parameters
	shift 9
#After last of ls -l command, no parameters can be obtained
#Hence to terminate the loop, check for null value
	if [ ! -n "$1" ]
	then
	break
	fi
done
set `ls -lt $dir_2`
#To ignore the first line of output of ls -l command
shift 2
slash=/
while true
do
fl_nm=$dir_2$slash$9
	if [ -f $fl_nm ]
	then
	printf "%-30s\t%-3s\t%2s\t%-5s\t%-55s\n" $9 $6 $7 $8 $dir_2 >> merge_dirs.dat
#       printf "%-30s\t%-3s\t%2s\t%-5s\t%-55s\n" $9 $6 $7 $8 $dir_2
	fi
#To get next line parameters
	shift 9
#After last of ls -l command, no parameters can be obtained
#Hence to terminate the loop, check for null value
	if [ ! -n "$1" ]
	then
	break
	fi
done
#Now refer mrgdir02.sh for further operations
