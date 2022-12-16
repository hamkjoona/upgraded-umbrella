#!/bin/bash

# Ei ota kantaa tunnistukseen, ssh-avaimen ja ssh-add -komennon käyttöä suositellaan pusksemisen sujuvoittamiseksi. 

git add .

git_status=$(git status --porcelain)
#has_changes=$(echo $git_status| wc -l)

#if [ $has_changes ]; then
if [ ! -z "$git_status" ]; then 
	echo "Komminoitavat tiedostot:"
	echo "$git_status"
	echo
	echo "Anna commit-viesti:"
	read viesti
	if [ -z $viesti ]; then
		echo "Viesti on tyhjä!"
		exit	
	fi

	git commit -am "$viesti"
else 
	echo "Ei muutoksia."
fi

#echo "Pusketaanko? (k/e)[k]"
#read pusketaanko
read -p "Pusetaanko? k/e [k]: " pusketaanko
pusketaanko = ${pusketaanko:-k}

if [ $pusketaanko = "k" ]; then
	read -p "Lahde: [origin]: " lahde
	lahde=${lahde:-origin}
	git push $lahde master
fi

if [ ! -z "$git_status" ]; then 
	echo ""
	echo Kirjatut muutokset
	git log --stat -n 1
fi
