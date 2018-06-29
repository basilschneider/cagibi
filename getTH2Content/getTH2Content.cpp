void getTH2Content(TString filename, TString histoname){

    TFile* f = new TFile(filename);
    TH2D* h = (TH2D*)f->Get(histoname);

    double x_width = (h->GetXaxis()->GetXmax() - h->GetXaxis()->GetXmin())/h->GetNbinsX();
    double y_width = (h->GetYaxis()->GetXmax() - h->GetYaxis()->GetXmin())/h->GetNbinsY();

    for (size_t x=0; x<h->GetNbinsX(); ++x){
        for (size_t y=0; y<h->GetNbinsY(); ++y){
            if (h->GetBinContent(x, y) == 0){ continue; }
            printf("x/y: %6.1f/%6.1f: %10.2f\n", (x-1)*x_width, (y-1)*y_width, h->GetBinContent(x, y));
        }
    }

    return;
}
