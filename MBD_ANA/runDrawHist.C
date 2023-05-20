#include <iostream>
#include "runDrawHist.h"

void runDrawHist(int i=2, bool drawonly=false)
{
  bool isPickupEvt = (i>=0) ? true : false;
  if(!drawonly){
    makeMBDhist t;
    t.Loop(i);
  }
  string filename = (isPickupEvt) ? Form("OutputHist_event%d.root",i) : "OutputHist_all.root";
  TFile* rf;
  if(isPickupEvt){
    rf = (TFile*)gROOT->GetListOfFiles()->FindObject((Form("OutputHist_event%d.root",i)));
  }
  else rf = (TFile*)gROOT->GetListOfFiles()->FindObject("OutputHist_all.root");
  
  if(!rf || !rf->IsOpen()){
    rf = new TFile(filename.c_str());
  }   

  //gROOT->LoadMacro("../Utility/sPhenixStyle.C");
  //gROOT->ProcessLine("SetsPhenixStyle()");

  string outdir = "plots";
  outdir += Form("/Run%d",RunNumber);
  void * dirf = gSystem->OpenDirectory(outdir.c_str());
  if(dirf) gSystem->FreeDirectory(dirf);
  else {gSystem->mkdir(outdir.c_str(), kTRUE);}

  TH1D* h_ADC_sum_s= (TH1D*) rf->Get("h_ADC_sum_s");
  TH1D* h_ADC_sum_n= (TH1D*) rf->Get("h_ADC_sum_n");
  TH1D* h_ADC_corr= (TH1D*) rf->Get("h_ADC_corr");
  TH1D* h_ADC_corr_pedcut= (TH1D*) rf->Get("h_ADC_corr_pedcut");

  const int nChannels = 64;
  TH1D* h_ADC_n[nChannels];
  TH1D* h_ADC_s[nChannels];
  TH1D* h_TDC_n[nChannels];
  TH1D* h_TDC_s[nChannels];
  TH1D* h_TDC_diff[nChannels];
  TH1D* h_TDC_diff_pedcut[nChannels];

  TH1D* h_waveform_ADC_s[nChannels];
  TH1D* h_waveform_ADC_n[nChannels];
  TH1D* h_waveform_TDC_s[nChannels];
  TH1D* h_waveform_TDC_n[nChannels];

  for(int ic=0; ic<nChannels;ic++){
    h_ADC_n[ic] = (TH1D*) rf->Get(Form("h_ADC_n_ch%d",ic));
    h_ADC_s[ic] = (TH1D*) rf->Get(Form("h_ADC_s_ch%d",ic));
    h_TDC_n[ic] = (TH1D*) rf->Get(Form("h_TDC_n_ch%d",ic));
    h_TDC_s[ic] = (TH1D*) rf->Get(Form("h_TDC_s_ch%d",ic));
    h_TDC_diff[ic] = (TH1D*) rf->Get(Form("h_TDC_diff_ch%d",ic));
    h_TDC_diff_pedcut[ic] = (TH1D*) rf->Get(Form("h_TDC_diff_pedcut_ch%d",ic));
    if(isPickupEvt){
      h_waveform_ADC_s[ic] = (TH1D*) rf->Get(Form("h_ADC_waveform_s_event%d_ch%d",i,ic));
      h_waveform_ADC_n[ic] = (TH1D*) rf->Get(Form("h_ADC_waveform_n_event%d_ch%d",i,ic));
      h_waveform_TDC_s[ic] = (TH1D*) rf->Get(Form("h_TDC_waveform_s_event%d_ch%d",i,ic));
      h_waveform_TDC_n[ic] = (TH1D*) rf->Get(Form("h_TDC_waveform_n_event%d_ch%d",i,ic));
    }
  }

  int sc = h_ADC_sum_s->GetEntries();
  string strevt = (isPickupEvt) ? Form("Event %d",i) : Form("Event all (%d)",sc);
  string saven = (isPickupEvt) ? Form("event%d",i) : "eventAll";
  saven += Form("_Run%d",RunNumber);

  const char* infotext = Form("#bf{%s} Run%d, %s",str_date.c_str(),RunNumber,strevt.c_str());


  gStyle->SetOptStat(0);

  TCanvas* c_ADC_sum_s = new TCanvas("c_ADC_sum_s","",700,700);
  SetCanvasStyle(c_ADC_sum_s,h_ADC_sum_s);
  TLegend* leg_s = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_s);
  leg_s->SetHeader(infotext);
  leg_s->AddEntry(h_ADC_sum_s,"MBD charge south","pe");
  leg_s->Draw("same");
  c_ADC_sum_s->SaveAs(Form("%s/MBD_chargeSum_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_sum_n = new TCanvas("c_ADC_sum_n","",700,700);
  SetCanvasStyle(c_ADC_sum_n,h_ADC_sum_n);
  TLegend* leg_n = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_n);
  leg_n->SetHeader(infotext);
  leg_n->AddEntry(h_ADC_sum_n,"MBD charge north","pe");
  leg_n->Draw("same");
  c_ADC_sum_n->SaveAs(Form("%s/MBD_chargeSum_north_%s.pdf",outdir.c_str(),saven.c_str()));
  
  TCanvas* c_ADC_corr = new TCanvas("c_ADC_corr","",700,700);
  c_ADC_corr->SetLogz();
  c_ADC_corr->SetLeftMargin(0.151);
  c_ADC_corr->SetRightMargin(0.153);
  h_ADC_corr->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,1,sphenix_textsize);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,1,col_textsize);
  TLegend* leg_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_corr);
  leg_corr->SetHeader(infotext);
  leg_corr->Draw("same");
  c_ADC_corr->SaveAs(Form("%s/MBD_chargeSum_corr_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_corr_pedcut = new TCanvas("c_ADC_corr_pedcut","",700,700);
  c_ADC_corr_pedcut->SetLogz();
  c_ADC_corr_pedcut->SetLeftMargin(0.151);
  c_ADC_corr_pedcut->SetRightMargin(0.153);
  h_ADC_corr_pedcut->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,1,sphenix_textsize);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,1,col_textsize);
  leg_corr->Draw("same");
  c_ADC_corr_pedcut->SaveAs(Form("%s/MBD_chargeSum_corr_pedcut_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_s = new TCanvas("c_TDC_s","",800,800);
  TPad* pad_tdcs = new TPad("pad_tdcs","",0,0,1,0.95);
  pad_tdcs->Divide(8,8);
  c_TDC_s->cd();
  pad_tdcs->Draw();
  drawText("#bf{South - TDC}",sphenix_x-xshift_sq[0],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText(infotext,sphenix_x+xshift_sq[1],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText("#bf{#it{sPHENIX}} Internal",col_x+xshift_sq[2],col_y+yshift,1,col_textsize_sq);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift_sq[3],col_y+yshift,1,col_textsize_sq);
  for(int ic=0;ic<nChannels;ic++){
    pad_tdcs->cd(ic+1);
    gPad->SetLogy();
    SetHistStyle(h_TDC_s[ic],0,2);
    h_TDC_s[ic]->Draw();
    c_TDC_s->Update();
    c_TDC_s->Modified();
  }
  c_TDC_s->SaveAs(Form("%s/TDC_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_n = new TCanvas("c_TDC_n","",800,800);
  TPad* pad_tdcn = new TPad("pad_tdcn","",0,0,1,0.95);
  pad_tdcn->Divide(8,8);
  c_TDC_n->cd();
  pad_tdcn->Draw();
  drawText("#bf{North - TDC}",sphenix_x-xshift_sq[0],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText(infotext,sphenix_x+xshift_sq[1],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText("#bf{#it{sPHENIX}} Internal",col_x+xshift_sq[2],col_y+yshift,1,col_textsize_sq);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift_sq[3],col_y+yshift,1,col_textsize_sq);
  for(int ic=0;ic<nChannels;ic++){
    pad_tdcn->cd(ic+1);
    gPad->SetLogy();
    SetHistStyle(h_TDC_n[ic],0,2);
    h_TDC_n[ic]->Draw();
  }
  c_TDC_n->Update();
  c_TDC_n->SaveAs(Form("%s/TDC_north_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_diff = new TCanvas("c_TDC_diff","",800,800);
  c_TDC_diff->Divide(8,8);
  c_TDC_diff->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_TDC_diff->cd(ic+1);
    SetHistStyle(h_TDC_diff[ic],0,0);
    h_TDC_diff[ic]->Draw();
    c_TDC_diff->Update();
    c_TDC_diff->Modified();
  }
  c_TDC_diff->SaveAs(Form("%s/TDC_diff_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_TDC_diff_pedcut = new TCanvas("c_TDC_diff_pedcut","",800,800);
  c_TDC_diff_pedcut->Divide(8,8);
  c_TDC_diff_pedcut->SetTopMargin(0.11);
  for(int ic=0;ic<nChannels;ic++){
    c_TDC_diff_pedcut->cd(ic+1);
    SetHistStyle(h_TDC_diff_pedcut[ic],0,0);
    h_TDC_diff_pedcut[ic]->Draw();
    c_TDC_diff_pedcut->Update();
    c_TDC_diff_pedcut->Modified();
  }
  c_TDC_diff_pedcut->SaveAs(Form("%s/TDC_diff_pedcut_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_s = new TCanvas("c_ADC_s","",800,800);
  TPad* pad_adcs = new TPad("pad_adcs","",0,0,1,0.95);
  pad_adcs->Divide(8,8);
  c_ADC_s->cd();
  pad_adcs->Draw();
  drawText("#bf{South - ADC}",sphenix_x-xshift_sq[0],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText(infotext,sphenix_x+xshift_sq[1],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText("#bf{#it{sPHENIX}} Internal",col_x+xshift_sq[2],col_y+yshift,1,col_textsize_sq);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift_sq[3],col_y+yshift,1,col_textsize_sq);
  for(int ic=0;ic<nChannels;ic++){
    pad_adcs->cd(ic+1);
    gPad->SetLogy();
    SetHistStyleSmall(h_ADC_s[ic],0,2);
    h_ADC_s[ic]->Draw();
    c_ADC_s->Update();
    c_ADC_s->Modified();
  }
  c_ADC_s->SaveAs(Form("%s/ADC_south_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_ADC_n = new TCanvas("c_ADC_n","",800,800);
  TPad* pad_adcn = new TPad("pad_adcn","",0,0,1,0.95);
  pad_adcn->Divide(8,8);
  c_ADC_n->cd();
  drawText("#bf{North - ADC}",sphenix_x-xshift_sq[0],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText(infotext,sphenix_x+xshift_sq[1],sphenix_y+yshift,1,sphenix_textsize_sq);
  drawText("#bf{#it{sPHENIX}} Internal",col_x+xshift_sq[2],col_y+yshift,1,col_textsize_sq);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift_sq[3],col_y+yshift,1,col_textsize_sq);
  pad_adcn->Draw();
  for(int ic=0;ic<nChannels;ic++){
    pad_adcn->cd(ic+1);
    gPad->SetLogy();
    SetHistStyleSmall(h_ADC_n[ic],0,2);
    h_ADC_n[ic]->Draw();
    c_ADC_n->Update();
    c_ADC_n->Modified();
  }
  c_ADC_n->SaveAs(Form("%s/ADC_north_%s.pdf",outdir.c_str(),saven.c_str()));

  if(isPickupEvt){
    TCanvas* c_waveform_s = new TCanvas("c_waveform_s","",1600,800);
    TPad* pad1 = new TPad("pad1","",0,0,0.5,0.95);
    TPad* pad2 = new TPad("pad2","",0.5,0,1,0.95);
    pad1->Divide(8,8);
    pad2->Divide(8,8);
    c_waveform_s->cd();
    pad1->Draw();
    pad2->Draw();
    drawText("#bf{North}",sphenix_x-xshift[0],sphenix_y_shift,1,sphenix_textsize);
    drawText("#bf{ADC} waveform",sphenix_x-xshift[1],sphenix_y_shift,1,sphenix_textsize);
    drawText(infotext,sphenix_x+xshift[2],sphenix_y_shift,1,sphenix_textsize);
    drawText("#bf{TDC} waveform",col_x-xshift[3],col_y_shift,1,col_textsize);
    drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+xshift[4],sphenix_y_shift,1,sphenix_textsize);
    drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift[5],col_y_shift,1,col_textsize);
    for(int ich=0; ich<nChannels; ich++){
      pad1->cd(ich+1);
      h_waveform_ADC_s[ich]->GetYaxis()->SetLimits(adcmin,adcmax);
      h_waveform_ADC_s[ich]->GetYaxis()->SetRangeUser(adcmin,adcmax);
      h_waveform_ADC_s[ich]->Draw();

      pad2->cd(ich+1);
      h_waveform_TDC_s[ich]->GetYaxis()->SetLimits(tdcmin, tdcmax);
      h_waveform_TDC_s[ich]->GetYaxis()->SetRangeUser(tdcmin, tdcmax);
      h_waveform_TDC_s[ich]->Draw();
    }
    pad1->Update();
    pad2->Update();
    c_waveform_s->Update();
    c_waveform_s->SaveAs(Form("%s/Waveform_south_%s.pdf",outdir.c_str(),saven.c_str()));
    
    TCanvas* c_waveform_n = new TCanvas("c_waveform_n","",1600,800);
    TPad* padn1 = new TPad("padn1","",0,0,0.5,0.95);
    TPad* padn2 = new TPad("padn2","",0.5,0,1,0.95);
    padn1->Divide(8,8);
    padn2->Divide(8,8);
    c_waveform_n->cd();
    drawText("#bf{South}",sphenix_x-xshift[0],sphenix_y,1,sphenix_textsize);
    drawText("#bf{ADC} waveform",sphenix_x-xshift[1],sphenix_y,1,sphenix_textsize);
    drawText(infotext,sphenix_x+xshift[2],sphenix_y,1,sphenix_textsize);
    drawText("#bf{TDC} waveform",col_x-xshift[3],col_y,1,col_textsize);
    drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+xshift[4],sphenix_y,1,sphenix_textsize);
    drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x+xshift[5],col_y,1,col_textsize);
    padn1->Draw();
    padn2->Draw();
    for(int ich=0; ich<nChannels; ich++){
      padn1->cd(ich+1);
      h_waveform_ADC_n[ich]->GetYaxis()->SetLimits(adcmin,adcmax);
      h_waveform_ADC_n[ich]->GetYaxis()->SetRangeUser(adcmin,adcmax);
      h_waveform_ADC_n[ich]->Draw();

      padn2->cd(ich+1);
      h_waveform_TDC_n[ich]->GetYaxis()->SetLimits(tdcmin, tdcmax);
      h_waveform_TDC_n[ich]->GetYaxis()->SetRangeUser(tdcmin, tdcmax);
      h_waveform_TDC_n[ich]->Draw();
    }
    padn1->Update();
    padn2->Update();
    c_waveform_n->Update();
    c_waveform_n->cd();
    c_waveform_n->Modified();
    c_waveform_n->SaveAs(Form("%s/Waveform_north_%s.pdf",outdir.c_str(),saven.c_str()));
  }
} 
