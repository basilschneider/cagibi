#!/usr/bin/env python

from sys import argv
from ROOT import TFile, gDirectory, TH2F, TCanvas, gStyle

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
#masses = []
masses = TH2F('scan', 'scan', 401, -.5, 400.5, 401, -.5, 400.5)
c = TCanvas()
gStyle.SetOptStat(0)

for idx in range(1, len(argv)):
    print 'Open file {} from {}'.format(idx, len(argv)-1)
    f = TFile(argv[idx])

    treename = get_first_tree(f)
    tree = f.Get(treename)

    for event in tree:
        genmass = list(event.GenPart_mass)
        pdgid = list(event.GenPart_pdgId)
        mn1 = mn2 = 0
        for idx in range(len(genmass)):
            if abs(pdgid[idx]) == 1000022:
                mn1 = genmass[idx]
            if abs(pdgid[idx]) == 1000024:
                mn2 = genmass[idx]
            if mn1 > 0 and mn2 > 0:
                #masses.append((mn1, mn2))
                masses.Fill(mn2, mn1, 1.)
                break
#print 'masses:', masses
masses.Draw('COLZ')
c.Print('scanSusyMassesNANOAOD.pdf')

# Store in root file
fout = TFile('scanSusyMassesNANOAOD.root', 'RECREATE')
masses.Write()
fout.Close()

#Events->Scan("MaxIf$(GenPart_mass,abs(GenPart_pdgId)==1000022):MaxIf$(GenPart_mass,abs(GenPart_pdgId)==1000024)")
