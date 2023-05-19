#include <iostream>
#include "runDrawHist.h"

void runDrawHist(int i=2)
{
  makeMBDhist t;
  t.Loop(i);

  TFile* rf;
  if(i>0) rf = new TFile(Form("OutputHist_event%d.root",i),"read");
  else rf = new TFile("OutputHist_all.root","read");

  //gROOT->LoadMacro("../Utility/sPhenixStyle.C");
  //gROOT->ProcessLine("SetsPhenixStyle()");

  string outdir = "plots";
  void * dirf = gSystem->OpenDirectory(outdir.c_str());
  if(dirf) gSystem->FreeDirectory(dirf);
  else {gSystem->mkdir(outdir.c_str(), kTRUE);}

  TH1D* h_ADC_sum_s= (TH1D*) rf->Get("h_ADC_sum_s");
  TH1D* h_ADC_sum_n= (TH1D*) rf->Get("h_ADC_sum_n");
  TH1D* h_ADC_corr= (TH1D*) rf->Get("h_ADC_corr");

  const int nChannels = 64;
  TH1D* h_ADC_n[nChannels];
  TH1D* h_ADC_s[nChannels];
  TH1D* h_TDC_n[nChannels];
  TH1D* h_TDC_s[nChannels];
  TH1D* h_TDC_diff[nChannels];
  for(int ic=0; ic<nChannels;ic++){
    h_ADC_n[ic] = (TH1D*) rf->Get(Form("h_ADC_n_ch%d",ic));
    h_ADC_s[ic] = (TH1D*) rf->Get(Form("h_ADC_s_ch%d",ic));
    h_TDC_n[ic] = (TH1D*) rf->Get(Form("h_TDC_n_ch%d",ic));
    h_TDC_s[ic] = (TH1D*) rf->Get(Form("h_TDC_s_ch%d",ic));
    h_TDC_diff[ic] = (TH1D*) rf->Get(Form("h_TDC_diff_ch%d",ic));

  }

  int sc = h_ADC_sum_s->GetEntries();
  string strevt = (i>0) ? Form("Event %d",i) : Form("Event all (%d)",sc);
  string saven = (i>0) ? Form("event%d",i) : "eventAll";


  gStyle->SetOptStat(0);

  TCanvas* c_ADC_sum_s = new TCanvas("c_ADC_sum_s","",700,700);
  SetCanvasStyle(c_ADC_sum_s,h_ADC_sum_s);
  TLegend* leg_s = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_s);
  leg_s->SetHeader(Form("#bf{%s} - %s",str_date.c_str(), strevt.c_str()));
  leg_s->AddEntry(h_ADC_sum_s,"MBD charge south","pe");
  leg_s->Draw("same");
  c_ADC_sum_s->SaveAs(Form("%s/MBD_chargeSum_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_sum_n = new TCanvas("c_ADC_sum_n","",700,700);
  SetCanvasStyle(c_ADC_sum_n,h_ADC_sum_n);
  TLegend* leg_n = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_n);
  leg_n->SetHeader(Form("#bf{%s} - %s",str_date.c_str(), strevt.c_str()));
  leg_n->AddEntry(h_ADC_sum_n,"MBD charge north","pe");
  leg_n->Draw("same");
  c_ADC_sum_n->SaveAs(Form("%s/MBD_chargeSum_north_%s.pdf",outdir.c_str(),saven.c_str()));
  
  TCanvas* c_ADC_corr = new TCanvas("c_ADC_corr","",700,700);
  c_ADC_corr->SetLogz();
  c_ADC_corr->SetLeftMargin(0.151);
  c_ADC_corr->SetRightMargin(0.153);
  h_ADC_corr->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,1,sphenix_textsize);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x-0.1,col_y,1,col_textsize);
  TLegend* leg_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_corr);
  leg_corr->SetHeader(Form("#bf{%s} - %s",str_date.c_str(), strevt.c_str()));
  leg_corr->Draw("same");
  c_ADC_corr->SaveAs(Form("%s/MBD_chargeSum_corr_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_s = new TCanvas("c_TDC_s","",800,800);
  c_TDC_s->Divide(8,8);
  c_TDC_s->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_TDC_s->cd(ic+1);
    SetHistStyleSmall(h_TDC_s[ic],0,2);
    h_TDC_s[ic]->Draw("PE");
    c_TDC_s->Update();
    c_TDC_s->Modified();
  }
  c_TDC_s->SaveAs(Form("%s/TDC_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_n = new TCanvas("c_TDC_n","",800,800);
  c_TDC_n->Divide(8,8);
  c_TDC_n->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_TDC_n->cd(ic+1);
    SetHistStyleSmall(h_TDC_n[ic],0,2);
    h_TDC_n[ic]->Draw("PE");
    c_TDC_n->Update();
    c_TDC_n->Modified();
  }
  c_TDC_n->SaveAs(Form("%s/TDC_north_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_s = new TCanvas("c_ADC_s","",800,800);
  c_ADC_s->Divide(8,8);
  c_ADC_s->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_ADC_s->cd(ic+1);
    SetHistStyleSmall(h_ADC_s[ic],0,2);
    h_ADC_s[ic]->Draw("PE");
    c_ADC_s->Update();
    c_ADC_s->Modified();
  }
  c_ADC_s->SaveAs(Form("%s/ADC_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_n = new TCanvas("c_ADC_n","",800,800);
  c_ADC_n->Divide(8,8);
  c_ADC_n->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_ADC_n->cd(ic+1);
    SetHistStyleSmall(h_ADC_n[ic],0,2);
    h_ADC_n[ic]->Draw("PE");
    c_ADC_n->Update();
    c_ADC_n->Modified();
  }
  c_ADC_n->SaveAs(Form("%s/ADC_north_%s.pdf",outdir.c_str(),saven.c_str()));

} 
