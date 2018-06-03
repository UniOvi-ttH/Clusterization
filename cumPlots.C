TString dir("/nfs/fanae/user/vischia/www/tth/2017-02-28_12.00/mem_ext");


void prettyCum(Int_t nLep)
{
  TFile* f = TFile::Open(Form("%s/cumulative_%s.root", dir.Data(), nLep==3 ? "3l" : "2l"));
  gStyle->SetOptStat(0);
  TH1F* h = (TH1F*) f->Get("h_cumulative");
  h->GetYaxis()->SetTitle("Cumulative");
  h->GetXaxis()->SetTitle("Likelihood ratio");
  h->GetXaxis()->SetRangeUser(0.,5.);
  int k(nLep==3 ? 5 : 8);
  float yaxis[k];
  float xaxis[k];
  TGraph* graphs1[k];
  TGraph* graphs2[k];
  for (int n = 0; n < k; ++n){
    yaxis[n] = float(n+1)/k;
  }

  for (int bin = 0; bin < k; ++bin){
    float dist = 999.;
    int nearbin = -1;
    for (int bincum = 1; bincum < h->GetNbinsX()+1; bincum++){
      if (TMath::Abs(h->GetBinContent(bincum) - yaxis[bin]) < dist){
	dist = TMath::Abs(h->GetBinContent(bincum) - yaxis[bin]);
	nearbin = bincum;
      }
    }
    xaxis[bin] = h->GetBinCenter(nearbin);
    cout << nearbin << endl;
    graphs1[bin] = new TGraph(2);
    graphs1[bin]->SetPoint(0,0.,yaxis[bin]);
    graphs1[bin]->SetPoint(1,xaxis[bin],yaxis[bin]);
    graphs2[bin] = new TGraph(2);
    graphs2[bin]->SetPoint(0,xaxis[bin],yaxis[bin]);
    graphs2[bin]->SetPoint(1,xaxis[bin],0.);
  }

  TCanvas* c = new TCanvas("c","c", 800, 800);
  c->cd();
  h->SetLineWidth(2);
  h->Draw();
  for (int bin = 0; bin < k-1; ++bin){
    graphs1[bin]->SetLineColor(kRed);
    graphs2[bin]->SetLineColor(kRed);
    graphs1[bin]->SetLineWidth(2);
    graphs2[bin]->SetLineWidth(2);
    graphs1[bin]->Draw("L,same");
    graphs2[bin]->Draw("L,same");
  }
  gSystem->Exec(Form("mv %s/cumulative_%s.png %s/cumulative_%s_ugly.png", dir.Data(), nLep==3 ? "3l" : "2lss", dir.Data(), nLep==3 ? "3l" : "2lss"));
  gSystem->Exec(Form("mv %s/cumulative_%s.pdf %s/cumulative_%s_ugly.pdf", dir.Data(), nLep==3 ? "3l" : "2lss", dir.Data(), nLep==3 ? "3l" : "2lss"));
  c->Print(Form("%s/cumulative_%s.png", dir.Data(), nLep==3 ? "3l" : "2lss"));
  c->Print(Form("%s/cumulative_%s.pdf", dir.Data(), nLep==3 ? "3l" : "2lss"));
  
}

void cumPlots()
{
  prettyCum(3);
  prettyCum(2);
}
