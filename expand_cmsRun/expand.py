#! /usr/bin/env python

# Expand CMS Driver config

import sys
compactPy=sys.argv[1]
result={}
execfile(compactPy,result)
process=result["process"]
print process.dumpPython()
