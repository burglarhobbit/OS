#To delete files with confirmation
#Written by Sanjay Chaudhary
echo "Enter the filename(s) to be renamed"
read filename
echo 'Enter the destination for file(s) to be moved : '
read dest 
mv -i $filename $dest
