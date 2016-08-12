while echo "Enter you name : \c " 1>&2
do
	read name
	if [ `expr "$name" : '.*'` -gt 20 ]
	then
		echo "Name too long" 1>&2
	else
		break
    fi
done
echo "$name"
