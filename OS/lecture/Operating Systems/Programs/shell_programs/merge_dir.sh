#--- To copy files from two directories & to keep latest common files in
#--- third directory.
echo "Enter Source Directory 1 : \c"
read dir1 
echo "Enter Source Directory 2 : \c"
read dir2 
echo "Enter Target Directory   : \c"
read dir3
ls -ltc $dir1 >  flist.era
ls -ltc $dir2 >> flist.era
sort  
 
