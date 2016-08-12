echo "\n Enter the pattern to be searched : \c"
read pname
echo "\n Enter the file name to be searched : \c"
read fname
echo "\n Searching for $pname from file $fname \n"
grep "$pname" $fname
echo "\n selected records shown above "
