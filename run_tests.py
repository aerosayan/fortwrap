#!/usr/bin/env python

import os
import glob

opts = '-g --clean -d wrap'
cmd = '../../fortwrap.py'

os.chdir('tests')
tests = glob.glob('*')

num_err = 0

# Hack so can go up a directory at start of loop
if tests:
    os.chdir(tests[0])

for test in tests:
    os.chdir('..')
    print "Running test:", test
    os.chdir(test)
    # Run wrapper generator
    stat = os.system(cmd + ' ' + opts)
    if stat!=0:
        print "Error running fortwrap.py"
        num_err += 1
        continue
    # Build test program
    stat = os.system('make')
    if stat!=0:
        print "Error building program"
        num_err += 1
        continue
    # Run test program
    stat = os.system('./prog')
    if stat!=0:
        print "Error running test program"
        num_err += 1

if num_err == 0:
    print "Tests successful"
else:
    print num_err, "error(s)"
