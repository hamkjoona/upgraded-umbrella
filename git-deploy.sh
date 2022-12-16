#!/bin/bash

# Ei ota kantaa tunnistukseen, ssh-avaimen ja ssh-add -komennon käyttöä suositellaan pusksemisen sujuvoittamiseksi. 

git add .

git_status=$(git status --porcelain)
has_changes=$(echo $git_status| wc -l)

if [ $has_changes ]; then
	echo Komminoitavat tiedostot:
	echo $git_status
	echo
	echo Anna commit-viesti:
	read viesti
	if [ -z $viesti ]; then
		echo Viesti on tyhjä!
		exit	
	fi

	git commit -am "$viesti"
else 
	echo Ei muutoksia.
fi

echo "Pusketaanko? (k/e)"
read pusketaanko

if [ $pusketaanko = "k" ]; then
	read -p "Lahde: [origin]: " lahde
	lahde=${lade:-origin}
	git push $lahde master
fi

echo
echo Kirjatut muutokset

git log --stat -n 1
