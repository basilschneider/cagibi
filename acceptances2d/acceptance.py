#!/usr/bin/env python3

from glob import glob
from ROOT import TH2D


pattern = 'cutflow_acc_N2N1_240_220_Delphes_13TeV+.txt'

for f in glob('cutflow_acc_N2N1_*'):
    print(f)



#    // Style
#    gStyle->SetOptStat(0);
#    gStyle->SetPaintTextFormat(".3f");
#    h->GetXaxis()->SetTitle("|#eta|");
#    h->GetYaxis()->SetTitle("p_{T}(e)");
#    h->GetZaxis()->SetRangeUser(0., 1.);
#    set_palette();
#
#    // Pave Text
#    TPaveText* t1 = new TPaveText(.1, .906, .2, 1., "NDC");
#    t1->SetTextSize(.039);
#    t1->SetFillColor(0);
#    t1->SetFillStyle(0);
#    t1->SetLineWidth(0);
#    t1->SetTextAlign(12);
#    t1->AddText("CMS");
#    TPaveText* t2 = new TPaveText(.13, .9, .9, 1., "NDC");
#    t2->SetTextSize(.033);
#    t2->SetFillColor(0);
#    t2->SetFillStyle(0);
#    t2->SetLineWidth(0);
#    t2->SetTextAlign(12);
#    t2->SetTextFont(42);
#    t2->AddText("Phase-2 Simulation Preliminary, 14 TeV, 200 PU    Muon Tight ID Efficiency");
#
#    // Plot
#    TCanvas* c = new TCanvas();
#    c->SetLogy();
#    h->Draw("colz|text");
#    t1->Draw("same");
#    t2->Draw("same");
#    c->Print("eff-mu.pdf");
#}
