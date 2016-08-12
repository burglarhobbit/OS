overwrite()
{
  while echo "Enter the output filename : \c" 1>&2
  do
		read filename		# variable used by all programs
		filename=${filename:-default.lst}	# use file default.lst by default
		if [ -f $filename ]
		then
			while echo "File $filename exists Overwrite? :\c" 1>&2
			do
				read answer
				case $answer in
					y|Y) >$filename; echo $filename; break 2;;
					n|N) continue 2;;
					  *) echo "Enter a y or n" 1>&2;;
				esac
			done
		else
			echo $filename
			break
		fi
	done
}
