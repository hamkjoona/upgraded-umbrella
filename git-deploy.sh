#!/bin/bash

git add .
git status

echo Komminoidaan ylläolevat muutokset.
echo Anna commit-viesti:
read viesti

print $viesti;

git commit -am "$viesti"

echo "Pusketaanko? (k/e)"
read pusketaanko

if [ $pusketaanko = "k" ]; then
	read -p "Lahde: [origin]: " lahde
	lahde=${lade:-origin}
	git push $lahde master
fi

