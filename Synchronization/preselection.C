{

  TFile *f = TFile::Open("testNanoAOD_NANO.root");
  auto t1 = (TTree*)f->Get("Events");
  auto c1 = new TCanvas("c1","c1");

  // Preselection for Muon and Electrons from:
  // https://gitlab.cern.ch/ttH_leptons/doc/blob/master/Legacy/objects.md#2151-preselection

  // Electron

  t1->Draw("Electron_pt");
  c1->Print("Electron_pt_NoCuts.png");

  TCut ePt = "Electron_pt>7";
  TCut eEta = "abs(Electron_eta)<2.5";
  TCut eDxy = "Electron_dxy<=0.05";
  TCut eDz = "Electron_dz<0.1";
  TCut eMIso = "Electron_miniPFRelIso_all<0.4";
  TCut eSip3d = "Electron_sip3d<8.";
  TCut eWPLoose = "HLT_Ele25_eta2p1_WPLoose_Gsf";

  Int_t count = t1->Draw("Electron_pt",
                         ePt && eEta && eDxy && eDz
                         && eMIso && eSip3d && eWPLoose);
  cout << "Electron preselection events: " << count << endl;
  TH1F *hEle = (TH1F*)gPad->GetPrimitive("htemp");
  hEle->GetXaxis()->SetRangeUser(0.,300.);
  hEle->SetTitle("Electron Pt after Preselection;Pt;Counts");

  c1->Print("Electron_pt_PreselectionCuts.png");

  // Muon

  t1->Draw("Muon_pt");
  c1->Print("Muon_pt_NoCuts.png");

  TCut muPt = "Muon_pt>5";
  TCut muEta = "abs(Muon_eta)<2.4";
  TCut muDxy = "Muon_dxy<=0.05";
  TCut muDz = "Muon_dz<0.1";
  TCut muMIso = "";
  TCut muSip3d = "Muon_sip3d<8.";
  TCut nMuon = "nMuon>1";

  count = t1->Draw("Muon_pt",
                   muPt && muEta && muDxy && muDz
                   && muMIso && muSip3d && nMuon);
  cout << "Muon preselection events: " << count << endl;
  TH1F *hMu = (TH1F*)gPad->GetPrimitive("htemp");
  hMu->GetXaxis()->SetRangeUser(0.,300.);
  hMu->SetTitle("Muon Pt after Preselection;Pt;Counts");

  c1->Print("Muon_pt_PreselectionCuts.png");

  // Jets

  t1->Draw("Jet_pt");
  c1->Print("Jet_pt_NoCuts.png");

  TCut jetPt = "Jet_pt>25";
  TCut jetEta = "abs(Jet_eta)<2.4";

  count = t1->Draw("Jet_pt",
                   jetPt && jetEta);
  cout << "Jet preselection events: " <<  count << endl;
}
