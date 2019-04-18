void scanSusyMassesNANOAOD(){

    // THIS IS NOT WORKING

    // Loop over position arguments, fill vector with root files
    std::vector<string> filenames;
    for (unsigned int i=0; i<gApplication->Argc(); ++i){
        //printf("a[%d]=%s\n", i, gApplication->Argv(i));
        if (string(gApplication->Argv(i)).find(".root") != std::string::npos){
            filenames.push_back(gApplication->Argv(i));
        }
    }

    for (unsigned int i=0; i<filenames.size(); ++i){
        printf("Open file %d from %lu.\n", i+1, filenames.size());

        TFile* f = new TFile(filenames[i].c_str());
        TTree* t = (TTree*)f->Get("Events");

        const unsigned int array_size = 9;

        UInt_t nGenPart;
        Float_t GenPart_mass[array_size],
                GenPart_pdgId[array_size];
        t->SetBranchAddress("GenPart_mass", &GenPart_mass);
        t->SetBranchAddress("GenPart_pdgId", &GenPart_pdgId);
        t->SetBranchAddress("nGenPart", &nGenPart);

        for (unsigned int j=0; j<t->GetEntries(); ++j){

            t->GetEntry(j);
            printf("nGenPart: %d\n", nGenPart);
            printf("Run: %d; Lumi: %d; Event: %d; genID: %f; gen2: %f; gen3: %f\n", 1, 2, 3, GenPart_pdgId[0], GenPart_pdgId[1], GenPart_pdgId[2]);

            for (unsigned int k=0; k<array_size; ++k){
                std::cout << "a: " << GenPart_pdgId[k] << std::endl;
                if (abs(GenPart_pdgId[k]) == 1000022){
                    std::cout << GenPart_mass[k] << std::endl;
                }
            }
            std::cout << "x: " << GenPart_mass << std::endl;
            std::cout << "y: " << GenPart_mass[0] << std::endl;
            std::cout << "y: " << GenPart_mass[1] << std::endl;
            std::cout << "z: " << *max_element(GenPart_mass , GenPart_mass + 9) << std::endl;
            abort();
        }
    }

}
//
//for idx in range(1, len(argv)):
//    print 'Open file {} from {}'.format(idx, len(argv)-1)
//    f = TFile(argv[idx])
//
//    treename = get_first_tree(f)
//    tree = f.Get(treename)
//
//    for event in tree:
//        genmass = list(event.GenPart_mass)
//        pdgid = list(event.GenPart_pdgId)
//        mn1 = mn2 = 0
//        for idx in range(len(genmass)):
//            if abs(pdgid[idx]) == 1000022:
//                mn1 = genmass[idx]
//            if abs(pdgid[idx]) == 1000024:
//                mn2 = genmass[idx]
//            if mn1 > 0 and mn2 > 0:
//                #masses.append((mn1, mn2))
//                masses.Fill(mn2, mn1, 1.)
//                break
//#print 'masses:', masses
//masses.Draw('COLZ')
//c.Print('scanSusyMassesNANOAOD.pdf')
//
//
//#Events->Scan("MaxIf$(GenPart_mass,abs(GenPart_pdgId)==1000022):MaxIf$(GenPart_mass,abs(GenPart_pdgId)==1000024)")
