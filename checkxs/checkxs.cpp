float checkxs(TString path){
    TFile* f = new TFile(path);
    TLeaf* l = ((TTree*)f->Get("sf/t"))->GetLeaf("Xsec");
    l->GetBranch()->GetEntry(0);
    return l->GetValue();
}
