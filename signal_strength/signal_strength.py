#!/usr/bin/env python2

from glob import glob
from array import array
from ROOT import TH2D, TCanvas, gStyle, TColor, TPaveText

#def set_palette():
#
#    """ Set a color palette from a given RGB list. stops, red, green and
#    blue should all be lists of the same length. """
#
#    stops = [0.00, 0.34, 0.61, 0.84, 1.00]
#    red   = [0.00, 0.00, 0.87, 1.00, 0.71]
#    green = [0.10, 0.81, 1.00, 0.20, 0.10]
#    blue  = [0.61, 1.00, 0.12, 0.00, 0.00]
#
#    s = array('d', stops)
#    r = array('d', red)
#    g = array('d', green)
#    b = array('d', blue)
#
#    npoints = len(s)
#    TColor.CreateGradientColorTable(npoints, s, r, g, b, 100)
#    gStyle.SetNumberContours(100)
#
## Histogram
#xbins = [1, 2, 3]
#ybins = [1, 2, 3]
#xbinsa = array('d', xbins)
#ybinsa = array('d', ybins)
#
#h = TH2D('', '', len(xbinsa)-1, xbinsa, len(ybinsa)-1, ybinsa)
#h.Fill(2, 3, 4)
#
## Style
#gStyle.SetOptStat(0)
#gStyle.SetPaintTextFormat('.2f')
#h.GetXaxis().SetTitle('N2')
#h.GetYaxis().SetTitle('dM')
#set_palette()
#
## Pave Text
#t1 = TPaveText(.1, .906, .2, 1., 'NDC')
#t1.SetTextSize(.039)
#t1.SetFillColor(0)
#t1.SetFillStyle(0)
#t1.SetLineWidth(0)
#t1.SetTextAlign(12)
#t1.AddText('CMS')
#t2 = TPaveText(.13, .9, .9, 1., 'NDC')
#t2.SetTextSize(.033)
#t2.SetFillColor(0)
#t2.SetFillStyle(0)
#t2.SetLineWidth(0)
#t2.SetTextAlign(12)
#t2.SetTextFont(42)
#t2.AddText('Phase-2 Simulation Preliminary   {} {} at {}TeV {}'
#        .format('a', 'b', 'c', 'd'))

# Plot
c = TCanvas()
#c.SetLogy()
#h.Draw('colz|text')
#t1.Draw('same')
#t2.Draw('same')
#c.Print('signal_strength.pdf')
#c.Print('signal_strength.png')
