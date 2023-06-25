#ifndef runDrawHist_h
#define runDrawHist_h

#include <iostream>
#include "makeLL1MBDHist.C"


TH1D* h_waveform;
TCanvas* c_waveform;

int channelsel= 20;

double text_etax = 0.5;
double text_etay = 0.5;
double text_phix = 0.5;
double text_phiy = 0.3;
double text_ex = 0.4;
double text_ey = 0.6;
double legx1 = 0.00;
double legx2 = 0.3;
double legy1 = 0.00;
double legy2 = 0.06;

double margin_l = 0.150;
double margin_r = 0.145;
double margin_t = 0.11;
double margin_b = 0.12;

double sphenix_x = 0.17;
double sphenix_y = 0.92;
double sphenix_textsize = 21;
double sphenix_textsize_sq = 18;
double col_x = 0.57;
double col_y = 0.92;
double col_textsize = 21;
double col_textsize_sq = 18;
    
double adcmin=1000; double adcmax=2700;
double tdcmin=0; double tdcmax=12000;
double yshift = 0.04;
double sphenix_y_shift = sphenix_y+yshift;
double col_y_shift = col_y + yshift;
double xshift[6] = {0.13, 0.04, 0.1, 0.05, 0.56, 0.28};
double xshift_sq[4] = {0.125, 0.01,0.03,0.21};

void SetCanvasStyle(TCanvas* c, TH1* h, bool islogy)
{
  if(islogy) c->SetLogy();
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
