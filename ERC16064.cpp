/*
 * ERC16064.cpp - Library for display numbers.
 * Driver ST7528.
 * SPI 4-Wire.
 * http://www.buy-display.com/download/interfacing/ERC16064-1_Interfacing.pdf
 * Created by Nikolay Prishhcepov, June 18, 2015.
 * Released into the public domain.
 */
 
#ifndef ERC16064_cpp
#define ERC16064_cpp

#include "ERC16064.h"

ERC16064::ERC16064()
{
  Initialize();
}

void ERC16064::Write_command(uchar command)
{
  uint i;
  CS_OFF;
  A0_OFF;
  for(i = 0; i < 8; i++)
  {
    SCL_OFF;
    if(command&0x80)
      SDA_ON;
    else
      SDA_OFF;
    SCL_ON;
    command = command<<1;
  }
  CS_ON;
}

void ERC16064::Write_data(uchar datas)
{
  uint i;
  CS_OFF;
  A0_ON;
  for(i = 0; i < 8; i++)
  {
    SCL_OFF;
    if(datas&0x80)
      SDA_ON;
    else
      SDA_OFF;
    SCL_ON;
    datas = datas<<1;
  }
  CS_ON;
}

void ERC16064::Initialize()
{
  A0_INIT;
  CS_INIT;
  RST_INIT;
  SCL_INIT;
  SDA_INIT;
 
  uchar Gray_Parameters[]=
  {
    0x00,0x00,0x00,0x00, 0x04,0x04,0x04,0x04, 0x08,0x08,0x08,0x08, 0x0c,0x0c,0x0c,0x0c,
    0x10,0x10,0x10,0x10, 0x14,0x14,0x14,0x14, 0x18,0x18,0x18,0x18, 0x1c,0x1c,0x1c,0x1c,
    0x20,0x20,0x20,0x20, 0x24,0x24,0x24,0x24, 0x28,0x28,0x28,0x28, 0x2c,0x2c,0x2c,0x2c,
    0x30,0x30,0x30,0x30, 0x34,0x34,0x34,0x34, 0x38,0x38,0x38,0x38, 0x3c,0x3c,0x3c,0x3c,
  };

  uint i;
  RST_OFF;
  _delay_us(100);
  RST_ON;
  _delay_us(100);
 
  Write_command(ModeSet);
  Write_command(ModeSetP1);
  Write_command(InterOsc_on);
  Write_command(Set_Initial_COM0);
  Write_command(Set_Initial_COM0P);
 
  Write_command(AdcSelect);
  Write_command(ComScanDirection);
  Write_command(BoostLevel_5);
  _delay_us(100);
  Write_command(LcdBias_9);
  Write_command(Duty_set);
  Write_command(Duty_setP);
  Write_command(Regulator);
  Write_command(Contrast_level);
  Write_command(Contrast_levelP);
  Write_command(PowerControll_on1);
  _delay_ms(1);
  Write_command(PowerControll_on2);
  _delay_us(100);
  Write_command(PowerControll_on3);
  _delay_us(100);
  Write_command(FrcPwm_set);
 
  Write_command(ModeSet);
  Write_command(ModeSetP2);
 
  for(i=0;i<64;i++)
  {
    Write_command(0x80+i);
    Write_command(Gray_Parameters[i]);
  }
 
  Write_command(ModeSet);
  Write_command(ModeSetP1);
  Write_command(Display_on);
 
  Clear();
}

void ERC16064::Write_number(uchar k, uchar row, uchar col)
{
  uchar i;
 
  if(row >= 0 && row < 7 && col >= 0 && col < 16 && k >= 0 && k < 11)
  {
    Write_command(Start_page + row);
    Write_command(Start_columnlsb + ((col * 10) & 0x0f));
    Write_command(Start_columnmsb + ((col * 10) >> 4));

    for(i = 0; i < 10; i++)
    {
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
    }
   
    Write_command(Start_page + row + 1);
    Write_command(Start_columnlsb + ((col * 10) & 0x0f));
    Write_command(Start_columnmsb + ((col * 10) >> 4));

    for(i = 10; i < 20; i++)
    {
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
      Write_data(*(num+20*k+i));
    }
  }
}

void ERC16064::Clear()
{
  uint j,k;

  Write_command(StartLine_set);
  Write_command(0x00);
  for(j = 0; j < 8; j++)
  {
    Write_command(Start_page + j);
    Write_command(Start_columnlsb);
    Write_command(Start_columnmsb);
    for(k = 0; k < 160; k++)
    {
      Write_data(0);
      Write_data(0);
      Write_data(0);
      Write_data(0);
    }
  }
}


#endif  //  #ifndef ERC16064_cpp
