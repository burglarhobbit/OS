cat << END

			MENU

		1. List of files
		2. Processes of user
		3. Today's date
		4. Users of system
		5. Quit to UNIX
END
echo " Enter Your Option : \c"
read choice
echo
case "$choice" in
	1)	ls -l ;;
	2)	ps -f ;;
	3)	date  ;;
	4)	who   ;;
	5)	exit  ;;
esac
