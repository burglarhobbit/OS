#! /bin/sh
# This scripts is written by Sanjay Chaudhary, Oasis Systems
# This script will read names of each solaris server from solaris_servs file
# Then it will make backup copy of /etc/hosts file on each server with timestamp
# Then it will copy /etc/hosts file of behemoth onto each server
# Pre-requisite : following entry in /.rhosts file of each server :
# behemoth root

in_file="solaris_servs"
if [ ! -r $in_file ]
then
	echo 'File : solaris_servs is not existing or not a readable file !!!'
	exit
fi
MONTH=`date +%m`
YEAR=`date +%y`
DATE=`date +%d`
HOUR=`date +%H`
MINUTE=`date +%M`
REPL_DT=$MONTH-$DATE-$YEAR-$HOUR-$MINUTE
exec 7<$in_file
while read rec 0<&7
do
	echo "$rec"
	rsh $rec cp /data2/export/home/sanjay/hosts /data2/export/home/sanjay/hosts.$REPL_DT
	rcp -p /etc/inet/hosts $rec:/data2/export/home/sanjay
done
