#!/usr/bin/env python2.7

# Derive scale factors binned in MET and HT

from ROOT import TFile, TCanvas, gStyle

f_in = TFile('plots_2LSOS.root')
f_out = TFile('met_ht_fs.root', 'RECREATE')

name_histos = ['sf_met_ht_fine', 'sf_met_ht_coarse',
               'sf_met_ht200_fine', 'sf_met_ht200_coarse',
               'sf_met_ht200_coarse_varbin']

# FullSim samples
samplesFullSim = ['DY_FS', 'Wj_FS', 'TTbar_incl', 'TChiWZ_400_375_FS']

# Delphes samples
samplesDelphes = ['DY2', 'Wj2', 'tt', 'TChiWZ_400_375_Delphes_v09']

for name_histo in name_histos:
    for idx in range(0, len(samplesFullSim)):
        sampleFullSim = samplesFullSim[idx]
        sampleDelphes = samplesDelphes[idx]
        histo_FullSim = f_in.Get('{}_{}'.format(name_histo, sampleFullSim))
        histo_Delphes = f_in.Get('{}_{}'.format(name_histo, sampleDelphes))
        histo_ratio = histo_FullSim.Clone()
        histo_ratio.SetName('{}_ratio'.format(histo_Delphes.GetName()))
        histo_ratio.Divide(histo_Delphes)

        #print idx, histo_FullSim, histo_FullSim.Integral(1, 10, 1, 10), histo_FullSim.GetXaxis().GetNbins()
        #print idx, histo_Delphes, histo_Delphes.Integral(1, 10, 1, 10)

        ## Loop over histogram, include overflow bin, but not underflow bin
        #for binX in range(1, histo_FullSim.GetXaxis().GetNbins()+2):
        #    for binY in range(1, histo_FullSim.GetXaxis().GetNbins()+2):
        #        content_FullSim = histo_FullSim.GetBinContent(binX, binY)
        #        content_Delphes = histo_Delphes.GetBinContent(binX, binY)
        #        try:
        #            ratio = content_FullSim/content_Delphes
        #        except ZeroDivisionError:
        #            ratio = 0.
        #        #print idx, binX, binY, content_FullSim, content_Delphes, ratio
        #        histo_ratio.SetBinContent(binX, binY, ratio)

        # Cosmetics for ratio histogram
        c = TCanvas()
        gStyle.SetOptStat(0)
        histo_ratio.SetTitle('Delphes to FullSim scale factors for {}'
                             .format(sampleDelphes))
        histo_ratio.GetYaxis().SetTitleOffset(1.05)
        c.SetBottomMargin(.13)
        c.SetLeftMargin(.14)
        c.SetRightMargin(.12)

        # Draw and save ratio histogram
        histo_ratio.Draw('COLZ')
        c.SaveAs('{}_ratio_{}_ratio.pdf'.format(name_histo, sampleFullSim))

        # Save histograms to root file
        f_out.cd()
        histo_FullSim.Write()
        histo_Delphes.Write()
        histo_ratio.Write()
