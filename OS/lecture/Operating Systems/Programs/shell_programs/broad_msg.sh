#-- To broadcast message to logged on users
for username in `who -q`
do
 write $username < msg_file
done
