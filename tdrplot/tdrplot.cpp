#include "TDRStyle.h"

void plot(std::string particle){
    TString s_file_in("./plots_2LSOS.root");
    TString s_h1(particle+"1_pt_TChiWZ_300_293_FullSim");
    TString s_h2(particle+"2_pt_TChiWZ_300_293_FullSim");
    TString s_out("tdrplot_"+particle+".pdf");
    TString s_axis_title, s_leg_title1, s_leg_title2;
    if (particle == "el"){
        s_axis_title = "p_{T} (e)";
        s_leg_title1 = "p_{T} (e_{1})";
        s_leg_title2 = "p_{T} (e_{2})";
    }else{
        s_axis_title = "p_{T} (#mu)";
        s_leg_title1 = "p_{T} (#mu_{1})";
        s_leg_title2 = "p_{T} (#mu_{2})";
    }


    TFile* file_in = new TFile(s_file_in);

    gStyle->SetOptStat(0);

    TH1D* h1 = (TH1D*)file_in->Get(s_h1);
    TH1D* h2 = (TH1D*)file_in->Get(s_h2);

    formatHisto(h1);
    formatHisto(h2);

    h1->Scale(1./h1->Integral());
    h2->Scale(1./h2->Integral());

    h1->SetMaximum(.7);
    h1->GetXaxis()->SetRangeUser(0., 30.);

    h1->SetTitle("");
    h1->GetXaxis()->SetTitle(s_axis_title);
    h1->SetLineColor(kBlue);
    h2->SetLineColor(kRed);
    h1->SetFillColorAlpha(kBlack, .0);
    h2->SetFillColorAlpha(kBlack, .0);

    TLegend* l = new TLegend(.8, .76, .9, .88);
    l->SetBorderSize(0.);
    l->AddEntry(h1, s_leg_title1, "L");
    l->AddEntry(h2, s_leg_title2, "L");

    TCanvas* c = setCanvas();

    h1->Draw("HIST");
    h2->Draw("HISTSAME");
    l->Draw();

    drawCMS();
    drawEnPu();

    c->SaveAs(s_out);
}
void tdrplot(){
    plot("el");
    plot("mu");
}
