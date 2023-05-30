#ifndef makeLL1Hist_h
#define makeLL1Hist_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "runinfo.h"
#include "../../Utility/Style_jaebeom.h"

class makeLL1Hist {
public :
   TTree          *fChain;   
   Int_t           fCurrent; 

   // Declaration of leaf types
   Int_t           runnumber;
   Int_t           evtnr;
   Int_t           clock;
   Int_t           channel[52][20];
   Int_t           triggerwords[8][20];
   Int_t           nhit_n1[20];
   Int_t           nhit_n2[20];
   Int_t           nhit_s1[20];
   Int_t           nhit_s2[20];
   Int_t           nhit_n[20];
   Int_t           nhit_s[20];
   Int_t           chargesum_n1[20];
   Int_t           chargesum_n2[20];
   Int_t           chargesum_s1[20];
   Int_t           chargesum_s2[20];
   Int_t           chargesum_n[20];
   Int_t           chargesum_s[20];
   Int_t           timesum_n1[20];
   Int_t           timesum_n2[20];
   Int_t           timesum_s1[20];
   Int_t           timesum_s2[20];
   Int_t           timesum_n[20];
   Int_t           timesum_s[20];
   Int_t           idxsample;
   Int_t           idxhitn;
   Int_t           idxhits;

   // List of branches
   TBranch        *b_runnumber;   //!
   TBranch        *b_evtnr;   //!
   TBranch        *b_clock;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_triggerwords;   //!
   TBranch        *b_nhit_n1;   //!
   TBranch        *b_nhit_n2;   //!
   TBranch        *b_nhit_s1;   //!
   TBranch        *b_nhit_s2;   //!
   TBranch        *b_nhit_n;   //!
   TBranch        *b_nhit_s;   //!
   TBranch        *b_chargesum_n1;   //!
   TBranch        *b_chargesum_n2;   //!
   TBranch        *b_chargesum_s1;   //!
   TBranch        *b_chargesum_s2;   //!
   TBranch        *b_chargesum_n;   //!
   TBranch        *b_chargesum_s;   //!
   TBranch        *b_timesum_n1;   //!
   TBranch        *b_timesum_n2;   //!
   TBranch        *b_timesum_s1;   //!
   TBranch        *b_timesum_s2;   //!
   TBranch        *b_timesum_n;   //!
   TBranch        *b_timesum_s;   //!
   TBranch        *b_idxsample;   //!
   TBranch        *b_idxhitn;   //!
   TBranch        *b_idxhits;   //!

   makeLL1Hist(TTree *tree=0);
   virtual ~makeLL1Hist();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   
protected:
   TH1D* h_nhit_n;
   TH1D* h_nhit_s;
   TH2D* h_nhit_corr;
   TH2D* h_hit_check;
   const int nSamples = 20;
   const int nChannels =52;
   const int nChargeChannels = 8;
   const int nHitSampleIdx = 8;

   const int nhitbins = 65;

};

#endif

#ifdef makeLL1Hist_cxx
makeLL1Hist::makeLL1Hist(TTree *tree) : fChain(0) 
{
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(Form("/gpfs/mnt/gpfs02/sphenix/user/jpark4/Run2023Commissioning/analysis/run/sPHENIX_Run2023Commissioning/LL1_DECODING/LL1_to_root/rootfiles/junk_LL1-00000%d-0000.root",RunNumber));
      if (!f || !f->IsOpen()) {
         f = new TFile(Form("/gpfs/mnt/gpfs02/sphenix/user/jpark4/Run2023Commissioning/analysis/run/sPHENIX_Run2023Commissioning/LL1_DECODING/LL1_to_root/rootfiles/junk_LL1-00000%d-0000.root",RunNumber));
      }
      f->GetObject("W",tree);

   }
   Init(tree);
}

makeLL1Hist::~makeLL1Hist()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t makeLL1Hist::GetEntry(Long64_t entry)
{
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t makeLL1Hist::LoadTree(Long64_t entry)
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

void makeLL1Hist::Init(TTree *tree)
{
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("runnumber", &runnumber, &b_runnumber);
   fChain->SetBranchAddress("evtnr", &evtnr, &b_evtnr);
   fChain->SetBranchAddress("clock", &clock, &b_clock);
   fChain->SetBranchAddress("channel", channel, &b_channel);
   fChain->SetBranchAddress("triggerwords", triggerwords, &b_triggerwords);
   fChain->SetBranchAddress("nhit_n1", nhit_n1, &b_nhit_n1);
   fChain->SetBranchAddress("nhit_n2", nhit_n2, &b_nhit_n2);
   fChain->SetBranchAddress("nhit_s1", nhit_s1, &b_nhit_s1);
   fChain->SetBranchAddress("nhit_s2", nhit_s2, &b_nhit_s2);
   fChain->SetBranchAddress("nhit_n", nhit_n, &b_nhit_n);
   fChain->SetBranchAddress("nhit_s", nhit_s, &b_nhit_s);
   fChain->SetBranchAddress("chargesum_n1", chargesum_n1, &b_chargesum_n1);
   fChain->SetBranchAddress("chargesum_n2", chargesum_n2, &b_chargesum_n2);
   fChain->SetBranchAddress("chargesum_s1", chargesum_s1, &b_chargesum_s1);
   fChain->SetBranchAddress("chargesum_s2", chargesum_s2, &b_chargesum_s2);
   fChain->SetBranchAddress("chargesum_n", chargesum_n, &b_chargesum_n);
   fChain->SetBranchAddress("chargesum_s", chargesum_s, &b_chargesum_s);
   fChain->SetBranchAddress("timesum_n1", timesum_n1, &b_timesum_n1);
   fChain->SetBranchAddress("timesum_n2", timesum_n2, &b_timesum_n2);
   fChain->SetBranchAddress("timesum_s1", timesum_s1, &b_timesum_s1);
   fChain->SetBranchAddress("timesum_s2", timesum_s2, &b_timesum_s2);
   fChain->SetBranchAddress("timesum_n", timesum_n, &b_timesum_n);
   fChain->SetBranchAddress("timesum_s", timesum_s, &b_timesum_s);
   fChain->SetBranchAddress("idxsample", &idxsample, &b_idxsample);
   fChain->SetBranchAddress("idxhitn", &idxhitn, &b_idxhitn);
   fChain->SetBranchAddress("idxhits", &idxhits, &b_idxhits);
   Notify();
}

Bool_t makeLL1Hist::Notify()
{
   return kTRUE;
}

void makeLL1Hist::Show(Long64_t entry)
{
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t makeLL1Hist::Cut(Long64_t entry)
{
   return 1;
}
#endif // #ifdef makeLL1Hist_cxx
