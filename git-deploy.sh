#!/bin/bash

git add .

git_status=$(git status --porcelain)
has_changes=$(echo $git_status| wc -l)

#echo $changed_files_count tiedostoa muuttunut.
#echo $git_status | wc -l

if [ $has_changes ]; then
	echo Komminoitavia muutoksia:
	echo $git_status
	echo
	echo Anna commit-viesti:
	read viesti

	print $viesti;

	git commit -am "$viesti"
else 
	Ei muutoksia.
fi

echo "Pusketaanko? (k/e)"
read pusketaanko

if [ $pusketaanko = "k" ]; then
	read -p "Lahde: [origin]: " lahde
	lahde=${lade:-origin}
	git push $lahde master
fi

