#!/usr/bin/env python

# Quick and ugly: Move ROOT objects from one TFile to another

from sys import argv, exit
from ROOT import TFile

# Read in file
try:
    s_f_in = argv[1]
except IndexError:
    print 'Give me the name of the root file you want to read in as argument.'
    exit()

# Define name of output file
try:
    s_f_out = '{}_new.root'.format(s_f_in[:s_f_in.rindex('.')])
except ValueError:
    s_f_out = '{}_new.root'.format(s_f_in)

s_t_in = 'ntuple/Delphes'
s_t_out = 'Delphes'

s_h_in = 'weightCounter/Event_weight'
s_h_out = 'Event_weight'

f_in = TFile(s_f_in, 'READ')
t_in = f_in.Get(s_t_in)
h_in = f_in.Get(s_h_in)
f_out = TFile(s_f_out, 'RECREATE')
f_out.cd()
t_out = t_in.CloneTree()
h_out = h_in.Clone()
del t_in, h_in
f_out.Write()
f_out.Close()

print 'All good (I hope). File {} is all yours.'.format(s_f_out)
