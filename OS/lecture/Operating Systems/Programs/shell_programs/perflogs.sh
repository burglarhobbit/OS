#! /bin/sh
# This script is written by Sanjay Chaudhary, 
# Date written
# This script will generate iostat, vmstat and sar results and
# will be stored in /usr/local/perflogs
# This scripts is to be executed as a part of cron every half and hour

TZ=US/Eastern
export TZ

MONTH=`date +%m`
YEAR=`date +%y`
DATE=`date +%d`
HOUR=`date +%H`
MINUTE=`date +%M`

echo >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo "At the time : $MONTH-$DATE-$YEAR-$HOUR-$MINUTE" >> /export/home/faculty/sanjay/log
echo "The output of iostat is as under :" >> /export/home/faculty/sanjay/log
iostat 5 5 >> /export/home/faculty/sanjay/log
echo "The output of vmstat is as under :" >> /export/home/faculty/sanjay/log
vmstat 5 5 >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo "The output of sar is as under :" >> /export/home/faculty/sanjay/log
sar 5 5 >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo "The output of mpstat is as under :" >> /export/home/faculty/sanjay/log
mpstat 5 5 >> /export/home/faculty/sanjay/log
echo >> /export/home/faculty/sanjay/log
echo "--------------------------------------" >> /export/home/faculty/sanjay/log
