IFS="|"
while echo "\n Enter Department Code : \c"
do
	read dcode
	set -- `grep "^$dcode" limit`
	case $# in
	3) echo "Department Name : $2\n Empno of HOD : $3"
		shift 3;;
	*) echo "Invalid Code"; continue
	esac
done
