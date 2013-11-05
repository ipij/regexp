#!/usr/bin/env python

import re
import sys

HEADER = '\033[95m'
NORMAL = '\033[0m'


def print_attr(key, value):
    print('%s%s: %s%s' % (HEADER, key, NORMAL, value))

re_type = r"""
(?:
    (\w+\s+)*  #  additional attributes to type
    \w+  # name of type
    (\s+|\s*[*&]+\s*)
)
"""

re_funcs = re.compile(
    r"""
    (^|;|})\s*  # begin
    (?P<function>
        (?P<type>{type})  # types
        (?P<name>
            \w+  # func name
            (\s*::\s*\w+)?  # if method
        )\s*  
        \(\s*  # left paren
            (?P<args>
                ({type}\w+\s*,\s*)*  # many arguments
                ({type}\w+)  # last arguments
                |void|\.\.\.  # or void/...
            )?  # optional - non-args function
            (\s*const)?  # const function
        \s*\)  # right paren
    )  # end function
    \s*[{;]  # end
    """.replace("{type}", re_type),
    re.MULTILINE | re.VERBOSE
)

if len(sys.argv) < 2:
    print("usage: jimmy.py <filename>")

with open(sys.argv[1]) as f:
    buff = f.read()

lines = {
    #line char position: line_number
    m.start(): line_number + 1
    for line_number, m in enumerate(re.finditer(r"\n", buff))
}

print("functions:")
for m in re_funcs.finditer(buff):
    #find line
    line = lines[buff.rfind("\n", 0, m.end() + 1)]

    print_attr(line, m.group("function"))
    print_attr("name", m.group("name"))
    print_attr("args", m.group("args"))
    print_attr("type", m.group("type"))
    print('----')