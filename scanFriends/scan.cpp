void scan(){

    const char path_file[] = "friends_v10_data.root";
    const char path_tree[] = "sf/t";

    TFile *f = new TFile(path_file, "READ");
    TTree *t = (TTree*)f->Get(path_tree);

    //t->Scan("Event",
    //        "nLep==1 \
    //            && Lep_pt>25 \
    //            && Selected==1 \
    //            && nVeto==0 \
    //            && (!isData || (HLT_EleOR || HLT_MuOR || HLT_MetOR)) \
    //            && (!isData || ( (PD_SingleEle && HLT_EleOR) || (PD_SingleMu && (HLT_MuOR) && !(HLT_EleOR) ) || (PD_MET && (HLT_MetOR) && !(HLT_EleOR) && !(HLT_MuOR)))) \
    //            && (!isData || METfilters == 1) \
    //            && !iso_Veto \
    //            && RA2_muJetFilter == 1 \
    //            && nJets30Clean >= 6 && nJets30Clean <= 8 \
    //            && Jet2_pt > 80 \
    //            && HT > 500 && HT < 1000 \
    //            && LT > 250 && LT < 450 \
    //            && nBJet == 2 \
    //            && dPhi > 1.");

    Long64_t Event;
    Float_t Run;
    Float_t Lumi;
    Float_t nLep;
    Float_t Lep_pt;
    Float_t Selected;
    Float_t nVeto;
    Float_t isData;
    Float_t HLT_EleOR;
    Float_t HLT_MuOR;
    Float_t HLT_MetOR;
    Float_t PD_SingleEle;
    Float_t PD_SingleMu;
    Float_t PD_MET;
    Float_t METfilters;
    Float_t iso_Veto;
    Float_t RA2_muJetFilter;
    Float_t nJets30Clean;
    Float_t Jet2_pt;
    Float_t HT;
    Float_t LT;
    Float_t nBJet;
    Float_t dPhi;

    t->SetBranchAddress("Event", &Event);
    t->SetBranchAddress("Run", &Run);
    t->SetBranchAddress("Lumi", &Lumi);
    t->SetBranchAddress("nLep", &nLep);
    t->SetBranchAddress("Lep_pt", &Lep_pt);
    t->SetBranchAddress("Selected", &Selected);
    t->SetBranchAddress("nVeto", &nVeto);
    t->SetBranchAddress("isData", &isData);
    t->SetBranchAddress("HLT_EleOR", &HLT_EleOR);
    t->SetBranchAddress("HLT_MuOR", &HLT_MuOR);
    t->SetBranchAddress("HLT_MetOR", &HLT_MetOR);
    t->SetBranchAddress("PD_SingleEle", &PD_SingleEle);
    t->SetBranchAddress("PD_SingleMu", &PD_SingleMu);
    t->SetBranchAddress("PD_MET", &PD_MET);
    t->SetBranchAddress("METfilters", &METfilters);
    t->SetBranchAddress("iso_Veto", &iso_Veto);
    t->SetBranchAddress("RA2_muJetFilter", &RA2_muJetFilter);
    t->SetBranchAddress("nJets30Clean", &nJets30Clean);
    t->SetBranchAddress("Jet2_pt", &Jet2_pt);
    t->SetBranchAddress("HT", &HT);
    t->SetBranchAddress("LT", &LT);
    t->SetBranchAddress("nBJet", &nBJet);
    t->SetBranchAddress("dPhi", &dPhi);

    unsigned int counter = 0;

    for (unsigned int i=0; i<t->GetEntries(); ++i){
        t->GetEntry(i);

        if (nLep != 1){ continue; }
        if (Lep_pt <= 25){ continue; }
        if (Selected != 1){ continue; }
        if (nVeto != 0){ continue; }
        if (!(!isData || (HLT_EleOR || HLT_MuOR || HLT_MetOR))){ continue; }
        if (!(!isData || ( (PD_SingleEle && HLT_EleOR) || (PD_SingleMu && (HLT_MuOR) && !(HLT_EleOR) ) || (PD_MET && (HLT_MetOR) && !(HLT_EleOR) && !(HLT_MuOR))))){ continue; }
        if (!(!isData || METfilters == 1)){ continue; }
        if (iso_Veto){ continue; }
        if (RA2_muJetFilter != 1){ continue; }
        //if (nJets30Clean < 6 || nJets30Clean > 8){ continue; }
        if (nJets30Clean < 9){ continue; }
        if (Jet2_pt <= 80){ continue; };
        if (HT <= 500 || HT > 1500){ continue; }
        if (LT <= 250 || LT > 450){ continue; }
        if (nBJet <= 2){ continue; }
        if (dPhi <= 1.){ continue; }

        //std::cout << i << " - " << Event << std::endl;
        //std::cout << "HT: " << HT << " - LT: " << LT << std::endl;
        std::cout << i << " - " << "Run: " << Run << " - Lumi: " << Lumi << " - Event: " << Event << std::endl;
        counter++;
    }

    std::cout << "Counter: " << counter << std::endl;;

    return;
}
