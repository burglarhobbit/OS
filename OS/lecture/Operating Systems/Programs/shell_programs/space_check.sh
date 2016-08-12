#!/bin/sh
	df -kl | grep -iv filesystem | awk '{ print $5" used on "$6 } ' | while read line
	do
		echo $line
		PERC=`echo $line | cut -d"%" -f1 | awk '{ print $1 }'`
		if [ $PERC -gt 50 ]
		then
			echo "${PERC}% ALERT" | mailx -s "${line} of `hostname` : almost full" sanjay
		fi
	done
