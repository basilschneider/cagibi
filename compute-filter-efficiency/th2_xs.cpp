std::string getP(int p){
    switch(p){
        case 1: return "#chi^{0}_{1}";
        case 2: return "#chi^{0}_{2}";
        case 3: return "#chi^{0}_{3}";
        case 4: return "#chi^{0}_{4}";
        case 5: return "#chi^{+}_{1}";
        case 6: return "#chi^{+}_{2}";
        case 7: return "#chi^{-}_{1}";
        case 8: return "#chi^{-}_{2}";
    }
    return "none";
}

void set_palette(){

    const Int_t n = 5;

    Double_t stops[n] = {0.00, 0.34, 0.61, 0.84, 1.00};
    Double_t red[n]   = {0.00, 0.00, 0.87, 1.00, 0.71};
    Double_t green[n] = {0.10, 0.81, 1.00, 0.20, 0.10};
    Double_t blue[n]  = {0.61, 1.00, 0.12, 0.00, 0.00};

    TColor::CreateGradientColorTable(n, stops, red, green, blue, 100);
    gStyle->SetNumberContours(100);
}

void th2_xs(){

    TH2F* h = new TH2F("Filter efficiency", "Filter efficiency", 8, 90., 250., 10, 250., 1250.);

    gStyle->SetPaintTextFormat(".3f");

    h->Fill(100, 1000, 0.05698);
    h->Fill(100, 300, 0.07331);
    h->Fill(100, 400, 0.07172);
    h->Fill(100, 500, 0.07242);
    h->Fill(100, 600, 0.06708);
    h->Fill(100, 800, 0.0639);
    h->Fill(120, 1000, 0.05683);
    h->Fill(120, 300, 0.0739733333333);
    h->Fill(120, 400, 0.07376);
    h->Fill(120, 500, 0.07193);
    h->Fill(120, 600, 0.0691);
    h->Fill(120, 800, 0.0644266666667);
    h->Fill(140, 1000, 0.05702);
    h->Fill(140, 300, 0.07441);
    h->Fill(140, 400, 0.07468);
    h->Fill(140, 500, 0.0739);
    h->Fill(140, 600, 0.06979);
    h->Fill(140, 800, 0.06288);
    h->Fill(160, 1000, 0.0584933333333);
    h->Fill(160, 300, 0.07472);
    h->Fill(160, 400, 0.07387);
    h->Fill(160, 500, 0.07408);
    h->Fill(160, 600, 0.07208);
    h->Fill(160, 800, 0.06507);
    h->Fill(180, 1000, 0.05812);
    h->Fill(180, 300, 0.07721);
    h->Fill(180, 400, 0.0755);
    h->Fill(180, 500, 0.07337);
    h->Fill(180, 600, 0.0718533333333);
    h->Fill(180, 800, 0.06292);
    h->Fill(200, 1000, 0.05849);
    h->Fill(200, 300, 0.0789066666667);
    h->Fill(200, 400, 0.07478);
    h->Fill(200, 500, 0.07434);
    h->Fill(200, 600, 0.0709);
    h->Fill(200, 800, 0.0651466666667);
    h->Fill(220, 1000, 0.05872);
    h->Fill(220, 300, 0.08363);
    h->Fill(220, 400, 0.0766933333333);
    h->Fill(220, 500, 0.07456);
    h->Fill(220, 600, 0.07238);
    h->Fill(220, 800, 0.06485);
    h->Fill(240, 1000, 0.0588933333333);
    h->Fill(240, 300, 0.08836);
    h->Fill(240, 400, 0.0772);
    h->Fill(240, 500, 0.0743466666667);
    h->Fill(240, 600, 0.07132);
    h->Fill(240, 800, 0.06552);

    h->SetStats(false);

    TCanvas* c = new TCanvas();
    c->SetRightMargin(.14);
        h->Draw("COLZ|text");
    c->SaveAs("filter-eff.pdf");
}
