overwrite()
{
  while echo "Enter the output filename : \c" 1>&2
  do
	read filename
	filename=${filename:-default.lst}
	if [ -f $filename ]
	then
	   while echo "File $filename exists overwrite? : \c" 1>&2
	   do
		 read answer
		 case $answer in
			y|Y) >$filename; echo $filename; break 2;;
			n|N) continue 2;;
			  *) echo "Enter yY or Nn" 1>&2;;
		 esac
	   done
	else
	   echo $filename
	   break
	fi
   done
}

