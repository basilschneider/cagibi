void savePlot(TH1F* h1, TH1F* h2, TH1F* h3, TH1F* h4, std::string name, bool logy, double yMax){
    h1->GetYaxis()->SetRangeUser(0, yMax);
    h1->GetYaxis()->SetTitle("# events");
    h1->SetTitle("");

    h1->SetLineColor(kGreen+3);
    h1->SetMarkerColor(kGreen+3);
    h2->SetLineColor(kRed);
    h2->SetMarkerColor(kRed);
    h3->SetLineColor(kYellow+1);
    h3->SetMarkerColor(kYellow+1);
    h4->SetLineColor(kBlue+1);
    h4->SetMarkerColor(kBlue+1);

    gStyle->SetOptStat(0);
    TCanvas c;

    h1->Draw("HIST");
    h2->Draw("SAME HIST");
    h3->Draw("SAME HIST");
    h4->Draw("SAME HIST");

    TLegend* l = new TLegend(0.6, 0.7, 0.9, 0.9);
    l->AddEntry(h1, "metUncorr", "l");
    l->AddEntry(h2, "met", "l");
    l->AddEntry(h3, "metEGClean", "l");
    l->AddEntry(h4, "metMuEGClean", "l");

    l->Draw("SAME");

    if (logy){
        h1->SetMinimum(0.5);
        c.SetLogy();
    }

    name += ".pdf";
    c.Print(name.c_str());
}

void plot(){
    TFile* f1 = new TFile("plots_metUncorr.root", "READ");
    TFile* f2 = new TFile("plots_met.root", "READ");
    TFile* f3 = new TFile("plots_metEGClean.root", "READ");
    TFile* f4 = new TFile("plots_metMuEGClean.root", "READ");

    TH1F* h1MET = f1->Get("MET_data");
    TH1F* h2MET = f2->Get("MET_data");
    TH1F* h3MET = f3->Get("MET_data");
    TH1F* h4MET = f4->Get("MET_data");

    savePlot(h1MET, h2MET, h3MET, h4MET, "MET", false, 220.);
    savePlot(h1MET, h2MET, h3MET, h4MET, "MET_log", true, 220.);

    TH1F* h1LT = f1->Get("LT_data");
    TH1F* h2LT = f2->Get("LT_data");
    TH1F* h3LT = f3->Get("LT_data");
    TH1F* h4LT = f4->Get("LT_data");

    savePlot(h1LT, h2LT, h3LT, h4LT, "LT", false, 220.);
    savePlot(h1LT, h2LT, h3LT, h4LT, "LT_log", true, 220.);

    TH1F* h1dPhi = f1->Get("dPhi_data");
    TH1F* h2dPhi = f2->Get("dPhi_data");
    TH1F* h3dPhi = f3->Get("dPhi_data");
    TH1F* h4dPhi = f4->Get("dPhi_data");

    savePlot(h1dPhi, h2dPhi, h3dPhi, h4dPhi, "dPhi", false, 220.);
    savePlot(h1dPhi, h2dPhi, h3dPhi, h4dPhi, "dPhi_log", true, 220.);

    return;
}
