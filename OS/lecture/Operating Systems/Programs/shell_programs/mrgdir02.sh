#In continuation with mrgdir01.sh
sort -o merge_dirs01.srt merge_dirs.dat
exec 5<merge_dirs01.srt
if [ -f merge_dirs02.srt ]
then
rm merge_dirs02.srt
fi
while read fl mon dt tm dir 0<&5
do
if [ $mon = "Jan" ]
then
mno='01'
elif [ $mon = "Feb" ]
then
mno="02"
elif [ $mon = "Mar" ]
then
mno="03"
elif [ $mon = "Apr" ]
then
mno="04"
elif [ $mon = "May" ]
then
mno="05"
elif [ $mon = "Jun" ]
then
mno="06"
elif [ $mon = "Jul" ]
then
mno="07"
elif [ $mon = "Aug" ]
then
mno="08"
elif [ $mon = "Sep" ]
then
mno="09"
elif [ $mon = "Oct" ]
then
mno="10"
elif [ $mon = "Nov" ]
then
mno="11"
elif [ $mon = "Dec" ]
then
mno="12"
fi
#echo $mno
if [ $dt = 1 ]
then
dt=01
elif [ $dt = 2 ]
then
dt=02
elif [ $dt = 3 ]
then
dt=03
elif [ $dt = 4 ]
then
dt=04
elif [ $dt = 5 ]
then
dt=05
elif [ $dt = 6 ]
then
dt=06
elif [ $dt = 7 ]
then
dt=07
elif [ $dt = 8 ]
then
dt=08
elif [ $dt = 9 ]
then
dt=09
fi
#echo $dt
echo $tm > grep_fl
if grep : grep_fl>/dev/null
then
year=2001
tm_fl=$year$mno$dt$tm
else
year=$tm
tm_fl=$year$mno$dt
fi
#echo $tm_fl
printf "%-55s\t%-30s\t%13s\n" $dir $fl $tm_fl >> merge_dirs02.srt
done
exec 7<merge_dirs02.srt
read dir fl tm_fl 0<&7
pr_dir=$dir
pr_fl=$fl
pr_tm_fl=$tm_fl
while read dir fl tm_fl 0<&7
do
if [ $fl = $pr_fl ]
then
	fl_path=$dir/$fl
	if [ $tm_fl > $pr_tm_fl ]
	then
	cp $fl_path backup
	elif [ $tm_fl = $pr_tm_fl ]
	then
	cp $fl_path backup
	else
	fl_path=$pr_dir/$pr_fl
	cp $fl_path backup
	fi
else
	fl_path=$pr_dir/$pr_fl
	cp $fl_path backup
fi
	pr_dir=$dir
	pr_fl=$fl
	pr_tm_fl=$tm_fl
done
fl_path=$pr_dir/$pr_fl
cp $fl_path backup
