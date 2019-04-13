#!/usr/bin/env python2

from glob import glob
from array import array
from ROOT import TH2D, TCanvas, gStyle, TColor, TPaveText

def set_palette():

    """ Set a color palette from a given RGB list. stops, red, green and
    blue should all be lists of the same length. """

    stops = [0.00, 0.34, 0.61, 0.84, 1.00]
    red   = [0.00, 0.00, 0.87, 1.00, 0.71]
    green = [0.10, 0.81, 1.00, 0.20, 0.10]
    blue  = [0.61, 1.00, 0.12, 0.00, 0.00]

    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)

    npoints = len(s)
    TColor.CreateGradientColorTable(npoints, s, r, g, b, 100)
    gStyle.SetNumberContours(100)


N2s = []
N2mN1s = []
SSs = []

datafiles = '/uscms_data/d3/bschneid/analysis/higgsCombine/CMSSW_8_1_0/src/HiggsAnalysis/CombinedLimit/scripts/limits/logs/limit_N2C1_*.txt'
for datafile in glob(datafiles):
    N2 = datafile.split('_')[6]
    N2mN1 = datafile.split('_')[7].rstrip('.tx')
    with open(datafile, 'r') as f:
        for line in f:
            try:
                if line.split()[0] == 'Expected' and \
                        line.split()[1] == '50.0%:':
                    SS = line.split()[4]
            except IndexError:
                pass

        N2s.append(float(N2))
        N2mN1s.append(float(N2mN1))
        SSs.append(float(SS))

N2bins = [75., 125., 175., 225., 275., 325., 375.]
N2mN1bins = [4, 6.5, 9., 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 42.5]
N2bina = array('d', sorted(set(N2bins)))
N2mN1bina = array('d', sorted(set(N2mN1bins)))
print 'Foo02', N2mN1bina

# Histogram
h = TH2D('', '', len(N2bina)-1, N2bina, len(N2mN1bina)-1, N2mN1bina)
for idx in range(0, len(N2s)):
    N2 = N2s[idx]
    N2mN1 = N2mN1s[idx]
    SS = SSs[idx]
    #print 'Foo01', N2, N2mN1, SS
    h.Fill(N2, N2mN1, SS)

# Style
gStyle.SetOptStat(0)
gStyle.SetPaintTextFormat('.2f')
h.GetXaxis().SetTitle('N2')
h.GetYaxis().SetTitle('dM')
h.GetZaxis().SetRangeUser(0., 4.)
set_palette()

# Pave Text
t1 = TPaveText(.1, .906, .2, 1., 'NDC')
t1.SetTextSize(.039)
t1.SetFillColor(0)
t1.SetFillStyle(0)
t1.SetLineWidth(0)
t1.SetTextAlign(12)
t1.AddText('CMS')
t2 = TPaveText(.13, .9, .9, 1., 'NDC')
t2.SetTextSize(.033)
t2.SetFillColor(0)
t2.SetFillStyle(0)
t2.SetLineWidth(0)
t2.SetTextAlign(12)
t2.SetTextFont(42)
t2.AddText('Phase-2 Simulation Preliminary   {} {} at {}TeV {}'
        .format('N2C1', 'excluded signal strength', '14', ''))

# Plot
c = TCanvas()
#c.SetLogy()
h.Draw('colz|text')
t1.Draw('same')
t2.Draw('same')
c.Print('signal_strength.pdf')
c.Print('signal_strength.png')
