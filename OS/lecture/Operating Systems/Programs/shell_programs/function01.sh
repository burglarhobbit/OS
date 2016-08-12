trap 'echo "Program interrupted" ; exit' 1 2 15
. mainfunc.sh 		# load the function definitions
flname=`overwrite`	# invoke the overwrite function
while echo "Designation Code : \c" 1>&2
do
	read desig 
	case "$desig" in
	[0-9][0-9])	grep "^$desig" $flname > /dev/null &&
				{ echo "Code exists" 1>&2 ; continue
				} ;;
	         *) echo "Invalid code"  1>&2 ; continue ;;
	esac
 	while echo "Description    :\c" 1>&2
	do
		read desc
		if [ `expr "$desc" : '.*'` gt 15 ]
		then
			echo "Maximum 15 characters permitted" 1>&2; continue
		else
			case "$desc" in
			[!\ a-zA-Z]*)	echo "Only alphabets & spaces permited" 1>&2
							continue ;;
				      "")	echo "Description not entered" 1>&2
							continue ;;
				       *)   echo "$desig | $desc" ; break
			esac
		fi
	done
	anymore "Wish to continue" 1>&2 || break
done > flname
echo "Program terminated"

# The major drawback of this script is that it uses too many of these
# 1>&2 symbols, which doesn't really make life easy for the application
# developer.
