#include <iostream>
#include "runDrawHist.h"

void runDrawHist(bool drawonly=false)
{
  if(!drawonly){
    makeLL1Hist t;
    t.Loop();
  }
  string filename = Form("OutputHistLL1_RunNumber%d.root",RunNumber);
  TFile* rf = (TFile*)gROOT->GetListOfFiles()->FindObject((filename.c_str()));
  
  if(!rf || !rf->IsOpen()){
    rf = new TFile(filename.c_str());
  }   

  string outdir = "plots";
  outdir += Form("/Run%d",RunNumber);
  void * dirf = gSystem->OpenDirectory(outdir.c_str());
  if(dirf) gSystem->FreeDirectory(dirf);
  else {gSystem->mkdir(outdir.c_str(), kTRUE);}

  string saven = Form("Run%d",RunNumber);
  string infotext = Form("#bf{%s} Run%d",str_date.c_str(),RunNumber);
  
  TH2D* h_nhit_corr = (TH2D*) rf->Get("h_nhit_corr");
  TH2D* h_hit_check= (TH2D*) rf->Get("h_hit_check");

  gStyle->SetOptStat(0);

  TCanvas* c_nhit_corr= new TCanvas("c_nhit_corr","",700,700);
  gPad->SetTicks(1,1);
  c_nhit_corr->SetLogz();
  c_nhit_corr->SetLeftMargin(0.151);
  c_nhit_corr->SetRightMargin(0.153);
  h_nhit_corr->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,1,sphenix_textsize);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,1,col_textsize);
  TLegend* leg_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_corr);
  leg_corr->SetHeader(infotext.c_str());
  leg_corr->Draw("same");
  c_nhit_corr->SaveAs(Form("%s/hist_nhit_corr_%s.pdf",outdir.c_str(),saven.c_str()));

}
