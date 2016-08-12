`script -a script.log`
if $? = 0
then
ls -la
ps -a
df -k
fi
exit
