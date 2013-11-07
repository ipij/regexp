#!/usr/bin/python3

import re

re_href = re.compile(r"(?:(?<=http://)|www\.)[\w\-.]+", re.I)

with open("joemonster.html") as f:
	buff = f.read()
	urls = re_href.findall(buff)
	for url in urls:
		print(url)
	

