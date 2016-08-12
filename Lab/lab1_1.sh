# Lab Assignment 1
# Owner: Bhavya Patwa

while true
do
    echo -n "1. Delete\n2. Copy\n3. Rename\n4. Exit\nSelect one of the following: "
    read option

    if [ $option = 1 ]; then
        read -p "Enter the file name to be deleted: " filename
        rm -vi $filename
    elif [ $option = 2 ]; then
        read -p "Enter the source file/folder name to be copied: " filenamecopy
	read -p "Enter the destination file/folder name to be pasted to: " filenamepaste
	cp -vi $filenamecopy $filenamepaste
    elif [ $option = 3 ]; then
        read -p "Enter the source file name to be renamed: " filename
        read -p "Enter the new filename: " newfilename
        mv -i $filename $newfilename
    elif [ $option = 4 ]; then
        exit
    fi
done
