for file in `cat fillst.txt`
do
	file $file > l_v
	if grep "	executable" < l_v
	then
	echo $file 
	fi
done
