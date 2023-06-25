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
    cout << __FILE__<<__FUNCTION__<<__LINE__<<" Opening new file."<<endl;
    rf = new TFile(filename.c_str());
  }   

  string outdir = "plots";
  outdir += Form("/Run%d",RunNumber);
  void * dirf = gSystem->OpenDirectory(outdir.c_str());

  if(dirf) gSystem->FreeDirectory(dirf);
  else {gSystem->mkdir(outdir.c_str(), kTRUE);}

  string saven = Form("Run%d",RunNumber);
  string infotext = Form("#bf{%s} Run%d",str_date.c_str(),RunNumber);

  TH1D* h_time_diff = (TH1D*) rf->Get("h_time_diff");  
  TH2D* h_nhit_corr = (TH2D*) rf->Get("h_nhit_corr");
  TH2D* h_hit_check= (TH2D*) rf->Get("h_hit_check");
  TH2D* h_line_up = (TH2D*) rf->Get("h_line_up");
  TH2D* h_nhit_n_corr = (TH2D*) rf->Get("h_nhit_n_corr");
  TH2D* h_nhit_s_corr = (TH2D*) rf->Get("h_nhit_s_corr");
  TH1D* h_nhit_n1 = (TH1D*) rf->Get("h_nhit_n1");
  TH1D* h_nhit_n2 = (TH1D*) rf->Get("h_nhit_n2");
  TH1D* h_nhit_s1 = (TH1D*) rf->Get("h_nhit_s1");
  TH1D* h_nhit_s2 = (TH1D*) rf->Get("h_nhit_s2");
  gStyle->SetOptStat(0);
  TLine *line;

  TCanvas* c_nhit_corr= new TCanvas("c_nhit_corr","",700,700);
  gPad->SetTicks(1,1);
  c_nhit_corr->SetLogz();
  c_nhit_corr->SetLeftMargin(0.151);
  c_nhit_corr->SetRightMargin(0.153);
  h_nhit_corr->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y, 0, 1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y, 0, 1,col_textsize, 43);
  TLegend* leg_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_corr);
  leg_corr->SetHeader(infotext.c_str());
  leg_corr->Draw("same");
  line = new TLine(0, 0, 64, 64);
  SetLineAtt(line, kBlack, 4, 2);
  line->Draw();
  c_nhit_corr->SaveAs(Form("%s/hist_nhit_corr_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_line_up= new TCanvas("c_line_up","",700,700);
  gPad->SetTicks(1,1);
  c_line_up->SetLogz();
  c_line_up->SetLeftMargin(0.151);
  c_line_up->SetRightMargin(0.153);
  h_line_up->Draw("colz");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,0,1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,0,1,col_textsize, 43);
  TLegend* leg_line = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_line);
  leg_line->SetHeader(infotext.c_str());
  leg_line->Draw("same");
  c_line_up->SaveAs(Form("%s/hist_line_up_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_time_diff= new TCanvas("c_time_diff","",700,700);
  gPad->SetTicks(1,1);
  c_time_diff->SetLogz();
  c_time_diff->SetLeftMargin(0.151);
  c_time_diff->SetRightMargin(0.153);
  h_time_diff->Draw();
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,0,1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,0,1,col_textsize, 43);
  TLegend* leg_diff = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_diff);
  leg_diff->SetHeader(infotext.c_str());
  leg_diff->Draw("same");
  c_time_diff->SaveAs(Form("%s/hist_time_diff_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_nhit_n_corr= new TCanvas("c_nhit_n_corr","",700,700);
  gPad->SetTicks(1,1);
  c_nhit_n_corr->SetLogz();
  c_nhit_n_corr->SetLeftMargin(0.151);
  c_nhit_n_corr->SetRightMargin(0.153);
  h_nhit_n_corr->Draw("colz");
  line = new TLine(0, 0, 32, 32);
  SetLineAtt(line, kBlack, 4, 2);
  line->Draw();
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,0,1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,0,1,col_textsize, 43);
  TLegend* leg_n_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_n_corr);
  leg_n_corr->SetHeader(infotext.c_str());
  leg_n_corr->Draw("same");
  c_nhit_n_corr->SaveAs(Form("%s/hist_nhit_n_corr_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas* c_nhit_s_corr= new TCanvas("c_nhit_s_corr","",700,700);
  gPad->SetTicks(1,1);
  c_nhit_s_corr->SetLogz();
  c_nhit_s_corr->SetLeftMargin(0.151);
  c_nhit_s_corr->SetRightMargin(0.153);
  h_nhit_s_corr->Draw("colz");
  line = new TLine(0, 0, 32, 32);
  SetLineAtt(line, kBlack, 4, 2);
  line->Draw();
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,0,1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,0,1,col_textsize, 43);
  TLegend* leg_s_corr = new TLegend(legx1,legy1,legx2,legy2);
  SetLegendStyle(leg_s_corr);
  leg_s_corr->SetHeader(infotext.c_str());
  leg_s_corr->Draw("same");
  c_nhit_s_corr->SaveAs(Form("%s/hist_nhit_s_corr_%s.pdf",outdir.c_str(),saven.c_str()));

  TCanvas *c_nhit_4 = new TCanvas("c_nhit_4","", 700, 700);
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x+0.07,sphenix_y,0,1,sphenix_textsize, 43);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,0,1,col_textsize, 43);

  c_nhit_4->Divide(2,2);
  gPad->SetTicks(1,1);
  c_nhit_4->cd(1);
  h_nhit_n1->Draw("hist");
  drawText("North 1",col_x,col_y,0,1,col_textsize, 43);
  c_nhit_4->cd(2);
  h_nhit_n2->Draw("hist");
  drawText("North 2",col_x,col_y,0,1,col_textsize, 43);
  c_nhit_4->cd(3);
  h_nhit_s1->Draw("hist");
  drawText("South 1",col_x,col_y,0,1,col_textsize, 43);
  c_nhit_4->cd(4);
  h_nhit_s2->Draw("hist");
  drawText("South 2",col_x,col_y,0,1,col_textsize, 43);
  c_nhit_4->cd();
  c_nhit_4->SaveAs(Form("%s/hist_nhit_4_%s.pdf",outdir.c_str(),saven.c_str()));

}
