echo $*
echo 'Enter the destination : \c'
read dest
if [ ! -x $dest ]
then
echo 'Invalid destination'
exit
fi
for fl_nm in "$@"
do
	cp -i $fl_nm $dest
done
