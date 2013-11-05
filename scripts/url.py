#!/usr/bin/python3

import re

re_title = re.compile(r"(?:(?<=http://)|www\.)[\w\-.]+", re.I)

with open("joemonster.html") as f:
	buff = f.read()
	urls = re_title.findall(buff)
	for url in urls:
		print(url)
	

