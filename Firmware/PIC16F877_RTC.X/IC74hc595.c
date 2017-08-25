#include "IC74hc595.h"
#include"delay.h"

// *****************************************************************************
void vSendData595(unsigned char x)
{
    // type595 = 595 DATA
    // type595 = 595 Select LED
    unsigned char i, temp;    
    
        for(i=0;i<8;i++)
        {
            temp=x;
            temp=temp&0x80;
            if(temp==0x80)
            {
                DATA_595=1;
            }
            else
            {
                DATA_595=0;
            }
            x <<= 1;

            SCK_595 = 0;  
            DELAY_us(10);
            SCK_595 = 1;            
        }
//        SCL_595 = 0;
//        DELAY_us(10);
//        SCL_595 = 1;
}

// *****************************************************************************
unsigned char Binary2BCD(unsigned char a)
{
   unsigned char t1, t2;
   t1 = a%10;
   t1 = t1 & 0x0F;
   a = a/10;
   t2 = a%10;
   t2 = 0x0F & t2;
   t2 = t2 << 4;
   t2 = 0xF0 & t2;
   t1 = t1 | t2;
   return t1;
}