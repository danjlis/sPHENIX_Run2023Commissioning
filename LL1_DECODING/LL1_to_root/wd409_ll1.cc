#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

// Event library

#include "Event.h"
#include "Eventiterator.h"
#include "fileEventiterator.h"
//#include "packet_hbd_fpgashort.h"

// ROOT

#include "TFile.h"
#include "TTree.h"
#include "TSystem.h"

// Interpolator class and root of derivative

#include "Math/Interpolator.h"
#include "Math/Functor.h"
#include "Math/RootFinderAlgorithms.h" 

#include <math.h>
// data structures for this 

#include "wd409dataLL1.h"

using namespace std;

int wd409_ll1( const char *filename, const char *outputfile )
{

  // John Haggerty, BNL 2013.02.27

  int status;
  cerr << "evt file: " << filename << endl;

  Eventiterator *ievt =  new fileEventiterator (filename, status);
  if (status) {
    cerr << "Couldn't open input file " << filename << endl;
    delete ievt;
    exit(1);
  }

  Event *evt;

  // Get the root tree ready

  // first make a nice filename by making use of sthe string class

  TString rootfilename = outputfile;
  rootfilename.ReplaceAll(".EVT",".root");
  rootfilename.ReplaceAll(".evt",".root");
  rootfilename.ReplaceAll(".prdf",".root");
  rootfilename = gSystem->BaseName( rootfilename.Data() ) ;

  TString fullrootfilename;
  fullrootfilename = gSystem->pwd();
  fullrootfilename += "/";
  fullrootfilename += rootfilename;
  cout << "root file: " << fullrootfilename << endl;

  // now make the root file

  TFile f(rootfilename,"recreate");
  TTree W("W","Waveform digitizer raw data");
  W.SetMaxTreeSize(100000000000LL);

  wd409dataLL1 *wd;
  wd = new wd409dataLL1();

  TString branchstring;

  W.Branch("runnumber",&wd->runnumber,"runnumber/I"); 
  W.Branch("evtnr",&wd->evtnr,"evtnr/I"); 
  W.Branch("clock",&wd->clock,"clock/I"); 

  // Trailer words

  /*
     branchstring = "evenchcksum/I";
     W.Branch("evenchecksum",wd->evenchecksum,branchstring); 

     branchstring = "calcevenchcksum/I";
     W.Branch("calcevenchecksum",wd->calcevenchecksum,branchstring); 

     branchstring = "oddchcksum/I";
     W.Branch("oddchecksum",wd->oddchecksum,branchstring); 

     branchstring = "calcoddchcksum/I";
     W.Branch("calcoddchecksum",wd->calcoddchecksum,branchstring); 
     */

  // begin words from FEM header

  /*    branchstring = "femslot[";
        branchstring += NRMOD;
        branchstring += "]/I";
        W.Branch("femslot",wd->femslot,branchstring); 

        branchstring = "femevtnr[";
        branchstring += NRMOD;
        branchstring += "]/I";
        W.Branch("femevtnr",wd->femevtnr,branchstring); 

        branchstring = "femclock[";
        branchstring += NRMOD;
        branchstring += "]/I";
        W.Branch("femclock",wd->femclock,branchstring); 
        */
  // end words from FEM header

  // channel
  branchstring = "channel[";
  branchstring += NCH;
  branchstring += "][";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("channel",wd->channel,branchstring); 
  // channel
  branchstring = "triggerwords[";
  branchstring += NTRIGWORDS;
  branchstring += "][";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("triggerwords",wd->triggerwords,branchstring); 

  // Nhit 
  branchstring = "nhit_n1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_n1",wd->nhit_n1,branchstring);
  branchstring = "nhit_n2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_n2",wd->nhit_n2,branchstring);
  branchstring = "nhit_s1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_s1",wd->nhit_s1,branchstring);
  branchstring = "nhit_s2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_s2",wd->nhit_s2,branchstring);
  branchstring = "nhit_n[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_n",wd->nhit_n,branchstring);
  branchstring = "nhit_s[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("nhit_s",wd->nhit_s,branchstring);

  // charge sum
  branchstring = "chargesum_n1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_n1",wd->chargesum_n1,branchstring);
  branchstring = "chargesum_n2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_n2",wd->chargesum_n2,branchstring);
  branchstring = "chargesum_s1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_s1",wd->chargesum_s1,branchstring);
  branchstring = "chargesum_s2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_s2",wd->chargesum_s2,branchstring);
  branchstring = "chargesum_n[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_n",wd->chargesum_n,branchstring);
  branchstring = "chargesum_s[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("chargesum_s",wd->chargesum_s,branchstring);

  // time sum
  branchstring = "timesum_n1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_n1",wd->timesum_n1,branchstring);
  branchstring = "timesum_n2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_n2",wd->timesum_n2,branchstring);
  branchstring = "timesum_s1[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_s1",wd->timesum_s1,branchstring);
  branchstring = "timesum_s2[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_s2",wd->timesum_s2,branchstring);
  branchstring = "timesum_n[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_n",wd->timesum_n,branchstring);
  branchstring = "timesum_s[";
  branchstring += NRSAM;
  branchstring += "]/I";
  W.Branch("timesum_s",wd->timesum_s,branchstring);

  // sample index 
  branchstring = "idxsample";
  branchstring += "/I";
  W.Branch("idxsample",&wd->idxsample,branchstring);
  branchstring = "idxhitn";
  branchstring += "/I";
  W.Branch("idxhitn",&wd->idxhitn,branchstring);
  branchstring = "idxhits";
  branchstring += "/I";
  W.Branch("idxhits",&wd->idxhits,branchstring);

  // Arrays for Interpolator to work with
/*  Double_t t[NRSAM], a[NRSAM];
  for ( Int_t i = 0; i < NRSAM; i++ ) {
    t[i] = (Double_t) i;
  }
*/
  int n_recs = 0;
  std::stringstream ss;
  while ( (evt = ievt->getNextEvent()) ) {
    if ( evt->getEvtType() != 1 ) continue;

    //   int ibd = 0;
    for ( Int_t ixmit = 0; ixmit < NXMIT; ixmit++ ) {
      Packet *p;
      p = evt->getPacket( PACKET[ixmit] );
  
      if ( p ) {

        //	Packet_hbd_fpgashort *digitizerv2_p = dynamic_cast<Packet_hbd_fpgashort*>( p );
        //	digitizerv2_p->setNumSamples( NRSAM );

        wd->runnumber = evt->getRunNumber();
        wd->evtnr = p->iValue(0,"EVTNR");
        wd->clock = p->iValue(0,"CLOCK");

        int indx1=0; int inhit1=0; 
        int indx2=0; int inhit2=0;
        for(int is = 0; is < NRSAM; is++){
          wd->nhit_s1[is] =  p->iValue(is,NHITCHANNEL+NADCSH*0);
          wd->nhit_s2[is] =  p->iValue(is,NHITCHANNEL+NADCSH*1);
          wd->nhit_n1[is] =  p->iValue(is,NHITCHANNEL+NADCSH*2);
          wd->nhit_n2[is] =  p->iValue(is,NHITCHANNEL+NADCSH*3);

          wd->nhit_n[is] = wd->nhit_n1[is] + wd->nhit_n2[is];
          wd->nhit_s[is] = wd->nhit_s1[is] + wd->nhit_s2[is];
          
          wd->timesum_s1[is] =  p->iValue(is,NHITCHANNEL+1+NADCSH*0);
          wd->timesum_s2[is] =  p->iValue(is,NHITCHANNEL+2+NADCSH*1);
          wd->timesum_n1[is] =  p->iValue(is,NHITCHANNEL+3+NADCSH*2);
          wd->timesum_n2[is] =  p->iValue(is,NHITCHANNEL+4+NADCSH*3);

          wd->timesum_s[is] = wd->timesum_n1[is] + wd->timesum_n2[is];
          wd->timesum_n[is] = wd->timesum_s1[is] + wd->timesum_s2[is];

          if( wd->nhit_n[is]>0){
            if(inhit1 <  wd->nhit_n[is]){
              indx1 = is;
              inhit1 = wd->nhit_n[is];
            } 
          }
          
          if( wd->nhit_s[is]>0){
            if(inhit2 <  wd->nhit_s[is]){
              indx2 = is;
              inhit2 = wd->nhit_s[is];
            } 
          }

          wd->chargesum_n1[is] = 0;
          wd->chargesum_n2[is] = 0;
          wd->chargesum_s1[is] = 0;
          wd->chargesum_s2[is] = 0;
          wd->chargesum_s[is] = 0;
          wd->chargesum_n[is] = 0;

          for(int ic = 0; ic <NCH; ic++) {
            wd->channel[ic][is] = p->iValue(is,ic);
            if(ic>=NADCSH*0 && ic<NHITCHANNEL+NADCSH*0) wd->chargesum_s1[is] += p->iValue(is,ic);
            else if(ic>=NADCSH*1 && ic<NHITCHANNEL+NADCSH*1) wd->chargesum_s2[is] += p->iValue(is,ic);
            else if(ic>=NADCSH*2 && ic<NHITCHANNEL+NADCSH*2) wd->chargesum_n1[is] += p->iValue(is,ic);
            else if(ic>=NADCSH*3 && ic<NHITCHANNEL+NADCSH*3) wd->chargesum_n2[is] += p->iValue(is,ic);
            wd->chargesum_n[is] = wd->chargesum_n1[is] + wd->chargesum_n2[is];
            wd->chargesum_s[is] = wd->chargesum_s1[is] + wd->chargesum_s2[is];
          }
          for(int it=NCH; it<(NCH+NTRIGWORDS); it++){
            wd->triggerwords[it - NCH][is] =  p->iValue(is,it);
          }
        }	
        wd->idxhitn = indx1;
        wd->idxhits = indx2;

        wd->idxsample = (wd->idxhitn==wd->idxhits) ? wd->idxhitn : -1;

        delete p;
      }
    }
    W.Fill();
    n_recs++;
    delete evt;
  }

  //W.BuildIndex("runnumber", "evtnr");
  
  W.Write();
  f.Close();

  cout << "wd409 LL1 : final n_recs: " << n_recs << endl;

  delete wd;
  delete ievt;
  return 0;

}
