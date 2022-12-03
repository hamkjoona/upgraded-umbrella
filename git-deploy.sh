#!/bin/bash

git add .

git_status=$(git status --porcelain)
changed_files_count=$(git status --porcelain| wc -l)

echo $changed_files_count tiedostoa muuttunut.
#echo $git_status | wc -l

if [ $changed_files_count > 0 ]; then
	echo $git_status
	echo Komminoidaan ylläolevat tiedostot.
	echo Anna commit-viesti:
	read viesti

	print $viesti;

	git commit -am '$viesti'
else 
	print ää
fi

echo "Pusketaanko? (k/e)"
read pusketaanko

if [ $pusketaanko = "k" ]; then
	read -p "Lahde: [origin]: " lahde
	lahde=${lade:-origin}
	git push $lahde master
fi

