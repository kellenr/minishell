#/bin/bash

inotifywait -r -m -e modify,create --format '%w%f' . |
while read -r file; do
	if [[ "$file" =~ \.([ch])$ ]]; then
		echo "Detected change in $file. Running command..."
		norminette $file
	fi
done
