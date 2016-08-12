# Examples of file processing
# To assign filr handle 7 to input file
echo 'Enter name of input file : \c'
read in_file
if [ ! -r $in_file ]
then
	echo 'File is not existing or not readable file'
	exit
fi
echo 'Enter name of output file : \c'
read out_file
exec 7<$in_file
# To assign file handle 9 to output file myreport.rpt
exec 9>$out_file
while read rec 0<&7
do
	echo "$rec"
	echo "$rec" 1>&9
done

#The Other way to do the same job
#echo 'Enter name of input file : \c'
#read in_file
#if [ -r $in_file ]
#then
#	echo 'Enter name of output file : \c'
#	read out_file
#	exec 7<$in_file
# To assign file handle 9 to output file myreport.rpt
#	exec 9>$out_file
#	while read rec 0<&7
#	do
#		echo $rec
#		echo $rec 1>&9
#	done
