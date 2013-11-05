#!/usr/bin/env python3

import re
from datetime import date

re_date = re.compile(r"(\d\d)/(\d\d)/(\d\d\d\d)")

class DateError(Exception):
    pass

#I hate you, fajkowsky.

def parse_date(raw_date):
    match = re_date.match(raw_date)
    if match:
        day, month, year = (int(x) for x in match.groups())
        if year not in range(1600, 9999 + 1):
            raise ValueError("Year is not in <1600, 9999>")
        return date(day=day, month=month, year=year)
    else:
        raise ValueError("Date has wrong format")

try:
    while True:
        raw_date = input("insert date: ")
        try:
            if parse_date(raw_date):
                print("OK!")
        except ValueError as e:
            print("ERR: %s" % e)

except KeyboardInterrupt:
    print("Bye.")