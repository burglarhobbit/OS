:
# @(#) Examples of set 
no=0
for fl_nm in `ls`
do
	no=`expr $no + 1`	
	echo "File Number $no is : " $fl_nm 
done
no=0
set `ls -la`
for true
do
	no=`expr $no + 1`	
	echo "File Number $no is : " $1 
	shift
done
