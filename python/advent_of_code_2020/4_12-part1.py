#!/usr/bin/python3

from sys import stdin

valid_passports = 0
passport = {
    'byr': False, 
    'iyr': False, 
    'eyr': False,
    'hgt': False, 
    'hcl': False,
    'ecl': False,
    'pid': False,
    'cid': True
}

for line in stdin:
    if line != '\n':
        fields = line.split(" ")
        for field in fields:
            (entry_type, entry_value) = field.rstrip().split(':')
            passport[entry_type] = True
    else:
        print(f"Passport: {passport}")
        passport_valid = True
        #valid = len(list(filter(passport[key] passport.keys(),
        for passport_key in passport.keys():
            if passport[passport_key] == False:
                passport_valid = False
                break

        if passport_valid:
            print("Valid! :)")
            valid_passports += 1
        # clear passport
        for passport_key in passport.keys():
            passport[passport_key] = False
        passport['cid'] = True

print(valid_passports)
