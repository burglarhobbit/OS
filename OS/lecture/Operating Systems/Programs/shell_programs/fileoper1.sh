#Script to perform file operations, like copy, delete, rename
. shell_lib.sh
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
	
	[cC])   fcopy
		sleep 2
  	        continue;;

	[dD])   fdel
		sleep 2
	   	continue;;

	[rR])   fren
		sleep 2
	        continue;;

	[eE])   exit;;

	*) echo '\nPlease enter proper choice' 
		sleep 2
esac
done
