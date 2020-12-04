#!/usr/bin/python3

from sys import stdin

import re

valid_passports = 0

def verify_height(height):
    unit = height[-2:]
    if (unit not in ["in", "cm"]):
        return False

    value = int(height[:-2])
    if unit == 'in':
        return value >= 59 and value <= 76
    elif unit == 'cm':
        return value >= 150 and value <= 193
    else:
        return False

passport_validators = {
    'byr': (lambda x: int(x)>= 1920 and int(x) <= 2002),
    'iyr': (lambda x: int(x)>= 2010 and int(x) <= 2020),
    'eyr': (lambda x: int(x)>= 2020 and int(x) <= 2030),
    'hgt': verify_height,
    'hcl': (lambda x: re.match("\#[0-9a-f]{6}", x) != None),
    'ecl': (lambda x: x in ['amb', 'blu', 'brn', 'gry', 'grn', 'hzl', 'oth']),
    'pid': (lambda x: re.fullmatch("[0-9]{9}", x) != None)
}
passport = {
}

for line in stdin:
    if line != '\n':
        fields = line.split(" ")
        for field in fields:
            (entry_type, entry_value) = field.rstrip().split(':')
            passport[entry_type] = entry_value
    else:
        print(f"Passport: {passport}")
        passport_valid = True
        for passport_key in passport_validators.keys():
            if passport_key not in passport.keys():
                print(f"Invalid: Missing key for passport - {passport_key}")
                passport_valid = False
                break
            if passport_validators[passport_key](passport[passport_key]) != True:
                print(f"Invalid: Validation failed for - {passport_key} = {passport[passport_key]}")
                passport_valid = False
                break

        if passport_valid:
            print("Valid! :)")
            valid_passports += 1

        passport = {}

print(valid_passports)
