#! /bin/sh
# This script is written by Sanjay Chaudhary, Oasis Systems for ITD
# Date written May, 15, 2000
# This script will generate iostat results and will be stored in /usr/local/iostatlogs
# This scripts is to be executed as a part of cron every half and hour

TZ=US/Eastern
export TZ

MONTH=`date +%m`
YEAR=`date +%y`
DATE=`date +%d`
HOUR=`date +%H`
MINUTE=`date +%M`

echo "At the time : $MONTH-$DATE-$YEAR-$HOUR-$MINUTE" > /usr/local/iostatlogs/$MONTH-$DATE-$YEAR-$HOUR-$MINUTE
iostat >> /usr/local/iostatlogs/$MONTH-$DATE-$YEAR-$HOUR-$MINUTE

