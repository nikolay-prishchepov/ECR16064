/*
 * ERC16064.h - Library for display numbers.
 * Driver ST7528.
 * SPI 4-Wire.
 * http://www.buy-display.com/download/interfacing/ERC16064-1_Interfacing.pdf
 * Created by Nikolay Prishhcepov, June 18, 2015.
 * Released into the public domain.
 */

#ifndef ERC16064_h
#define ERC16064_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#include <avr/io.h>
#include <util/delay.h>

#define uint unsigned int
#define uchar unsigned char

#define ModeSet             0x38
#define ModeSetP1           0x64    //EXT=0
#define ModeSetP2           0x65    //EXT=1

#define Display_on          0xaf
#define Display_off         0xae

#define Regulator           0x26
#define Contrast_level      0x81
#define Contrast_levelP     0x0B

#define PowerControll_on1   0x2c
#define PowerControll_on2   0x2e
#define PowerControll_on3   0x2f

#define LcdBias_9           0x54
#define InterOsc_on         0xab
#define EntireDisp_on       0xa5
#define EntireDisp_off      0xa4
#define BoostLevel_5        0x66
#define Duty_set            0x48
#define Duty_setP           0x40
#define Start_columnlsb     0x00
#define Start_columnmsb     0x10
#define Start_page          0xb0
#define StartLine_set       0x40
//#define    StartLine_setP    0x00
#define Set_Initial_COM0    0x44
#define Set_Initial_COM0P   0x12


#define Entire_Displa_ON    0xA5
#define Entire_Displa_OFF   0xA4

#define FrcPwm_set          0x92
#define NLineInversion_on   0x4c
#define NLineInversion_onP  0x1f
#define NLineInversion_off  0xe4    
#define ReverseDisp_on      0xa7
#define ReverseDisp_off     0xa6
#define AdcSelect           0xa0
#define ComScanDirection    0xc8

//pin setting
#define SDAPORT PORTB //data  //set port
#define SDA     PB3           //set pin
#define SDADDR  DDRB          //set output

#define SCLPORT PORTB //clock
#define SCL     PB5
#define SCLDDR  DDRB

#define A0PORT PORTB  //data/command select
#define A0     PB1
#define A0DDR  DDRB

#define CSPORT PORTB  //chip select
#define CS     PB2
#define CSDDR  DDRB

#define RSTPORT PORTB //reset
#define RST     PB0
#define RSTDDR  DDRB
//

#define A0_INIT A0DDR  |= (1<<A0)
#define A0_ON   A0PORT |= (1<<A0)
#define A0_OFF  A0PORT &= ~(1<<A0)
#define A0_SW   A0PORT ^= (1<<A0)

#define CS_INIT CSDDR  |= (1<<CS)
#define CS_ON   CSPORT |= (1<<CS)
#define CS_OFF  CSPORT &= ~(1<<CS)
#define CS_SW   CSPORT ^= (1<<CS)

#define RST_INIT RSTDDR  |= (1<<RST)
#define RST_ON   RSTPORT |= (1<<RST)
#define RST_OFF  RSTPORT &= ~(1<<RST)
#define RST_SW   RSTPORT ^= (1<<RST)

#define SCL_INIT SCLDDR  |= (1<<SCL)
#define SCL_ON   SCLPORT |= (1<<SCL)
#define SCL_OFF  SCLPORT &= ~(1<<SCL)
#define SCL_SW   SCLPORT ^= (1<<SCL)

#define SDA_INIT SDADDR  |= (1<<SDA)
#define SDA_ON   SDAPORT |= (1<<SDA)
#define SDA_OFF  SDAPORT &= ~(1<<SDA)
#define SDA_SW   SDAPORT ^= (1<<SDA)

static uchar num[] =
{
    0x00, 0xFC, 0xFE, 0x07, 0x03, 0x03, 0x07, 0xFE, 0xFC, 0x00, 0x00, 0x3F, 0x7F, 0xE0, 0xC0, 0xC0, 0xE0, 0x7F, 0x3F, 0x00,  // Code for char 0
    0x00, 0x00, 0x0C, 0x0C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00,  // Code for char 1
    0x00, 0x1C, 0x1E, 0x07, 0x03, 0x83, 0xC7, 0xFE, 0x7C, 0x00, 0x00, 0xF8, 0xFC, 0xCE, 0xC7, 0xC3, 0xC1, 0xC0, 0xC0, 0x00,  // Code for char 2
    0x00, 0x1C, 0x1E, 0x07, 0x83, 0x83, 0xC7, 0xFE, 0x7C, 0x00, 0x00, 0x38, 0x78, 0xE0, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00,  // Code for char 3
    0x00, 0x00, 0xC0, 0xF0, 0x3C, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x0F, 0xCD, 0xCC, 0xFF, 0xFF, 0xCC, 0xCC, 0x00,  // Code for char 4
    0x00, 0xFF, 0xFF, 0x83, 0x83, 0x83, 0x83, 0x03, 0x03, 0x00, 0x00, 0x31, 0x71, 0xE1, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00,  // Code for char 5
    0x00, 0xF0, 0xFC, 0x9E, 0x87, 0x83, 0x83, 0x03, 0x00, 0x00, 0x00, 0x3F, 0x7F, 0xE1, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00,  // Code for char 6
    0x00, 0x03, 0x03, 0x03, 0x03, 0xC3, 0xE3, 0x7F, 0x3F, 0x00, 0x00, 0x00, 0x00, 0xFC, 0xFF, 0x07, 0x01, 0x00, 0x00, 0x00,  // Code for char 7
    0x00, 0x7C, 0xFE, 0xC7, 0x83, 0x83, 0xC7, 0xFE, 0x7C, 0x00, 0x00, 0x3E, 0x7F, 0xE3, 0xC1, 0xC1, 0xE3, 0x7F, 0x3E, 0x00,  // Code for char 8
    0x00, 0x7C, 0xFE, 0xC7, 0x83, 0x83, 0x87, 0xFE, 0xFC, 0x00, 0x00, 0x00, 0x00, 0xC1, 0xC1, 0xE1, 0x79, 0x3F, 0x0F, 0x00,  // Code for char 9
    0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00   // Code for char -
};

class ERC16064
{
  public:
    ERC16064();
    void Initialize();
    void Write_number(uchar k, uchar row, uchar col);
    void Clear();
    
  private:
    void Write_command(uchar command);
    void Write_data(uchar datas);
};

#endif  //  #ifndef ERC16064_h
