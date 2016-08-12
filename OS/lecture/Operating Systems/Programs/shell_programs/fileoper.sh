#Script to perform file operations, like copy, delete, rename
while true
do
clear
cat << MENU

	Menu

	C) Copy file(s)
	
	D) Delete file(s)

	R) Rename file(s)

	E) Exit

MENU
echo 'Enter your Choice :\c'
read choice

case $choice in
	[cC]) sh /export/home/faculty/sanjay/shell/filecopy.sh
		sleep 5
  	        continue;;

	[dD]) sh /export/home/sanjay/shell/filedel.sh
		sleep 5
	   	continue;;
	[rR]) sh /export/home/sanjay/shell/fileren.sh
		sleep 5
	        continue;;

	[eE]) exit;;

	*) echo '\nPlease enter proper choice' 
		sleep 5
esac
done
