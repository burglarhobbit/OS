trap 'echo abnormal key; continue' 1 2 15
echo `date | cut -f2,5 -d' '`
echo Today we are testing how echo command is going to display the lenthy line
echo "enter file name \c"
read fl_nm
set -- `cat $fl_nm | more`
if [ $? = 1 ]
then
echo file not found
fi
