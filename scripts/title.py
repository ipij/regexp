#!/usr/bin/python3

import re

re_title = re.compile(r"<title>([\w\s\-.]+?)</title>", re.I)

with open("site.html") as f:
	buff = f.read()
	tag = re_title.search(buff)
	if tag:
		print("Tytuł to:", tag.group(1))
	

