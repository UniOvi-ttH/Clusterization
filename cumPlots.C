void cumPlots()
{
  TFile* f = TFile::Open("/nfs/fanae/user/vischia/www/tth/2017-02-28_12.00/cumulative_3l.root");
  gStyle->SetOptStat(0);
  TH1F* h = (TH1F*) f->Get("h_cumulative");
  h->GetYaxis()->SetTitle("Cumulative");
  h->GetXaxis()->SetTitle("Likelihood ratio");
  h->GetXaxis()->SetRangeUser(0.,5.);
  int k = 5;
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
  gSystem->Exec("mv ~vischia/www/tth/2017-02-28_12.00/cumulative_3l.png ~vischia/www/tth/2017-02-28_12.00/cumulative_3l_ugly.png");
  gSystem->Exec("mv ~vischia/www/tth/2017-02-28_12.00/cumulative_3l.pdf ~vischia/www/tth/2017-02-28_12.00/cumulative_3l_ugly.pdf");
  c->Print("~vischia/www/tth/2017-02-28_12.00/cumulative_3l.png");
  c->Print("~vischia/www/tth/2017-02-28_12.00/cumulative_3l.pdf");
  
}
