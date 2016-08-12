#! /bin/sh
# This script is written by Sanjay Chaudhary, Oasis Systems Inc.
# This script is written to process reports for all agencies
# This script is to be executed as a part of cron

TZ=US/Eastern
export TZ
PATH=/nms/CSCOpx/lib/jre1.1.8/bin:/usr/sbin:/usr/bin:/usr/ucb:/etc:/nms/OV/bin:/nms/OV/pdn/OpenLane:
/opt/netscape:/usr/local/bin:/opt/CSCOpx/bin:/nms/CSCOtd5/bin:.
export PATH

MONTH=`date +%m`
YEAR=`date +%Y`
DATE=`date +%d`
RPT_DT=$MONTH/$DATE/$YEAR
export RPT_DT

cd /nms/OV/pdn/OpenLane
./ProcessReports -date $RPT_DT&
echo $RPT_DT >> /usr/local/sanjay/run_dt
unset RPT_DT
