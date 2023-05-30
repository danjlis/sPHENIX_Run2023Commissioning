#define makeLL1Hist_cxx
#include "makeLL1Hist.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void makeLL1Hist::Loop()
{
   if (fChain == 0) return;
   
   Long64_t nentries = fChain->GetEntriesFast();
   
   TFile *wf = new TFile(Form("OutputHistLL1_RunNumber%d.root",RunNumber),"recreate");

   h_nhit_corr = new TH2D("h_nhit_corr",";N_{hit}^{north};N_{hit}^{south}",nhitbins,0,nhitbins,nhitbins,0,nhitbins);
   h_hit_check = new TH2D("h_hit_check",";N_{hit}^{north} sample index;N_{hit}^{south} sample index",3,8,11,3,8,11);

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;

      h_nhit_corr->Fill(nhit_n[idxhitn], nhit_s[idxhits]);
      h_hit_check->Fill(idxhitn,idxhits);
   }
   wf->cd();
   h_nhit_corr->Write();
   h_hit_check->Write();
   wf->Close();
}
