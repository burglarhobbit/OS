#! /bin/sh
#-- To display directory list in following format
#--
#--  file   size in k   date  protection   owner
clear
printf "%-30s\t%-8s  %-14s  %-10s  %-8s\n" Filename "Size(KB)" Date-Time Protection Owner 
dash_ln="--------------------------------------------------------------------------------"
printf "%-80s" $dash_ln
set `ls -l`
#To ignore the first line of output of ls -l command
shift 2
while true
do
	fl_sz=$5
	if [ fl_sz > 1023 ]
	then
		fl_sz_kb=`expr $fl_sz / 1024`
	else
		fl_sz_kb=`expr $fl_sz_kb = 0`
	fi
	fl_sz_kb=`expr $fl_sz_kb + 1`
#output can be displayed using echo command also as under
#echo "$9 \t \t $fl_sz_kb \t $6 \t $7 \t $8 \t $1 \t $3"
#Though printf is much more preferable command to display output with formats
	printf "%-30s\t%8d  %3s, %2d, %5s  %-10s  %-8s\n" $9 $fl_sz_kb $6 $7 $8 $1 $3
#To get next line parameters
	shift 9
#After last of ls -l command, no parameters can be obtained
#Hence to terminate the loop, check for null value
	if [ ! -n "$1" ]
	then
	break
	fi
done
