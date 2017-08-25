#include "i2c.h"

short z;
// *****************************************************************************
// Master function (Slave below))
// *****************************************************************************


// *****************************************************************************
// c = frequency (Example: c = 100 000 (Hz) ))
// *****************************************************************************
void I2C_Master_Init(const unsigned long c)
{
  SSPCON = 0b00101000;
  SSPCON2 = 0;
  SSPADD = (_XTAL_FREQ/(4*c))-1;
  SSPSTAT = 0;
  TRISC3 = 1;        //Setting as input as given in datasheet
  TRISC4 = 1;        //Setting as input as given in datasheet
}

void I2C_Master_Wait()
{
  while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Master_Start()
{
  I2C_Master_Wait();
  SEN = 1;
}

void I2C_Master_RepeatedStart()
{
  I2C_Master_Wait();
  RSEN = 1;
}

void I2C_Master_Stop()
{
  I2C_Master_Wait();
  PEN = 1;
}

void I2C_Master_Write(unsigned d)
{
  I2C_Master_Wait();
  SSPBUF = d;
}

unsigned short I2C_Master_Read(unsigned short a)
{
  unsigned short temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;
  I2C_Master_Wait();
  ACKDT = (a)?0:1;
  ACKEN = 1;
  return temp;
}


// *****************************************************************************
// Slave function
// *****************************************************************************
void interrupt I2C_Slave_Read()
{
  if(SSPIF == 1)
  {
    SSPCONbits.CKP = 0;

    if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL))
    {
      z = SSPBUF; // Read the previous value to clear the buffer
      SSPCONbits.SSPOV = 0; // Clear the overflow flag
      SSPCONbits.WCOL = 0;  // Clear the collision bit
      SSPCONbits.CKP = 1;
    }

    if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW)
    {
      z = SSPBUF;
      while(!BF);
      PORTD = SSPBUF;
      SSPCONbits.CKP = 1;
    }
    else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW)
    {
      z = SSPBUF;
      BF = 0;
      SSPBUF = PORTB ;
      SSPCONbits.CKP = 1;
      while(SSPSTATbits.BF);
    }

    SSPIF = 0;
  }
}

void I2C_Slave_Init(short address)
{
  SSPSTAT = 0x80;
  SSPADD = address;
  SSPCON = 0x36;
  SSPCON2 = 0x01;
  TRISC3 = 1;   //Setting as input as given in datasheet
  TRISC4 = 1;   //Setting as input as given in datasheet
  GIE = 1;
  PEIE = 1;
  SSPIF = 0;
  SSPIE = 1;
}
