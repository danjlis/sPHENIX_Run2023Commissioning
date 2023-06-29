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

   float binstart = -0.5;
   float binend = 64.5;
   float binend2 = 32.5;

   h_line_up = new TH2D("h_line_up",";Sample;Channel", 20, -0.5, 19.5, 60, -0.5, 59.5);
   h_nhit_corr = new TH2D("h_nhit_corr",";N_{hit}^{north};N_{hit}^{south}",nhitbins, binstart, binend, nhitbins, binstart, binend);
   h_nhit_n_corr = new TH2D("h_nhit_n_corr",";N_{hit}^{N1};N_{hit}^{N2}",nhitbins/2 + 1,binstart,binend2,nhitbins/2+1,binstart,binend2);
   h_nhit_s_corr = new TH2D("h_nhit_s_corr",";N_{hit}^{S1};N_{hit}^{S2}",nhitbins/2 + 1,binstart,binend2, nhitbins/2+1,binstart,binend2);
   h_nhit_n1 = new TH1D("h_nhit_n1",";N_{hit}^{N1};counts", nhitbins/2 + 1, binstart,binend2);
   h_nhit_n2 = new TH1D("h_nhit_n2",";N_{hit}^{N2};counts", nhitbins/2 + 1, binstart,binend2);
   h_nhit_s1 = new TH1D("h_nhit_s1",";N_{hit}^{S1};counts", nhitbins/2 + 1, binstart,binend2);
   h_nhit_s2 = new TH1D("h_nhit_s2",";N_{hit}^{S2};counts", nhitbins/2 + 1, binstart,binend2);
   h_hit_check = new TH2D("h_hit_check",";N_{hit}^{north} sample index;N_{hit}^{south} sample index",3,8,11,3,8,11);
   h_time_diff = new TH1D("h_time_diff",";time_diff;counts", 50, -0.5, 300);

   Long64_t nbytes = 0, nb = 0;
   int id;
   int thresh = 2;
   int bad = 0;

   for (Long64_t jentry=0; jentry<(nentries < 1000000? nentries: 1000000);jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) < 0) continue;

      if (nhit_n[9] >= thresh && nhit_s[9] >= thresh){
	id = 9;
      }
      else if (nhit_n[idxhitn] >= thresh && nhit_s[idxhitn] >= thresh){
	id = idxhitn;
      }
      else if (nhit_n[idxhits] >= thresh && nhit_s[idxhits] >= thresh){
	id = idxhits;
      }
      else{
	// cout <<"Entry: "<<jentry<<" wasn't supposed to trigger..."<<endl;
	// cout <<"North peak "<<idxhitn<<": Nhit_N = "<<nhit_n[idxhitn]<<", Nhit_S = "<<nhit_s[idxhitn]<<endl;
 	// cout <<"North peak "<<idxhits<<": Nhit_N = "<<nhit_n[idxhits]<<", Nhit_S = "<<nhit_s[idxhits]<<endl;
	// cout <<"North peak "<<9<<": Nhit_N = "<<nhit_n[9]<<", Nhit_S = "<<nhit_s[9]<<endl;
	// for (int ic = 0 ; ic < 52; ic++)
	//   {
	//     cout <<dec <<"ch "<<ic<<" | ";
	//     for (int is = 0; is < 20; is++)
	//       {
	// 	cout << hex <<setw(4) << channel[ic][is]<<" ";
	//       }
	//     cout <<" "<<endl;
	//   }

	
	// for (int ic = 0 ; ic < 8; ic++)
	//   {
	//     cout <<dec <<"tr "<<ic<<" | ";
	//     for (int is = 0; is < 20; is++)
	//       {
	// 	cout << hex <<setw(4)<< triggerwords[ic][is]<<" ";
	//       }
	//     cout <<" "<<endl;
	//   }
	// cin >> id;
	bad++;
	id = 9;
	//	continue;
      }


      h_nhit_corr->Fill(nhit_n[id], nhit_s[id]);
      h_nhit_n_corr->Fill(nhit_n1[id], nhit_n2[id]);
      h_nhit_s_corr->Fill(nhit_s1[id], nhit_s2[id]);
      h_nhit_n1->Fill(nhit_n1[id]);
      h_nhit_n2->Fill(nhit_n2[id]);
      h_nhit_s1->Fill(nhit_s1[id]);
      h_nhit_s2->Fill(nhit_s2[id]);

      // if (nhit_s1[id] >= 31 && nhit_s2[id] >= 31 && nhit_n1[id] >= 31 && nhit_n2[id] >= 31){
      // 	cout << "ALL HIT: "<< jentry << endl;
      // 	cout << "s1: "<< nhit_s1[id] << endl;
      // 	cout << "s2: "<< nhit_s2[id] << endl;
      // 	cout << "n1: "<< nhit_n1[id] << endl;
      // 	cout << "n2: "<< nhit_n2[id] << endl;

      // }
      h_time_diff->Fill(triggerwords[6][id]);
      for (int is = 0; is < nSamples; is++)
	{ 
	  for (int ic = 0; ic < nChannels; ic++)
	    {
	      h_line_up->Fill(is, 60 - ic, channel[ic][is]);
	    }
	  for (int ic = 0; ic < 8; ic++)
	    {
	      h_line_up->Fill(is, 8 - ic, triggerwords[ic][is]);
	    }

	}

   }
   wf->cd();
   h_nhit_corr->Write();
   h_nhit_n_corr->Write();
   h_nhit_s_corr->Write();
   h_nhit_n1->Write();
   h_nhit_n2->Write();
   h_nhit_s1->Write();
   h_nhit_s2->Write();
   h_hit_check->Write();
   h_line_up->Write();
   h_time_diff->Write();
   wf->Close();
   cout << "Shouldn't have passed: " << bad << " / "<<nentries<<endl;
}
