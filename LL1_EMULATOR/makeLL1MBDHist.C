#define makeLL1MBDHist_cxx

#include "makeLL1MBDHist.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void makeLL1MBDHist::Loop(bool onlyMBD = false)
{
  if (fChain_mbd == 0) return;
  if (fChain_ll1 == 0 && !onlyMBD) return;

  Long64_t nentries;
  if (onlyMBD) nentries = fChain_mbd->GetEntriesFast();
  else nentries = min(fChain_ll1->GetEntriesFast(), fChain_mbd->GetEntriesFast());
  std::cout <<" In it: "<<nentries<<std::endl;   
  TFile *wf = new TFile(Form("OutputHistLL1MBD_RunNumber%d_%d.root",RunNumberLL1, RunNumberMBD),"recreate");
   
  Long64_t nbytesmbd = 0, nbmbd = 0;
  Long64_t nbytesll1 = 0, nbll1 = 0;
  int id;
  int hitmap[128];
  unsigned int trig[60][25];
  int thresh = 2;

  h_hitmap_n = new TEfficiency("h_hitmap_n",";PMT_{North};<HIT>", 64, -0.5, 63.5);
  h_hitmap_s = new TEfficiency("h_hitmap_s",";PMT_{South};<HIT>", 64, -0.5, 63.5);
  pEff_emulate = new TEfficiency("h_eff_emulate",";N_{HIT}^{NORTH};N_{HIT}^{SOUTH};#epsilon",65,-0.5,64.5,65,-0.5,64.5);
  h_line_up = new TH2D("h_line_up",";sample;channel",7, -0.5, 6.5, 60, -0.5, 59.5);
  h_nhit_emu = new TH2D("h_nhit_emu",";N_{HIT}^{NORTH};N_{HIT}^{SOUTH}",65, -0.5, 64.5, 65, -0.5, 64.5);

  h_nhit_n1 = new TH1D("h_nhit_n1",";N_{HIT}^{NORTH1};", 33, -0.5, 32.5);
  h_nhit_n2 = new TH1D("h_nhit_n2",";N_{HIT}^{NORTH2};", 33, -0.5, 32.5);
  h_nhit_s1 = new TH1D("h_nhit_s1",";N_{HIT}^{SOUTH1};", 33, -0.5, 32.5);
  h_nhit_s2 = new TH1D("h_nhit_s2",";N_{HIT}^{SOUTH2};", 33, -0.5, 32.5);

  h_hitdiff_n = new TH1D("h_hitdiff_n",";Hit_{Trig} - Hit_{EMU}; counts", 129, -64.5, 64.5);
  h_hitdiff_s = new TH1D("h_hitdiff_s",";Hit_{Trig} - Hit_{EMU}; counts", 129, -64.5, 64.5);
  h_nhit_emu_bad = new TH2D("h_nhit_emu_bad",";N_{HIT}^{NORTH};N_{HIT}^{SOUTH}",65, -0.5, 64.5, 65, -0.5, 64.5);

  h_mbd_vtx = new TH1D("h_mbd_vtx",";cm;arb",100, -200, 200);
  h_mbd_vtx_cut = new TH1D("h_mbd_vtx_cut",";cm;arb",100, -200, 200);

  Long64_t jentry_mbd = 0;
  Long64_t jentry_ll1 = 0;
  Long64_t jentry = 0;
  int idxem = 12;
  int idxemax = 0;
  unsigned int emax = 0;
  int bad = 0;
  int nen = 0;

  int nSkip = 0;
  bool leave = false;
  while (jentry<10000 && !leave){//nentries) {

    //    Long64_t ientry = LoadTree(jentry);

    //if (ientry < 0) break;

    nbmbd = fChain_mbd->GetEntry(jentry_mbd);   nbytesmbd += nbmbd;

    if (!onlyMBD) nbll1 = fChain_ll1->GetEntry(jentry_ll1);   nbytesll1 += nbll1;
    //if (Cut(ientry) < 0) continue;
    if (!onlyMBD && femclock[0] != ll1clock - 8) {
      std::cout << "CLOCKS! :"<<femclock[0] << " " << ll1clock << std::endl;
    }

    
    while ( !onlyMBD && femevtnr[0] != ll1evtnr)
      {

	if (nSkip>5) 
	  {
	    leave = true;
	    break;
	  }
	nSkip++;
	cout <<"Out of sync at "<<jentry<<": "<<femevtnr[0] << " - "<< ll1evtnr <<endl;
	if (femevtnr[0] < ll1evtnr)
	  {
	    jentry_mbd++;
	    nbmbd = fChain_mbd->GetEntry(jentry_mbd);   nbytesmbd += nbmbd;
	  }
	else
	  { 
	    jentry_ll1++;
	    nbll1 = fChain_ll1->GetEntry(jentry_ll1);   nbytesll1 += nbll1;
	  }
	continue;
      }
    nSkip=0;
    jentry_mbd++;
    if (!onlyMBD) jentry_ll1++;
    jentry++;

    for (int ic = 0; ic < 128; ic++) hitmap[ic] = 0;

    EmulateTrigger(adc, trig, hitmap);

    if (!onlyMBD)
      {      
	if (nhit_n[9] >= thresh && nhit_s[9] >= thresh){
	  id = 9;
	}
	else if (nhit_n[idxhitn] >= thresh && nhit_s[idxhitn] >= thresh){
	  id = idxhitn;
	}
	else if (nhit_n[idxhits] >= thresh && nhit_s[idxhits] >= thresh){
	  id = idxhits;
	}
	else id = 9;;
      }   

    pEff_emulate->Fill((trig[54][idxem] >= thresh && trig[55][idxem] >= thresh), nhit_n[id], nhit_s[id]);
    if (!(trig[54][idxem] >= thresh && trig[55][idxem] >= thresh)) h_nhit_emu_bad->Fill( nhit_n[id], nhit_s[id]);
    if (!onlyMBD)
      {
	h_hitdiff_n->Fill(nhit_n[id] - static_cast<int>(trig[55][idxem]));
	h_hitdiff_s->Fill(nhit_s[id] - static_cast<int>(trig[54][idxem]));
      }
    h_nhit_emu->Fill(trig[55][idxem],trig[54][idxem]);

    h_nhit_s1->Fill(trig[8][idxem]);
    h_nhit_s2->Fill(trig[21][idxem]);
    h_nhit_n1->Fill(trig[34][idxem]);
    h_nhit_n2->Fill(trig[47][idxem]);

    for (int ic = 0; ic < 60; ic++)
      {
	emax = 0;
	idxemax = -1;
	for (int is = 0 ; is < 7; is++)
	  {
	    if (trig[ic][is] > emax)
	      {
		emax = trig[ic][is];
		idxemax = is;
	      }
	  }
	if (idxemax != -1) h_line_up->Fill(idxemax, 59 - ic);
      }
    for (int ic = 0; ic < 64; ic++)
      {
	h_hitmap_n->Fill(hitmap[ic], ic);
	h_hitmap_s->Fill(hitmap[ic+64], ic);
      }
    float vtx = GetVertexZ(peak);

    if (trig[54][idxem] >= thresh && trig[55][idxem] >= thresh)
      {
	bad++;
	h_mbd_vtx_cut->Fill(vtx);
      }
    else if (!onlyMBD && !(nhit_n[id] < thresh && nhit_s[id] < thresh)) cout << "nothing? "<< dec <<ll1evtnr << " "<<endl;;
    h_mbd_vtx->Fill(vtx);
    nen++;
  }

  cout <<bad<<" / "<<nen<<endl;
  wf->cd();
  h_hitdiff_s->Write();
  h_hitdiff_n->Write();
  h_line_up->Write();
  h_nhit_emu->Write();
  h_nhit_emu_bad->Write();
  h_nhit_n1->Write();
  h_nhit_n2->Write();
  h_nhit_s1->Write();
  h_nhit_s2->Write();
  std::cout << __LINE__<< std::endl;
  h_mbd_vtx->Write();
  std::cout << __LINE__<< std::endl;
  h_mbd_vtx_cut->Write();
  std::cout << __LINE__<< std::endl;
  h_hitmap_n->Write();
  h_hitmap_s->Write();
  pEff_emulate->Write();

  wf->Close();
}


void makeLL1MBDHist::One(int event = 10, bool onlyMBD = false)
{
  if (fChain_mbd == 0) return;
  if (!onlyMBD && fChain_ll1 == 0) return;
   
  Long64_t nentries;
  if (onlyMBD) nentries = fChain_mbd->GetEntriesFast();
  else nentries = min(fChain_ll1->GetEntriesFast(), fChain_mbd->GetEntriesFast());
   
  Long64_t nbytesmbd = 0, nbmbd = 0;
  Long64_t nbytesll1 = 0, nbll1 = 0;
  int hitmap[128];
  unsigned int trig[60][25];
  int idxem = 5;   
  for (Long64_t jentry=event; jentry<event+1;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nbmbd = fChain_mbd->GetEntry(jentry);   nbytesmbd += nbmbd;
    if (!onlyMBD) nbll1 = fChain_ll1->GetEntry(jentry);   nbytesll1 += nbll1;
    if (Cut(ientry) < 0) continue;


    while (!onlyMBD && femevtnr[0] != ll1evtnr)
      {
	jentry++;
	nbmbd = fChain_mbd->GetEntry(jentry);   nbytesmbd += nbmbd;
	continue;
      }
    if (!onlyMBD)
      {
	for (int ic = 0; ic < nChannelsLL1; ic++)
	  {
	    if (ic%13==0) cout <<" -----------------------------------------------------------"<<endl;
	    cout <<"ch "<<dec<<ic<<" | ";
	    for (int is = 0; is < nSamplesLL1; is++)
	      { 
		cout << " "<<hex<<setw(4)<<channel[ic][is];
	      }
	    cout <<" "<<endl;
	  }
	cout <<" -----------------------------------------------------------"<<endl;
	for (int ic = 0; ic < 8; ic++)
	  {
	    cout <<"tr "<<dec<<ic<<" | ";
	    for (int is = 0; is < nSamplesLL1; is++)
	      { 
		cout << " "<<hex<<setw(4)<<triggerwords[ic][is];
	      }
	    cout <<" "<<endl;
	  
	  }
      }
    EmulateTrigger(adc, trig, hitmap);
    cout <<"Emulator: "<<endl;
    if (!onlyMBD) cout << dec <<"evt ll1/mbd: "<< ll1evtnr << " / "<<femevtnr[0]<<endl;
    cout <<"FEMS: ";
    for (int ib = 0; ib < 4; ib++) cout << femslot[ib]<<" ";
    cout <<" "<<endl;
    for (int ib = 0; ib < 4; ib++)
      {
	cout <<" -----------------------------------------------------------"<<endl;
	for (int ic = 0; ic < 8; ic++)
	  {

	    cout <<" "<<dec<<"Q"<<ic<<" | ";
	    for (int ig = 0; ig < 20; ig++)
	      {
		cout << " "<<hex<<setw(4)<<trig[ib*13 + ic][ig];
	      }
	    cout <<" "<<endl;
	  }
	cout <<" "<<dec<<"NH | ";
	for (int ig = 0; ig < 20; ig++)
	  {
	    cout << " "<<hex<<setw(4)<<trig[ib*13 + 8][ig];
	  }
	cout <<" "<<endl;
	for (int ic = 0; ic < 4; ic++)
	  {
	    cout <<" "<<dec<<"T"<<ic<<" | ";
	    for (int ig = 0; ig < 20; ig++)
	      {
		cout << " "<<hex<<setw(4)<<trig[ib*13 + 9 + ic][ig];
	      }
	    cout <<" "<<endl;
	  }
      }
    cout <<" -----------------------------------------------------------"<<endl;
    for (int ic = 0; ic < 8; ic++)
      {
	cout <<" "<<dec<<"W"<<ic<<" | ";
	for (int ig = 0; ig < 20; ig++)
	  {
	    cout << " "<<hex<<setw(4)<<trig[52 + ic][ig];
	  }
	cout <<" "<<endl;
      }
    cout <<" -----------------------------------------------------------"<<endl;
  }

}
