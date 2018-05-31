#include "/nfs/fanae/user/vischia/workarea/cmssw/tthMultilepton/Clusterization/RecursiveClustering.h"
#include "/nfs/fanae/user/vischia/workarea/cmssw/tthMultilepton/Clusterization/LikeliHOOD.h"

#include <TTree.h>
#include <TBranch.h>

#include <TMVA/Reader.h>
#include <TFile.h>
#include <TApplication.h>
#include <TSystem.h>


void runDaClusterfuck(TString iDir, TString dataset, TString version, Int_t nLeps)
{
  TString iFile(iDir+"/bdtDump_"+dataset+"_"+colour+".root");
  TString oDir(iDir+"/out_"+version);

  TString cfDir("/nfs/fanae/user/vischia/workarea/cmssw/tthMultilepton/Clusterization/");
  //gSystem->CompileMacro(cfDir+"RecursiveClustering.C++");
  //gSystem->Load(cfDir+"RecursiveClustering_C.so");
  cout << "Clustering recursive for " << nLeps << " leptons." << endl;

  RecursiveClustering g(2, nLeps, "root", 1); // Trial 1 does not save voronoi pdf. Run once as a sanity check, then go for 0
  cout << "Clustered, with ";
  Int_t nBins(g.GetFinalNbins());
  cout << nBins << " bins." <<  endl;
  //gSystem->CompileMacro(cfDir+"LikeliHOOD.C++");
  //gSystem->Load(cfDir+"LikeliHOOD_C.so");
  LikeliHOOD l(iDir, nBins, nLep, "root", 1);
  l.Test();
  l.VoronoiPlot();

  gSystem->Exec(Form("mkdir %s",oDir.Data()));
  gSystem->Exec(Form("mv cumulative* %s",oDir.Data()));
  gSystem->Exec(Form("mv likelihoodBased* %s",oDir.Data()));
  gSystem->Exec(Form("mv binning_* %s",oDir.Data()));

}
      
void clusterfuckOfAwesomeness(TString iDir, TString version)
{
  vector<Int_t> leps;
  leps.push_back(2);
  leps.push_back(3);

  for(auto& l : leps)
    runDaClusterfuck(iDir,training, version, l);

  cout << "\t Done clustering leptons" << endl;
  gApplication->Terminate();
}

//  LocalWords:  LF

