#   To copy files with confirmation
#   Written by Sanjay Chaudhary
fcopy()
{
	echo 'Enter the filename(s) to be copied'
	read filename
	echo 'Enter the destination for file(s) to be copied : '
	read dest 
	cp -i $filename $dest
}
#   To rename files with confirmation
#   Written by Sanjay Chaudhary
fren()
{
	echo "Enter the filename(s) to be renamed"
	read filename
	echo 'Enter the destination for file(s) to be moved : '
	read dest 
	mv -i $filename $dest
}
#   To delete files with confirmation
#   Written by Sanjay Chaudhary
fdel()
{
        echo 'your choice is '  $choice	
	echo 'Enter the filename(s) to be deleted'
	read filename
	rm -i $filename
}
