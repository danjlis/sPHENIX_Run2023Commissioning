//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu May 18 21:30:10 2023 by ROOT version 6.26/06
// from TTree W/Waveform digitizer raw data
// found on file: /sphenix/user/dlis/Projects/fit_emcal/root_mbd/calib-00007009-0000.root
//////////////////////////////////////////////////////////

#ifndef makeMBDhist_h
#define makeMBDhist_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "runinfo.h"
#include "../Utility/Style_jaebeom.h"

// Header file for the classes stored in the TTree if any.

class makeMBDhist {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           evtnr;
   Int_t           clock;
   Int_t           femslot[4];
   Int_t           femevtnr[4];
   Int_t           femclock[4];
   Int_t           adc[256][31];
   Float_t         mean[256];
   Float_t         rms[256];
   Int_t           minadc[256];
   Int_t           maxadc[256];
   Float_t         pedestal[256];
   Float_t         pedsig[256];
   Float_t         peak[256];
   Float_t         time[256];
   Float_t         integral[256];
   Float_t         integral2[256];
   Int_t           summary[2];

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_evtnr;   //!
   TBranch        *b_clock;   //!
   TBranch        *b_femslot;   //!
   TBranch        *b_femevtnr;   //!
   TBranch        *b_femclock;   //!
   TBranch        *b_adc;   //!
   TBranch        *b_mean;   //!
   TBranch        *b_rms;   //!
   TBranch        *b_minadc;   //!
   TBranch        *b_maxadc;   //!
   TBranch        *b_pedestal;   //!
   TBranch        *b_pedsig;   //!
   TBranch        *b_peak;   //!
   TBranch        *b_time;   //!
   TBranch        *b_integral;   //!
   TBranch        *b_integral2;   //!
   TBranch        *b_summary;   //!

   makeMBDhist(TTree *tree=0);
   virtual ~makeMBDhist();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int ievt);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void EventDisplay(int ievt);

protected :
   virtual std::pair<int,int> MBD_ChannelMap(int ich);
   double TDC_PeakVal(int i, int ich);
   map<TString,TH1D*> h_ADC_s;
   map<TString,TH1D*> h_ADC_n;
   map<TString,TH1D*> h_TDC_s;
   map<TString,TH1D*> h_TDC_n;
   map<TString,TH1D*> h_TDC_diff;
   map<TString,TH1D*> h_TDC_diff_pedcut;
   TH1D* h_TDC_diff_avg;
   TH1D* h_TDC_avg_s;
   TH1D* h_TDC_avg_n;
   TH1D* h_TDC_diff_avg_pedcut;
   TH1D* h_TDC_avg_s_pedcut;
   TH1D* h_TDC_avg_n_pedcut;
   TH1D* h_ADC_sum_s;
   TH1D* h_ADC_sum_n;
   TH2D* h_ADC_corr;
   TH2D* h_ADC_corr_pedcut;
   TH1D* h_waveform_ADC_s[64];
   TH1D* h_waveform_TDC_s[64];
   TH1D* h_waveform_ADC_n[64];
   TH1D* h_waveform_TDC_n[64];

   const int nChannels = 64;
   const int nADCbins = 800;
   const int nTDCbins = 500;
   double xADCmin = -10;
   double xADCmax = 10000;
   double xTDCmin = -100;
   double xTDCmax = 11000;
   double xTDCdiffmin = -1000;
   double xTDCdiffmax = 1000;
   const int adcloop = 256;
   double adccoincut=30e3;

   const int nSamples = 31;

   int evt_start, evt_end;

   int NADC_OFF =8;
   int NOFFSET =16;
   int ch_ns_div = 64;

   int runN = RunNumber;
   //string filename = Form("/sphenix/user/dlis/Projects/fit_emcal/root_mbd/calib-0000%d-0000.root",RunNumber);
   string filename = Form("/gpfs/mnt/gpfs02/sphenix/user/dlis/Projects/sPHENIX_Run2023Commissioning/MBD_ANA/rootfiles/beam_mbd-000%d-0000.root",RunNumber);
};

#endif

#ifdef makeMBDhist_cxx
makeMBDhist::makeMBDhist(TTree *tree) : fChain(0) 
{
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename.c_str());
      if (!f || !f->IsOpen()) {
         f = new TFile(filename.c_str());
      }
      f->GetObject("W",tree);

   }
   Init(tree);
}

makeMBDhist::~makeMBDhist()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t makeMBDhist::GetEntry(Long64_t entry)
{
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t makeMBDhist::LoadTree(Long64_t entry)
{
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void makeMBDhist::Init(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("evtnr", &evtnr, &b_evtnr);
   fChain->SetBranchAddress("clock", &clock, &b_clock);
   fChain->SetBranchAddress("femslot", femslot, &b_femslot);
   fChain->SetBranchAddress("femevtnr", femevtnr, &b_femevtnr);
   fChain->SetBranchAddress("femclock", femclock, &b_femclock);
   fChain->SetBranchAddress("adc", adc, &b_adc);
   fChain->SetBranchAddress("mean", mean, &b_mean);
   fChain->SetBranchAddress("rms", rms, &b_rms);
   fChain->SetBranchAddress("minadc", minadc, &b_minadc);
   fChain->SetBranchAddress("maxadc", maxadc, &b_maxadc);
   fChain->SetBranchAddress("pedestal", pedestal, &b_pedestal);
   fChain->SetBranchAddress("pedsig", pedsig, &b_pedsig);
   fChain->SetBranchAddress("peak", peak, &b_peak);
   fChain->SetBranchAddress("time", time, &b_time);
   fChain->SetBranchAddress("integral", integral, &b_integral);
   fChain->SetBranchAddress("integral2", integral2, &b_integral2);
   fChain->SetBranchAddress("summary", summary, &b_summary);
   Notify();
}

Bool_t makeMBDhist::Notify()
{
   return kTRUE;
}

void makeMBDhist::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t makeMBDhist::Cut(Long64_t entry)
{
   return 1;
}
#endif // #ifdef makeMBDhist_cxx
