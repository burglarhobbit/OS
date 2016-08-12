#Script written by Sanjay Chaudhary
#This script will read IP address of each node from /etc/hosts file
#Then it will ping each node to check whether node is working or not
exec 5</etc/hosts
while read ip_adr nodename alias 0<&5
do
if [ $ip_adr != "#" ]
then
	ping $ip_adr > /dev/null
		if [ $? = 1 ] 
		then
		msg="$nodename not reachable at : `date`"
		echo "$msg \n"
		echo
		fi
fi
done
