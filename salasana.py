#!/usr/bin/python3

import sys
import string
import random

s_pituus = 8;
salasana = "";

tuetut_merkit = string.ascii_letters
for i in range(0, 10):
	tuetut_merkit += str(i);

if len(sys.argv) > 1:
	try:
		pituus = int(sys.argv[1]);
		if pituus > 0:
			s_pituus = int(sys.argv[1])
	except ValueError:
		print("Viallinen numero!");

for i in range(s_pituus):
	salasana += random.choice(tuetut_merkit)
print(salasana)

