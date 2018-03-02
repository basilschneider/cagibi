#!/usr/bin/env python

from sys import argv
from ROOT import TFile, gDirectory

# Returns first tree it finds
def get_first_tree(f, dir=''):
    if dir:
        f.cd(dir)
    for key in gDirectory.GetListOfKeys():
        if key.GetClassName() == "TDirectoryFile":
            return get_first_tree(f, key.GetName())
        if key.GetClassName() == "TTree":
            if dir:
                return '{}/{}'.format(dir, key.GetName())
            else:
                return key.GetName()

total = 0

for idx in range(1, len(argv)):
    print 'Open file {} from {}'.format(idx, len(argv)-1)
    f = TFile(argv[idx])

    treename = get_first_tree(f)
    total += f.Get(treename).GetEntries()

print 'Total number of events: {}'.format(total)
