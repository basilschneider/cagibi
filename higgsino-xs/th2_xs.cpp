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

void th2_xs(std::string inputfile, std::string outputfolder){

    TH2F* h = new TH2F("h", "h", 8, 90., 250., 10, 250., 1250.);

    std::size_t pos = inputfile.find_last_of("/") + 1;
    std::string outputfile = outputfolder+"/xs13_" + inputfile.substr(pos+3) + ".pdf";
    std::ifstream ifs(inputfile, std::ios_base::in);
    std::string s;
    int mu, m1;
    double xs;

    double factor = 1000.;
    if (inputfile.find("_unc") != std::string::npos){
        // Uncertainty
        factor = 1.;
    }else if (inputfile.find("_kfac") != std::string::npos){
        // k-factor
        factor = 1.;
    }

    gStyle->SetPaintTextFormat(".3f");

    while(ifs >> s >> xs){
        mu = std::stoi(s.substr(9, 3));
        m1 = std::stoi(s.substr(13));
        h->Fill(mu, m1, factor*xs);
    }

    h->SetStats(false);
    h->GetXaxis()->SetTitle("#mu");
    h->GetYaxis()->SetTitle("M_{1}");

    set_palette();
    h->SetMarkerSize(2.);

    std::string title;
    if (inputfile.substr(pos, 7) == "xs_incl"){
        if (inputfile.find("kfac_unc") != std::string::npos){
            title = "k-factor uncertainty";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(0., .02);
        }else if (inputfile.find("kfac_avg") != std::string::npos){
            title = "averaged k-factor";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(.79, 2.4);
        }else if (inputfile.find("_unc") != std::string::npos){
            title = "#sigma_{inclusive}^{uncertainty} (13 TeV)";
            h->SetTitle(title.c_str());
        }else if (inputfile.find("_kfac") != std::string::npos){
            title = "overall k-factor";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(.79, 2.4);
        }else if (inputfile.find("_lo") != std::string::npos){
            title = "#sigma^{LO}_{inclusive} (13 TeV) [fb]";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(0., 16000.);
            gStyle->SetPaintTextFormat(".0f");
        }else{
            title = "#sigma^{NLO}_{inclusive} (13 TeV) [fb]";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(0., 16000.);
            gStyle->SetPaintTextFormat(".0f");
        }
    }else{
        int p1 = stoi(inputfile.substr(pos+3, 1));
        int p2 = stoi(inputfile.substr(pos+5, 1));
        if (inputfile.find("_unc") != std::string::npos){
            title = "#sigma_{" + getP(p1) + " " + getP(p2) + "}^{uncertainty} (13 TeV)";
            h->SetTitle(title.c_str());
        }else if (inputfile.find("_kfac") != std::string::npos){
            title = "k-factor_{" + getP(p1) + " " + getP(p2) + "}";
            h->SetTitle(title.c_str());
            h->GetZaxis()->SetRangeUser(.79, 2.4);
        }else if (inputfile.find("_lo") != std::string::npos){
            title = "#sigma^{LO}_{" + getP(p1) + " " + getP(p2) + "} (13 TeV) [fb]";
            h->SetTitle(title.c_str());
            if (h->GetMaximum() > 100.){
                gStyle->SetPaintTextFormat(".0f");
            }
            h->GetZaxis()->SetRangeUser(0., 3500.);
        }else{
            title = "#sigma^{NLO}_{" + getP(p1) + " " + getP(p2) + "} (13 TeV) [fb]";
            h->SetTitle(title.c_str());
            if (h->GetMaximum() > 100.){
                gStyle->SetPaintTextFormat(".0f");
            }
            h->GetZaxis()->SetRangeUser(0., 3500.);
        }
    }

    TCanvas* c = new TCanvas();
    c->SetRightMargin(.14);
        h->Draw("COLZ|text");
    c->SaveAs(outputfile.c_str());
}
