fname=result.txt
for pattern in "$@"
do
	grep "$pattern" input.txt || echo "Pattern $pattern not found" 1>&2
done > $fname
