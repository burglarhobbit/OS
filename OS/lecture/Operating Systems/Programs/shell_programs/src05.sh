IFS="|"
while echo "\n Enter Department Code : \c"
do
	read dcode
	set -- `grep "^$dcode" << limit
01|accounts|16213
02|admin|5364
03|mktg|2309
limit`
	case $# in
	3) echo "Department Name : $2\n Empno of HOD : $3"
		shift 3;;
	*) echo "Invalid Code"; continue
	esac
done
