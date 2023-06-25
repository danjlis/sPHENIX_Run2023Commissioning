#ifndef mbdEmulator_h
#define mbdEmulator_h

#include <iostream>

unsigned int m_out_tsum[2] = {0,0};
unsigned int m_out_tavg[2] = {0,0};
unsigned int m_out_nhit[2] = {0,0};
unsigned int m_out_trem[2] = {0,0};
unsigned int m_out_vtx_sub = 0;
unsigned int m_out_vtx_add = 0;

//! Trigger primitives                                     
unsigned int m_trig_charge[4][8];
int max = 20;
unsigned int m_trig_nhit[4];
unsigned int m_trig_time[4][4];

unsigned int pmp[256];
int ipmp[256];
unsigned int qadd[32];
unsigned int tmp;
unsigned int tmp2;
unsigned int tmp3;
int hit1, hit2, time1, time2, time3;


unsigned int m_l1_adc_table[1024];
unsigned int m_l1_slewing_table[4096];



void EmulateTrigger(int adc[][31], unsigned int trig[][25], int *hitmap)
{

  unsigned int i, j, ns, diff;
  for (i = 0; i < 1024; i++)
    {
      m_l1_adc_table[i] = (i) & 0x3ff;
    }

  for (i = 0; i < 4096; i++)
    {
      m_l1_slewing_table[i] = (i) & 0x1ff;
    }

  for (int ig = 0; ig < 20; ig++)
    {
      
      for (i = 0; i < 4; i++)
	{
	  for (j = 0; j < 4; j++)
	    {
	      m_trig_time[i][j] = 0;
	    }
	  m_trig_nhit[i] = 0;
	  for (j = 0; j < 8; j++)
	    {
	      m_trig_charge[i][j] = 0;
	    }
	} 

      for (int ee = 0 ; ee < 256; ee++)
	{
	  ipmp[ee] =  adc[ee][ig + 7] - adc[ee][ig];
	  if (ipmp[ee] < 0) ipmp[ee] = 0;
	  pmp[ee] = static_cast<unsigned int>(ipmp[ee] & 0x3ff);
	} 

      for (int iadc = 0; iadc < 4; iadc++)
	{

	  for (int ns = 0; ns < 32; ns++)
	    {
	      tmp2 = iadc*64 + 8 + (ns/8)*16 + (ns%8);
	      tmp = m_l1_adc_table[ipmp[tmp2] >> 4];
	      
	      qadd[ns] = (tmp & 0x380) >> 7;
	      m_trig_charge[3 - iadc][ns/4] += tmp & 0x3ff;
	    }
	  
	  m_trig_nhit[3 - iadc] = 0;
	  
	  for (int ns = 0; ns < 32 ; ns++)
	    {
	      tmp2 = iadc*64 + (ns/8)*16 + (ns%8);
	      tmp = m_l1_adc_table[ipmp[tmp2]>>4];
	      if (ig == 5) hitmap[iadc*32 + ns] += (tmp & 0x200) >> 9;
	      m_trig_nhit[3 - iadc] += (tmp & 0x200) >> 9;	      
	      tmp3 = m_l1_slewing_table[(qadd[ns] << 9) + (tmp & 0x01ff)];
	      m_trig_time[3 - iadc][ns/8] += tmp3;
	      
	    }
	  
	}

      m_out_nhit[0] = 0;
      m_out_nhit[1] = 0;
      m_out_tsum[0] = 0;
      m_out_tsum[1] = 0;

      for (ns = 0; ns < 2; ns++)
	{
	  for (j = 0 ; j < 4 ; j++)
	    {
	      m_out_tsum[0] += m_trig_time[ns][j];
	      m_out_tsum[1] += m_trig_time[ns+2][j];
	    }
	  m_out_nhit[0] += m_trig_nhit[ns];
	  m_out_nhit[1] += m_trig_nhit[ns+2];
	}
      for (ns = 0; ns < 2; ns++)
	{
	  m_out_tavg[ns] = 0;
	  m_out_trem[ns] = 0;
	  if (m_out_nhit[ns] == 0) 
	    {
	      m_out_tavg[ns] = 0x7fff;
	      continue;
	    }
	  m_out_tavg[ns] = m_out_tsum[ns]/m_out_nhit[ns];
	  m_out_trem[ns] = m_out_tsum[ns]%m_out_nhit[ns];
	}
      if (m_out_tavg[0] > m_out_tavg[1]) diff = m_out_tavg[0] - m_out_tavg[1];
      else diff = m_out_tavg[1] - m_out_tavg[0];
      m_out_vtx_sub = diff;
      m_out_vtx_add = (m_out_tavg[0] + m_out_tavg[1]) & 0x3ff;
      for (int igg = 0;  igg < 4; igg++)
	{
	  int ii;
	  for (ii = 0; ii < 8; ii++)
	    { 
	      trig[igg*13+ii][ig] = m_trig_charge[igg][ii];
	    }
	  trig[igg*13+ii][ig] = m_trig_nhit[igg];
	  
	  for (ii = 0; ii < 4; ii++)
	    {
	      trig[igg*13+ 9 + ii][ig] = m_trig_time[igg][ii];
	    }
	}

      trig[52][ig] = m_out_tavg[0];
      trig[53][ig] = m_out_tavg[1];
      trig[54][ig] = m_out_nhit[0];
      trig[55][ig] = m_out_nhit[1];
      trig[56][ig] = m_out_trem[0];
      trig[57][ig] = m_out_trem[1];
      trig[58][ig] = m_out_vtx_sub;
      trig[59][ig] = m_out_vtx_add;

    }

}

#endif
