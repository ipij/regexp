#!/usr/bin/env python

import re
import sys

HEADER = '\033[95m'
NORMAL = '\033[0m'

def print_attr(key, value):
    print('%s%s: %s%s' % (HEADER, key, NORMAL, value))

re_funcs = re.compile(
    r"(^|;|})\s*"  # begin
    "(?P<function>"
        r"(?P<type>(\w+(\s*\*+)?\s+)+)"  #types
        r"(?P<name>\w+)\s*"  # func name
        r"\(\s*"  # left paren
            "(?P<args>"
                r"((\w+(\s*\*+)?\s+)+\w+\s*,\s*)*"  # many arguments
                r"((\w+(\s*\*+)?\s+)+\w+)"  # last arguments
                r"|void|\.\.\." # or void/...
            ")?"  # optional - 0 args is true
        r"\s*\)"  # right paren
        r"(\s*const)?" # const function
    ")"
    r"\s*[{;]"  # end
    , re.MULTILINE
)

if len(sys.argv) < 2:
    print("usage: jimmy.py <filename>")

with open(sys.argv[1]) as f:
    buff = f.read()

print("functions:")
for m in re_funcs.finditer(buff):
    
    print_attr("func", m.group("function"))
    print_attr("name", m.group("name"))
    print_attr("args", m.group("args"))
    print_attr("type", m.group("type"))
    print('----')
