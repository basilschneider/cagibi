void openTree(TString filename){
    TFile* f = new TFile(filename);
    TTree* t = (TTree*)f->Get("Delphes");
    std::cout << "TTree in " << filename << " has " << t->GetEntries() << " events." << std::endl;
}
