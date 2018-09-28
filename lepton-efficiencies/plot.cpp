void set_palette(){

    const Int_t n = 5;

    Double_t stops[n] = {0.00, 0.34, 0.61, 0.84, 1.00};
    Double_t red[n]   = {0.00, 0.00, 0.87, 1.00, 0.71};
    Double_t green[n] = {0.10, 0.81, 1.00, 0.20, 0.10};
    Double_t blue[n]  = {0.61, 1.00, 0.12, 0.00, 0.00};

    TColor::CreateGradientColorTable(n, stops, red, green, blue, 100);
    gStyle->SetNumberContours(100);
}

void plot(){

    // Create histogram
    //double eta_bins[8] = {0.0, 0.5, 1.0, 1.45, 1.55, 2.0, 2.5, 3.0};
    double eta_bins[6] = {0.0, 0.5, 1.0, 1.45, 1.55, 1.6};
    double pt_bins[9] = {2., 4., 6., 8., 10., 20., 35., 50., 100.};
    TH2D* h = new TH2D("", "", sizeof(eta_bins)/sizeof(eta_bins[0])-1, eta_bins, sizeof(pt_bins)/sizeof(pt_bins[0])-1, pt_bins);

    // Fill histogram
    h->Fill(0.2,  5., 0.018);
    h->Fill(0.2,  7., 0.252);
    h->Fill(0.2,  9., 0.480);
    h->Fill(0.2, 15., 0.681);
    h->Fill(0.2, 30., 0.792);
    h->Fill(0.2, 40., 0.862);
    h->Fill(0.2, 60., 0.859);
    h->Fill(0.7,  5., 0.016);
    h->Fill(0.7,  7., 0.198);
    h->Fill(0.7,  9., 0.446);
    h->Fill(0.7, 15., 0.598);
    h->Fill(0.7, 30., 0.759);
    h->Fill(0.7, 40., 0.847);
    h->Fill(0.7, 60., 0.872);
    h->Fill(1.2,  5., 0.005);
    h->Fill(1.2,  7., 0.029);
    h->Fill(1.2,  9., 0.108);
    h->Fill(1.2, 15., 0.289);
    h->Fill(1.2, 30., 0.570);
    h->Fill(1.2, 40., 0.743);
    h->Fill(1.2, 60., 0.828);
    h->Fill(1.5,  5., 0.026);
    h->Fill(1.5,  7., 0.045);
    h->Fill(1.5,  9., 0.133);
    h->Fill(1.5, 15., 0.411);
    h->Fill(1.5, 30., 0.629);
    h->Fill(1.5, 40., 0.761);
    h->Fill(1.5, 60., 0.752);
    h->Fill(1.57,  5., 0.061);
    h->Fill(1.57,  7., 0.191);
    h->Fill(1.57,  9., 0.337);
    h->Fill(1.57, 15., 0.475);
    h->Fill(1.57, 30., 0.605);
    h->Fill(1.57, 40., 0.713);
    h->Fill(1.57, 60., 0.794);
    h->Fill(2.2,  5., 0.100);
    h->Fill(2.2,  7., 0.223);
    h->Fill(2.2,  9., 0.427);
    h->Fill(2.2, 15., 0.590);
    h->Fill(2.2, 30., 0.720);
    h->Fill(2.2, 40., 0.800);
    h->Fill(2.2, 60., 0.840);
    h->Fill(2.7,  5., 0.049);
    h->Fill(2.7,  7., 0.152);
    h->Fill(2.7,  9., 0.436);
    h->Fill(2.7, 15., 0.679);
    h->Fill(2.7, 30., 0.778);
    h->Fill(2.7, 40., 0.830);
    h->Fill(2.7, 60., 0.919);

    // Style
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat(".3f");
    h->GetXaxis()->SetTitle("|#eta|");
    h->GetYaxis()->SetTitle("p_{T}(e)");
    h->GetZaxis()->SetRangeUser(0., 1.);
    set_palette();

    // Pave Text
    TPaveText* t1 = new TPaveText(.1, .906, .2, 1., "NDC");
    t1->SetTextSize(.039);
    t1->SetFillColor(0);
    t1->SetFillStyle(0);
    t1->SetLineWidth(0);
    t1->SetTextAlign(12);
    t1->AddText("CMS");
    TPaveText* t2 = new TPaveText(.13, .9, .9, 1., "NDC");
    t2->SetTextSize(.033);
    t2->SetFillColor(0);
    t2->SetFillStyle(0);
    t2->SetLineWidth(0);
    t2->SetTextAlign(12);
    t2->SetTextFont(42);
    t2->AddText("Phase-2 Simulation Preliminary, 14 TeV, 200 PU    Electron Medium ID Efficiency");

    // Plot
    TCanvas* c = new TCanvas();
    c->SetLogy();
    h->Draw("colz|text");
    t1->Draw("same");
    t2->Draw("same");
    c->Print("eff-el.pdf");
}

//void plot(){
//
//    // Create histogram
//    //double eta_bins[7] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.5, 2.8};
//    double eta_bins[6] = {0.0, 0.5, 1.0, 1.5, 2.0, 2.4};
//    double pt_bins[9] = {2., 4., 6., 8., 10., 20., 35., 50., 100.};
//    TH2D* h = new TH2D("", "", sizeof(eta_bins)/sizeof(eta_bins[0])-1, eta_bins, sizeof(pt_bins)/sizeof(pt_bins[0])-1, pt_bins);
//
//    // Fill histogram
//    h->Fill(0.2,  3., 0.04);
//    h->Fill(0.2,  5., 0.43);
//    h->Fill(0.2,  7., 0.53);
//    h->Fill(0.2,  9., 0.67);
//    h->Fill(0.2, 15., 0.81);
//    h->Fill(0.2, 30., 0.90);
//    h->Fill(0.2, 40., 0.92);
//    h->Fill(0.2, 60., 0.90);
//    h->Fill(0.7,  3., 0.05);
//    h->Fill(0.7,  5., 0.46);
//    h->Fill(0.7,  7., 0.56);
//    h->Fill(0.7,  9., 0.65);
//    h->Fill(0.7, 15., 0.79);
//    h->Fill(0.7, 30., 0.91);
//    h->Fill(0.7, 40., 0.93);
//    h->Fill(0.7, 60., 0.92);
//    h->Fill(1.2,  3., 0.15);
//    h->Fill(1.2,  5., 0.47);
//    h->Fill(1.2,  7., 0.55);
//    h->Fill(1.2,  9., 0.64);
//    h->Fill(1.2, 15., 0.78);
//    h->Fill(1.2, 30., 0.89);
//    h->Fill(1.2, 40., 0.96);
//    h->Fill(1.2, 60., 0.91);
//    h->Fill(1.7,  3., 0.23);
//    h->Fill(1.7,  5., 0.44);
//    h->Fill(1.7,  7., 0.53);
//    h->Fill(1.7,  9., 0.68);
//    h->Fill(1.7, 15., 0.78);
//    h->Fill(1.7, 30., 0.89);
//    h->Fill(1.7, 40., 0.95);
//    h->Fill(1.7, 60., 0.88);
//    h->Fill(2.2,  3., 0.22);
//    h->Fill(2.2,  5., 0.36);
//    h->Fill(2.2,  7., 0.44);
//    h->Fill(2.2,  9., 0.57);
//    h->Fill(2.2, 15., 0.63);
//    h->Fill(2.2, 30., 0.71);
//    h->Fill(2.2, 40., 0.76);
//    h->Fill(2.2, 60., 0.82);
//    //h->Fill(2.7,  3., 0.80);
//    //h->Fill(2.7,  5., 0.80);
//    //h->Fill(2.7,  7., 0.80);
//    //h->Fill(2.7,  9., 0.80);
//    //h->Fill(2.7, 15., 0.80);
//    //h->Fill(2.7, 30., 0.80);
//    //h->Fill(2.7, 40., 0.80);
//    //h->Fill(2.7, 60., 0.80);
//
//    // Style
//    gStyle->SetOptStat(0);
//    gStyle->SetPaintTextFormat(".3f");
//    h->GetXaxis()->SetTitle("|#eta|");
//    h->GetYaxis()->SetTitle("p_{T}(#mu)");
//    h->GetZaxis()->SetRangeUser(0., 1.);
//    set_palette();
//
//    // Pave Text
//    TPaveText* t1 = new TPaveText(.1, .906, .2, 1., "NDC");
//    t1->SetTextSize(.039);
//    t1->SetFillColor(0);
//    t1->SetFillStyle(0);
//    t1->SetLineWidth(0);
//    t1->SetTextAlign(12);
//    t1->AddText("CMS");
//    TPaveText* t2 = new TPaveText(.13, .9, .9, 1., "NDC");
//    t2->SetTextSize(.033);
//    t2->SetFillColor(0);
//    t2->SetFillStyle(0);
//    t2->SetLineWidth(0);
//    t2->SetTextAlign(12);
//    t2->SetTextFont(42);
//    t2->AddText("Phase-2 Simulation Preliminary, 14 TeV, 200 PU    Muon Tight ID Efficiency");
//
//    // Plot
//    TCanvas* c = new TCanvas();
//    c->SetLogy();
//    h->Draw("colz|text");
//    t1->Draw("same");
//    t2->Draw("same");
//    c->Print("eff-mu.pdf");
//}
