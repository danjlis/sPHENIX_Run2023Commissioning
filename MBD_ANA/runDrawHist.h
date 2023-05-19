#ifndef runDrawHist_h
#define runDrawHist_h

#include <iostream>
#include "makeMBDhist.C"


TH1D* h_waveform;
TCanvas* c_waveform;

int channelsel= 20;
string str_date = "05/18/2023";

double text_etax = 0.5;
double text_etay = 0.5;
double text_phix = 0.5;
double text_phiy = 0.3;
double text_ex = 0.4;
double text_ey = 0.6;
double legx1 = 0.45;
double legx2 = 0.65;
double legy1 = 0.6;
double legy2 = 0.7;

double margin_l = 0.153;
double margin_r = 0.145;
double margin_t = 0.11;
double margin_b = 0.12;

double sphenix_x = 0.17;
double sphenix_y = 0.92;
double sphenix_textsize = 21;
double col_x = 0.65;
double col_y = 0.92;
double col_textsize = 21;

void SetCanvasStyle(TCanvas* c, TH1* h)
{
  c->SetLogy();
  c->cd();
  c->SetLeftMargin(margin_l);
  c->SetRightMargin(margin_r);
  c->SetRightMargin(margin_t);
  SetHistStyleSmall(h,0,2);
  h->Draw("PE");
  drawText("#bf{#it{sPHENIX}} Internal",sphenix_x,sphenix_y,1,sphenix_textsize);
  drawText("Au+Au #sqrt{s_{NN}}=200 GeV",col_x,col_y,1,col_textsize);
}


#endif
