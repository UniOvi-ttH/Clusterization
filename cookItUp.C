void cookItUp()
{

  gStyle->SetOptFit(1111111);
  TFile* f = TFile::Open("data/2017-02-28_12.00/trees_for_opt_binning_3l_v6_withMEM/ev_3l_TTV.root");

  TTree* t = (TTree*) f->Get("t");

  TH2D* h = new TH2D("h", "withMEM;without MEM; with MEM", 101, -1., 1., 101, -1., 1.);

  TCanvas* c = new TCanvas("c", "c", 800, 800);
  //c->Divide(2);
  c->cd(1);
  t->Draw("kinMVA_3l_ttV_withMEM:kinMVA_3l_ttV >> h");
  h->Draw("col z");
  //c->cd(2);
  //TObjArray aSlices;
  TF1 *lin = new TF1("lin","[0]+[1]*x",-1.,1.);
  //h->Fit(lin, 0, -1, 0, "QR"FF, &aSlices);
  h->Fit(lin, "QR");
  //for(auto par : aSlices)
  //  par->Draw("same");
  //TProfile* p = h->ProfileX();
  //p->SetMarkerSize(1);
  //p->SetMarkerStyle(21);
  //p->SetMarkerColor(kRed);
  //p->SetLineColor(kRed);
  //p->Draw("PE SAME");
  c->Print("~/www/tth/2017-02-28_12.00/cookItUp.png");
  c->Print("~/www/tth/2017-02-28_12.00/cookItUp.pdf");
}
