/*
 * File:   display.c
 * Author: pml
 *
 * Created on September 10, 2017, 10:51 AM
 */


#include "display.h"


void vDisplay(uint8_t ui8First, uint8_t ui8Second, uint8_t ui8Thrd, uint8_t ui8Fourth)
{
        PORTD = ucBCD_ARR[ui8Fourth];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_MINUTE_UNIT;
        DELAY_ms(DELAY_BTW_LED);
        
        PORTD = ucBCD_ARR[ui8Thrd];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_MINUTE_DOZEN;
        DELAY_ms(DELAY_BTW_LED);
        
        PORTD = ucBCD_ARR[ui8Second];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_HOUR_UNIT;
        DELAY_ms(DELAY_BTW_LED);
        
        PORTD = ucBCD_ARR[ui8First];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_HOUR_DOZEN;
        DELAY_ms(DELAY_BTW_LED);
}

uint8_t ui8Dec2HexDisplay(uint8_t ui8Input)
{    
    uint8_t ui8Output;
    uint8_t ui8Temp;
    
    ui8Temp = (uint8_t)ui8Input/10;
    ui8Output = ui8Temp;
    ui8Output <<= 4;
    
    ui8Temp = (uint8_t)ui8Input%10;
    ui8Output |= ui8Temp;
    
    return ui8Output;
}

uint8_t ui8Hex2DECDisplay(uint8_t ui8Input)
{        
    /*  Display 0x16(hex) = 16(dec)    */
    uint8_t ui8Temp;
    ui8Temp = ui8Input & 0xF0;
    ui8Temp >>= 4;
    return ((ui8Temp * 10) + (ui8Input & 0x0F));
}