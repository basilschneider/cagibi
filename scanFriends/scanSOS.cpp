void scanSOS(){

    const char path_file[] = "DYJetsToLL_M5to50_HT100to200.root";
    const char path_tree[] = "tree";

    TFile *f = new TFile(path_file, "READ");
    TTree *t = (TTree*)f->Get(path_tree);

    const unsigned int array_size = 13;

    Int_t nLepGood, nGenPart, nJet, ngenLep;
    Int_t LepGood_pdgId[array_size],
          GenPart_pdgId[array_size],
          genLep_pdgId[array_size],
          GenPart_status[array_size],
          genLep_status[array_size];
    Float_t GenPart_pt[array_size],
            GenPart_eta[array_size],
            GenPart_phi[array_size],
            Jet_pt[array_size],
            Jet_eta[array_size],
            Jet_phi[array_size],
            LepGood_pt[array_size],
            LepGood_eta[array_size],
            LepGood_phi[array_size],
            genLep_pt[array_size],
            genLep_phi[array_size],
            genLep_eta[array_size],
            LepGood_relIso03[array_size];
    Float_t met_pt, met_eta, met_phi;
    UInt_t run, lumi;
    ULong64_t evt;

    t->SetBranchAddress("nLepGood", &nLepGood);
    t->SetBranchAddress("nGenPart", &nGenPart);
    t->SetBranchAddress("nJet", &nJet);
    t->SetBranchAddress("ngenLep", &ngenLep);
    t->SetBranchAddress("LepGood_pdgId", &LepGood_pdgId);
    t->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
    t->SetBranchAddress("genLep_pdgId", &genLep_pdgId);
    t->SetBranchAddress("GenPart_status", &GenPart_status);
    t->SetBranchAddress("genLep_status", &genLep_status);
    t->SetBranchAddress("GenPart_pt", &GenPart_pt);
    t->SetBranchAddress("GenPart_eta", &GenPart_eta);
    t->SetBranchAddress("GenPart_phi", &GenPart_phi);
    t->SetBranchAddress("Jet_pt", &Jet_pt);
    t->SetBranchAddress("Jet_eta", &Jet_eta);
    t->SetBranchAddress("Jet_phi", &Jet_phi);
    t->SetBranchAddress("LepGood_pt", &LepGood_pt);
    t->SetBranchAddress("LepGood_eta", &LepGood_eta);
    t->SetBranchAddress("LepGood_phi", &LepGood_phi);
    t->SetBranchAddress("genLep_pt", &genLep_pt);
    t->SetBranchAddress("genLep_eta", &genLep_eta);
    t->SetBranchAddress("LepGood_relIso03", &LepGood_relIso03);
    t->SetBranchAddress("genLep_phi", &genLep_phi);
    t->SetBranchAddress("met_pt", &met_pt);
    t->SetBranchAddress("met_eta", &met_eta);
    t->SetBranchAddress("met_phi", &met_phi);
    t->SetBranchAddress("run", &run);
    t->SetBranchAddress("lumi", &lumi);
    t->SetBranchAddress("evt", &evt);

    unsigned int counter = 0;

    for (unsigned int i=0; i<t->GetEntries(); ++i){

        t->GetEntry(i);

        if (!(nLepGood == 2 && abs(LepGood_pdgId[0]) == 13 && abs(LepGood_pdgId[1]) == 13)){ continue; }
        if (LepGood_pt[0] < 5 || LepGood_pt[0] > 30){ continue; }
        if (LepGood_pt[1] < 5 || LepGood_pt[1] > 30){ continue; }

        printf("NEW EVENT\n");
        printf("Run: %d; Lumi: %d; Event: %lld; genID: %d\n", run, lumi, evt, GenPart_pdgId[0]);
        for (unsigned int j=0; j<nGenPart; ++j){
            //printf("GenParts: %d/%d\n", j, nGenPart);
            //printf("PID: %d\n", GenPart_pdgId[j]);
            //printf("Status: %d\n", GenPart_status[j]);
            //printf("pT: %f\n", GenPart_pt[j]);
            //printf("eta: %f\n\n", GenPart_eta[j]);
            printf("GenParts: %d/%d; PID: %d; Status: %d; pT: %f; eta: %f; phi: %f\n",
                   j+1, nGenPart, GenPart_pdgId[j], GenPart_status[j], GenPart_pt[j], GenPart_eta[j], GenPart_phi[j]);
        }
        for (unsigned int j=0; j<ngenLep; ++j){
            printf("GenLep: %d/%d: ID: %d; Status: %d; pt: %f; eta: %f; phi: %f\n",
                   j+1, ngenLep, genLep_pdgId[j], genLep_status[j], genLep_pt[j], genLep_eta[j], genLep_phi[j]);
        }
        for (unsigned int j=0; j<nJet; ++j){
            printf("RecoJet: %d/%d; pt: %f; eta: %f; phi: %f\n", j+1, nJet, Jet_pt[j], Jet_eta[j], Jet_phi[j]);
        }
        for (unsigned int j=0; j<nLepGood; ++j){
            printf("RecoLep: %d/%d; ID: %d; pt: %f; eta: %f; phi: %f; iso: %f\n",
                   j+1, nLepGood, LepGood_pdgId[j], LepGood_pt[j], LepGood_eta[j], LepGood_phi[j], LepGood_relIso03[j]*LepGood_pt[j]);
        }
        printf("MET: pt: %f; eta: %f; phi: %f\n", met_pt, met_eta, met_phi);
        std::cout << std::endl;
        counter++;
        if (counter >= 10){ break; }
    }

    std::cout << "Counter: " << counter << std::endl;;

    return;
}
