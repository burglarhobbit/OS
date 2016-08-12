find /etc -print > src01.txt
for file in `cat src01.txt`
do
   file $file > t1
   if  grep "	executable" < t1 >> rak.era 
   then
      cp $file /export/home/sanjay/etcshell
    fi
done
