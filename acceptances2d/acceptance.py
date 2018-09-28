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

def make_histos(signal, com, cutflows, stage):

    N2s = []
    N1s = []
    N2mN1s = []
    nTots = []
    nTotErrs = []
    nEnds = []
    nEndErrs = []
    paveTitle = '?'
    paveTitle2 = ''

    for cutflow in glob(cutflows):
        N2 = cutflow.split('_')[7]
        N1 = cutflow.split('_')[8]
        with open(cutflow, 'r') as f:
            for line in f:
                if line.split()[0] == 'entry' and line.split()[1] == 'point':
                    nTot = line.split()[2]
                    nTotErr = line.split()[3]
                elif line.split()[0] == 'dR-Lep1-Lep2-smaller-2':
                    nEnd = line.split()[1]
                    nEndErr = line.split()[2]

        N2s.append(float(N2))
        N1s.append(float(N1))
        N2mN1s.append(float(N2)-float(N1))
        nTots.append(float(nTot))
        nTotErrs.append(float(nTotErr))
        nEnds.append(float(nEnd))
        nEndErrs.append(float(nEndErr))

    if signal == 'N2N1' and com == '13':
        N2bins = [90., 110., 130., 150., 170., 190., 210., 230., 250.]
        N2mN1bins = [6.5, 8.5, 12.5, 17.5, 25., 35., 45.]
    elif signal == 'N2C1' and com == '13':
        N2bins = [87.5, 112.5, 137.5, 162.5, 187.5, 212.5, 237.5, 262.5, 287.5, 312.5]
        N2mN1bins = [6.5, 8.5, 12.5, 17.5, 25., 35., 45.]
    elif signal == 'N2C1' and com == '14':
        N2bins = [75., 125., 175., 225., 275., 325., 375., 425.]
        N2mN1bins = [2.5, 7.5, 12.5, 17.5, 22.5, 27.5, 32.5, 37.5, 42.5]
    N2bina = array('d', sorted(set(N2bins)))
    N2mN1bina = array('d', sorted(set(N2mN1bins)))

    # Histogram
    h = TH2D('', '', len(N2bina)-1, N2bina, len(N2mN1bina)-1, N2mN1bina)
    for idx in range(0, len(N2s)):
        N2 = N2s[idx]
        N1 = N1s[idx]
        N2mN1 = N2mN1s[idx]
        nTot = nTots[idx]
        nTotErr = nTotErrs[idx]
        nEnd = nEnds[idx]
        nEndErr = nEndErrs[idx]
        #print 'Foo01', N2, N2mN1, nEnd
        if stage == 'nTot':
            paveTitle = 'Total events'
            h.Fill(N2, N2mN1, nTot)
        elif stage == 'nEnd':
            paveTitle = 'Events in SR'
            h.Fill(N2, N2mN1, nEnd)
        elif stage == 'Acc':
            paveTitle = 'Acceptance'
            paveTitle2 = '(*1000)'
            try:
                h.Fill(N2, N2mN1, 1000.*nEnd/nTot)
            except ZeroDivisionError:
                pass

    # Style
    gStyle.SetOptStat(0)
    gStyle.SetPaintTextFormat('.2f')
    h.GetXaxis().SetTitle('N2')
    h.GetYaxis().SetTitle('dM')
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
            .format(signal, paveTitle, com, paveTitle2))

    # Plot
    c = TCanvas()
    #c.SetLogy()
    h.Draw('colz|text')
    t1.Draw('same')
    t2.Draw('same')
    c.Print('{}_{}_{}TeV.pdf'.format(stage, signal, com))
    c.Print('{}_{}_{}TeV.png'.format(stage, signal, com))

signals = ['N2N1', 'N2C1', 'N2C1']
coms = ['13', '13', '14']
for idx in range(0, len(signals)):
    signal = signals[idx]
    com = coms[idx]
    cutflows = ('/uscms_data/d3/bschneid/analysis/upgrade/CMSSW_8_0_25/src/CMGTools/TTHAnalysis/python/plotter/acceptances/cutflow_acc_{}_*_Delphes_{}TeV+.txt'
                .format(signal, com))

    make_histos(signal, com, cutflows, 'nTot')
    make_histos(signal, com, cutflows, 'nEnd')
    make_histos(signal, com, cutflows, 'Acc')



# Divide two histograms (by hand)
N2bins = [87.5, 112.5, 137.5, 162.5, 187.5, 212.5, 237.5, 262.5, 287.5, 312.5]
N2mN1bins = [6.5, 8.5, 12.5, 17.5, 25., 35., 45.]
N2bina = array('d', sorted(set(N2bins)))
N2mN1bina = array('d', sorted(set(N2mN1bins)))

# Histogram
h = TH2D('', '', len(N2bina)-1, N2bina, len(N2mN1bina)-1, N2mN1bina)
h.Fill(100., 7.5, 2.00)
h.Fill(100., 10., 1.88)
h.Fill(100., 15., 2.20)
h.Fill(100., 20., 2.89)
h.Fill(100., 30., 2.40)
h.Fill(100., 40., 1.78)
h.Fill(200., 7.5, 1.82)
h.Fill(200., 10., 1.72)
h.Fill(200., 15., 1.77)
h.Fill(200., 20., 1.63)
h.Fill(200., 30., 1.71)
h.Fill(200., 40., 1.82)

# Style
gStyle.SetOptStat(0)
gStyle.SetPaintTextFormat('.2f')
h.GetXaxis().SetTitle('N2')
h.GetYaxis().SetTitle('dM')
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
t2.AddText('Phase-2 Simulation Preliminary   (N2C1+N2N1)/N2C1 Events in SR')

# Plot
c = TCanvas()
#c.SetLogy()
h.Draw('colz|text')
t1.Draw('same')
t2.Draw('same')
c.Print('ratio_N2C1N2N1dbN2C1_13TeV.pdf')
c.Print('ratio_N2C1N2N1dbN2C1_13TeV.png')
