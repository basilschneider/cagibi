void scan2(){

    const char path_file[] = "/nfs/dust/cms/group/susy-desy/Run2/MC/CMGtuples/basil/temp2/friends_v8_jecnom_metMuEGClean.root";
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
    Float_t MET, nBJet, HT, LT, nLep;

    t->SetBranchAddress("Event", &Event);
    t->SetBranchAddress("MET", &MET);
    t->SetBranchAddress("nBJet", &nBJet);
    t->SetBranchAddress("HT", &HT);
    t->SetBranchAddress("LT", &LT);
    t->SetBranchAddress("nLep", &nLep);

    for (unsigned int i=0; i<t->GetEntries(); ++i){
        t->GetEntry(i);

        if (Event != 505176792){ continue; }
        std::cout << "Event: " << Event
                  << "\nMET: " << MET
                  << "\nnBJet: " << nBJet
                  << "\nHT: " << HT
                  << "\nLT: " << LT
                  << "\nnLep: " << nLep
                  << std::endl;
        break;
    }

    return;
}
