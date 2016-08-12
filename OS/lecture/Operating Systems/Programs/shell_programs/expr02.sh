stg=javavirtualmachine
expr "$stg" : '......\(..\)'
#It will print rt
expr "$stg" : '.\{6\}\(..\)'
# It will print rt 
# It is same as substr(stg,7,2)
# If you want to locate the position of the character d from the string
# stg, then all you have to do is count the number of characters which
# are not d ( indicated by reg.exp., [^d]* ) followed by a d:
#
expr "$stg" : '[^m]*m'
# It will print 12 




