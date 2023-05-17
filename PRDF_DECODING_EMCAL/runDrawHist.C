#include <iostream>
#include "runDrawHist.h"

void runDrawHist(int i=2)
{
  makehist t;
  t.Loop(i);

  TFile* rf;
  if(i>0) rf = new TFile(Form("OutputHist_event%d.root",i),"read");
  else rf = new TFile("OutputHist_all.root","read");

  string outdir = "plots";
  void * dirf = gSystem->OpenDirectory(outdir.c_str());
  if(dirf) gSystem->FreeDirectory(dirf);
  else {gSystem->mkdir(outdir.c_str(), kTRUE);}

  TH1D* h_event = (TH1D*) rf->Get("h_event");
  TH1D* h_energy = (TH1D*) rf->Get("h_energy");
  TH1D* h_energy_eta = (TH1D*) rf->Get("h_energy_eta");
  TH1D* h_energy_phi = (TH1D*) rf->Get("h_energy_phi");
  TH2D* h_energy_map = (TH2D*) rf->Get("h_energy_map");

  int sc = h_event->GetBinContent(1);
  
  string strevt = (i>0) ? Form("Event %d",i) : Form("Event all (%d)",sc);

  h_energy->Scale(1./sc);
  h_energy_eta->Scale(1./sc);
  h_energy_phi->Scale(1./sc);

  gStyle->SetOptStat(0);
  TCanvas* c_2dmap = new TCanvas("c_2Dmap","",600,600);
  c_2dmap->cd();
  c_2dmap->SetLeftMargin(0.15);
  c_2dmap->SetRightMargin(0.16);
  h_energy_map->Draw("colz");
  h_energy_map->SetTitle("#eta vs #phi tower energy map");

  TCanvas* c_2dmap_avg = new TCanvas("c_2Dmap_avg","",600,600);
  c_2dmap_avg->cd();
  c_2dmap_avg->SetLeftMargin(0.15);
  c_2dmap_avg->SetRightMargin(0.16);
  h_energy_map->Scale(1./sc);
  h_energy_map->Draw("colz");
  h_energy_map->SetTitle("#eta vs #phi tower energy map");

  TCanvas* c_energy_eta = new TCanvas("c_energy_eta","",600,600);
  c_energy_eta->cd();
  c_energy_eta->SetLeftMargin(0.14);
  c_energy_eta->SetRightMargin(0.13);
  SetHistStyleSmall(h_energy_eta,0,4);
  h_energy_eta->Draw();
  drawText(strevt.c_str(),0.6,0.5,1,17);

  TCanvas* c_energy_phi = new TCanvas("c_energy_phi","",600,600);
  c_energy_phi->cd();
  c_energy_phi->SetLeftMargin(0.14);
  c_energy_phi->SetRightMargin(0.13);
  SetHistStyleSmall(h_energy_phi,0,4);
  h_energy_phi->Draw();
  drawText(strevt.c_str(),0.5,0.3,1,17);

  TCanvas* c_energy = new TCanvas("c_energy","",600,600);
  c_energy->cd();
  c_energy->SetLogy();
  c_energy->SetLeftMargin(0.11);
  c_energy->SetRightMargin(0.08);
  SetHistStyleSmall(h_energy,0,4);
  h_energy->Draw();
  drawText(strevt.c_str(),0.7,0.8,1,17);

  if(i>0){
    h_waveform = (TH1D*) rf->Get(Form("h_waveform_eta%d_phi%d",etabinsel,phibinsel));
    c_waveform = new TCanvas(Form("c_waveform_event%d",i),"",600,600);
    c_waveform->cd();
    h_waveform->Scale(1./sc);
    SetHistStyleSmall(h_waveform,0,4);
    c_waveform->SetLeftMargin(0.14);
    c_waveform->SetRightMargin(0.13);
    h_waveform->Draw("LPE");
    c_waveform->SaveAs(Form("%s/waveform_event%d_etabin%d_phibin%d.pdf",outdir.c_str(),i,etabinsel,phibinsel));
    c_2dmap->SaveAs(Form("%s/c_EMCAL_2D_mapping_event%d.pdf",outdir.c_str(),i));
    c_2dmap_avg->SaveAs(Form("%s/c_EMCAL_2D_mapping_avg_event%d.pdf",outdir.c_str(),i));
    c_energy_eta->SaveAs(Form("%s/c_energy_eta_event%d.pdf",outdir.c_str(),i));
    c_energy_phi->SaveAs(Form("%s/c_energy_phi_event%d.pdf",outdir.c_str(),i));
    c_energy->SaveAs(Form("%s/c_energy_event%d.pdf",outdir.c_str(),i));
  }
  else{
    c_2dmap->SaveAs(Form("%s/c_EMCAL_2D_mapping_all.pdf",outdir.c_str()));
    c_2dmap_avg->SaveAs(Form("%s/c_EMCAL_2D_mapping_avg_all.pdf",outdir.c_str()));
    c_energy_eta->SaveAs(Form("%s/c_energy_eta.pdf",outdir.c_str()));
    c_energy_phi->SaveAs(Form("%s/c_energy_phi.pdf",outdir.c_str()));
    c_energy->SaveAs(Form("%s/c_energy.pdf",outdir.c_str()));
  }

} 
