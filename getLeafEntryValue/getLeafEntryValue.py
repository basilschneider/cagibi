#!/usr/bin/env python

# Return value in root file for given leaf and entry

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

if __name__ == "__main__":
    # TODO: Replace positional parameters with options and make proper help
    if len(argv) != 4:
        raise RuntimeError("Need exactly three positional parameters")

    # Assign variable names to positional arguments
    f = TFile(argv[1])
    leaf = argv[2]
    entry = int(argv[3])

    # Find tree in file
    treename = get_first_tree(f)
    t = f.Get(treename)
    print ('Found tree with name {} and {} entries'
            .format(treename, t.GetEntries()))

    # Don't go beyond end of tree
    if entry >= t.GetEntries():
        msg = "The requested entry is larger than the entries in the tree."
        raise RuntimeError(msg)

    # Try to get value
    t.GetEntry(entry)
    try:
        val = t.GetLeaf(leaf).GetValue()
    except ReferenceError:
        raise ReferenceError("Leaf {} not found in tree {}."
                             .format(leaf, treename))

    # Print value
    print 'Value of leaf {} in tree {}: {}'.format(leaf, treename, val)
