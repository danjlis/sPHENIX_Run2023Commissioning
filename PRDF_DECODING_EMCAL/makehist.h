//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 17 15:22:14 2023 by ROOT version 6.26/06
// from TTree towerntup/Towers
// found on file: testtree_junk.root
//////////////////////////////////////////////////////////

#ifndef makehist_h
#define makehist_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class makehist {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   vector<float>   *energy;
   vector<int>     *etabin;
   vector<int>     *phibin;
   vector<float>   *waveform_0;
   vector<float>   *waveform_1;
   vector<float>   *waveform_2;
   vector<float>   *waveform_3;
   vector<float>   *waveform_4;
   vector<float>   *waveform_5;
   vector<float>   *waveform_6;
   vector<float>   *waveform_7;
   vector<float>   *waveform_8;
   vector<float>   *waveform_9;
   vector<float>   *waveform_10;
   vector<float>   *waveform_11;
   vector<float>   *waveform_12;
   vector<float>   *waveform_13;
   vector<float>   *waveform_14;
   vector<float>   *waveform_15;
   vector<float>   *waveform_16;
   vector<float>   *waveform_17;
   vector<float>   *waveform_18;
   vector<float>   *waveform_19;
   vector<float>   *waveform_20;
   vector<float>   *waveform_21;
   vector<float>   *waveform_22;
   vector<float>   *waveform_23;
   vector<float>   *waveform_24;
   vector<float>   *waveform_25;
   vector<float>   *waveform_26;
   vector<float>   *waveform_27;
   vector<float>   *waveform_28;
   vector<float>   *waveform_29;
   vector<float>   *waveform_30;

   // List of branches
   TBranch        *b_energy;   //!
   TBranch        *b_etabin;   //!
   TBranch        *b_phibin;   //!
   TBranch        *b_waveform_0;   //!
   TBranch        *b_waveform_1;   //!
   TBranch        *b_waveform_2;   //!
   TBranch        *b_waveform_3;   //!
   TBranch        *b_waveform_4;   //!
   TBranch        *b_waveform_5;   //!
   TBranch        *b_waveform_6;   //!
   TBranch        *b_waveform_7;   //!
   TBranch        *b_waveform_8;   //!
   TBranch        *b_waveform_9;   //!
   TBranch        *b_waveform_10;   //!
   TBranch        *b_waveform_11;   //!
   TBranch        *b_waveform_12;   //!
   TBranch        *b_waveform_13;   //!
   TBranch        *b_waveform_14;   //!
   TBranch        *b_waveform_15;   //!
   TBranch        *b_waveform_16;   //!
   TBranch        *b_waveform_17;   //!
   TBranch        *b_waveform_18;   //!
   TBranch        *b_waveform_19;   //!
   TBranch        *b_waveform_20;   //!
   TBranch        *b_waveform_21;   //!
   TBranch        *b_waveform_22;   //!
   TBranch        *b_waveform_23;   //!
   TBranch        *b_waveform_24;   //!
   TBranch        *b_waveform_25;   //!
   TBranch        *b_waveform_26;   //!
   TBranch        *b_waveform_27;   //!
   TBranch        *b_waveform_28;   //!
   TBranch        *b_waveform_29;   //!
   TBranch        *b_waveform_30;   //!

   makehist(TTree *tree=0);
   virtual ~makehist();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(int ievt);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual void     SetWaveFormVal(int i, double waveval[31]);

   int evt_start, evt_end;

   const int netabins=96;
   const int nphibins=256;
   const int nsample =31;
   const int size=96*256;
   double energymax = 35e3;
   int nenergy = 1500;
   
   double waveval[31];
   TH2D* h_energy_map;
   TH1D* h_energy_phi;
   TH1D* h_energy_eta;
   TH1D* h_energy;
   TH1D* h_event;

   TH1D* h_waveform_event[96][256];
   TH1D* h_waveform[96][256];


};

#endif

#ifdef makehist_cxx
makehist::makehist(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("testtree_junk.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("testtree_junk.root");
      }
      f->GetObject("towerntup",tree);

   }
   Init(tree);
}

makehist::~makehist()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t makehist::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t makehist::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void makehist::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   energy = 0;
   etabin = 0;
   phibin = 0;
   waveform_0 = 0;
   waveform_1 = 0;
   waveform_2 = 0;
   waveform_3 = 0;
   waveform_4 = 0;
   waveform_5 = 0;
   waveform_6 = 0;
   waveform_7 = 0;
   waveform_8 = 0;
   waveform_9 = 0;
   waveform_10 = 0;
   waveform_11 = 0;
   waveform_12 = 0;
   waveform_13 = 0;
   waveform_14 = 0;
   waveform_15 = 0;
   waveform_16 = 0;
   waveform_17 = 0;
   waveform_18 = 0;
   waveform_19 = 0;
   waveform_20 = 0;
   waveform_21 = 0;
   waveform_22 = 0;
   waveform_23 = 0;
   waveform_24 = 0;
   waveform_25 = 0;
   waveform_26 = 0;
   waveform_27 = 0;
   waveform_28 = 0;
   waveform_29 = 0;
   waveform_30 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("energy", &energy, &b_energy);
   fChain->SetBranchAddress("etabin", &etabin, &b_etabin);
   fChain->SetBranchAddress("phibin", &phibin, &b_phibin);
   fChain->SetBranchAddress("waveform_0", &waveform_0, &b_waveform_0);
   fChain->SetBranchAddress("waveform_1", &waveform_1, &b_waveform_1);
   fChain->SetBranchAddress("waveform_2", &waveform_2, &b_waveform_2);
   fChain->SetBranchAddress("waveform_3", &waveform_3, &b_waveform_3);
   fChain->SetBranchAddress("waveform_4", &waveform_4, &b_waveform_4);
   fChain->SetBranchAddress("waveform_5", &waveform_5, &b_waveform_5);
   fChain->SetBranchAddress("waveform_6", &waveform_6, &b_waveform_6);
   fChain->SetBranchAddress("waveform_7", &waveform_7, &b_waveform_7);
   fChain->SetBranchAddress("waveform_8", &waveform_8, &b_waveform_8);
   fChain->SetBranchAddress("waveform_9", &waveform_9, &b_waveform_9);
   fChain->SetBranchAddress("waveform_10", &waveform_10, &b_waveform_10);
   fChain->SetBranchAddress("waveform_11", &waveform_11, &b_waveform_11);
   fChain->SetBranchAddress("waveform_12", &waveform_12, &b_waveform_12);
   fChain->SetBranchAddress("waveform_13", &waveform_13, &b_waveform_13);
   fChain->SetBranchAddress("waveform_14", &waveform_14, &b_waveform_14);
   fChain->SetBranchAddress("waveform_15", &waveform_15, &b_waveform_15);
   fChain->SetBranchAddress("waveform_16", &waveform_16, &b_waveform_16);
   fChain->SetBranchAddress("waveform_17", &waveform_17, &b_waveform_17);
   fChain->SetBranchAddress("waveform_18", &waveform_18, &b_waveform_18);
   fChain->SetBranchAddress("waveform_19", &waveform_19, &b_waveform_19);
   fChain->SetBranchAddress("waveform_20", &waveform_20, &b_waveform_20);
   fChain->SetBranchAddress("waveform_21", &waveform_21, &b_waveform_21);
   fChain->SetBranchAddress("waveform_22", &waveform_22, &b_waveform_22);
   fChain->SetBranchAddress("waveform_23", &waveform_23, &b_waveform_23);
   fChain->SetBranchAddress("waveform_24", &waveform_24, &b_waveform_24);
   fChain->SetBranchAddress("waveform_25", &waveform_25, &b_waveform_25);
   fChain->SetBranchAddress("waveform_26", &waveform_26, &b_waveform_26);
   fChain->SetBranchAddress("waveform_27", &waveform_27, &b_waveform_27);
   fChain->SetBranchAddress("waveform_28", &waveform_28, &b_waveform_28);
   fChain->SetBranchAddress("waveform_29", &waveform_29, &b_waveform_29);
   fChain->SetBranchAddress("waveform_30", &waveform_30, &b_waveform_30);
   Notify();
}

Bool_t makehist::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void makehist::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t makehist::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

void makehist::SetWaveFormVal(int i, double waveval[31])
{
  waveval[0] = waveform_0->at(i);
  waveval[1] = waveform_1->at(i);
  waveval[2] = waveform_2->at(i);
  waveval[3] = waveform_3->at(i);
  waveval[4] = waveform_4->at(i);
  waveval[5] = waveform_5->at(i);
  waveval[6] = waveform_6->at(i);
  waveval[7] = waveform_7->at(i);
  waveval[8] = waveform_8->at(i);
  waveval[9] = waveform_9->at(i);
  waveval[10] = waveform_10->at(i);
  waveval[11] = waveform_11->at(i);
  waveval[12] = waveform_12->at(i);
  waveval[13] = waveform_13->at(i);
  waveval[14] = waveform_14->at(i);
  waveval[15] = waveform_15->at(i);
  waveval[16] = waveform_16->at(i);
  waveval[17] = waveform_17->at(i);
  waveval[18] = waveform_18->at(i);
  waveval[19] = waveform_19->at(i);
  waveval[20] = waveform_20->at(i);
  waveval[21] = waveform_21->at(i);
  waveval[22] = waveform_22->at(i);
  waveval[23] = waveform_23->at(i);
  waveval[24] = waveform_24->at(i);
  waveval[25] = waveform_25->at(i);
  waveval[26] = waveform_26->at(i);
  waveval[27] = waveform_27->at(i);
  waveval[28] = waveform_28->at(i);
  waveval[29] = waveform_29->at(i);
  waveval[30] = waveform_30->at(i);
}
#endif // #ifdef makehist_cxx
