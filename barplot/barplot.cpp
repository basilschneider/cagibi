void barplot(){
    TH1D* h = new TH1D("", "Excluded masses (model dependent)", 3, 0, 3);
    h->Fill(2., 2000.);
    h->Fill(1., 1000.);
    h->Fill(0., 350.);

    gStyle->SetOptStat(0);
    h->GetYaxis()->SetRangeUser(0., 2560.);
    h->GetXaxis()->SetNdivisions(3);
    h->GetYaxis()->SetNdivisions(80);
    h->GetXaxis()->SetLabelSize(0.);
    h->GetYaxis()->SetTickSize(0.);
    h->SetFillColor(kTeal+5);
    for (unsigned short int x=0; x<80; ++x){
        if (x==8 || x==21 || x==41){ continue; }
        h->GetYaxis()->ChangeLabel(x, -1., 0.);
    }

    TCanvas* c = new TCanvas();
    gPad->SetGridy();

    h->Draw("hbar0");

    TText* t1 = new TText(2050., 2.82, "Gluinos");
    TText* t2 = new TText(1050., 1.72, "Stops");
    TText* t3 = new TText(400., 0.88, "EWKinos");
    t1->SetTextAngle(-90.);
    t2->SetTextAngle(-90.);
    t3->SetTextAngle(-90.);
    t1->Draw();
    t2->Draw();
    t3->Draw();

    TLine* l1 = new TLine(350., 0., 350., 1.);
    TLine* l2 = new TLine(1000., 0., 1000., 2.);
    TLine* l3 = new TLine(2000., 0., 2000., 3.);
    l1->Draw();
    l2->Draw();
    l3->Draw();

    c->SaveAs("barplot.pdf");
}
