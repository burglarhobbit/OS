#-- Redirecting error of find to device null through exec
#
echo "Enter filename : \c"
read filename
exec 2>/dev/null
find /  -name $filename  -print >opt
cat opt
rm opt
