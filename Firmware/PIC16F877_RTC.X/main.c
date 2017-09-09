/*
 * File:   main.c
 * Author: Milinda
 *
 * Created on December 7, 2012, 7:52 AM
 */

#include <htc.h>
#include <pic16f887.h>
#include "rtc.h"
#include "delay.h"
#include "IC74hc595.h"
#include <xc.h>



// PIC16F887 Configuration Bit Settings
//

#define _XTAL_FREQ 16000000
#define INCREASE 1
#define DECCREASE 0
#define ON 1
#define OFF 0

#define LED_MINUTE_UNIT     0xDF
#define LED_MINUTE_DOZEN    0xEF
#define LED_HOUR_UINT       0xF7
#define LED_HOUR_DOZEN      0xFB
#define LED_CLEAR           0x3C    /*  Clear all LED   */
#define DELAY_BTW_LED       5

uint8_t ReverserByte(uint8_t ui8Input)
{
    uint8_t ui8Tmp;
    uint8_t ui8Tmp2;
    for(ui8Tmp2 = 0; ui8Tmp2 <= 8; ui8Tmp2++)
    {
        if((ui8Input && 0b00000001) == 1)
            ui8Tmp |= 0x01;
            
        ui8Input >>= 1;
        ui8Tmp <<= 1;
    }
    
    return ui8Tmp;
}


int main() 
{
// *****************************************************************************    
// Init all IO    
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    TRISD = 0x00;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1; // Increase button
    TRISBbits.TRISB2 = 0; 
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISBbits.TRISB5 = 0;
    
    TRISBbits.TRISB7 = 0; 
    
    TRISEbits.TRISE0 = 0;
    
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    OPTION_REGbits.nRBPU = 0;
    
    ANSELHbits.ANS12 = 0;   //Disable Anolog for RB0, RB1, RB2
    ANSELHbits.ANS10 = 0;
    ANSELHbits.ANS13 = 0;   //Disable Anolog for RB0, RB1, RB2
    ANSELHbits.ANS11 = 0;
    ANSELHbits.ANS9 = 0;
    ANSELHbits.ANS8 = 0;
    ANSELbits.ANS5 = 0;
    
    IOCB = 0x00;// Disable interrupt on change
// *****************************************************************************    
    PORTB = 0xFF;
// *****************************************************************************    
// Define new variables    
    uint8_t ucSec;
    uint8_t ucMin;
    uint8_t ucHours;
    uint8_t ucDate;
    uint8_t ucMonth;
    uint8_t ucYear;
    
    uint8_t ucSetData; // Settings button data = 0/1
    uint8_t ucSetCnt; // Settings button = 1 .. 6
//    uint8_t ucIncre;    // Increase button = 0/1
    
//    uint8_t ucDecre;    // Decrease button = 0/1
//    
    rtc_t rtc;

// *****************************************************************************
// Assign initials value for newly defined variables    
    ucSec = 0;
    ucMin = 0;
    ucHours = 0;
    ucDate = 0;
    ucMonth = 0;
    ucYear = 0;
    
    ucSetData = 0;
    ucSetCnt = 0;
//    ucIncre = 0;
//    ucDecre = 0;
    
    RTC_Init();

// *****************************************************************************
// New time to be written to DS1307    
    rtc.hour = 0x00; //  10:40:20 am
    rtc.min =  0x08;
    rtc.sec =  0x30;

    rtc.date = 0x31; //1st Jan 2016
    rtc.month = 0x12;
    rtc.year = 0x16;
    rtc.weekDay = 5; // Friday: 5th day of week considering monday as first day.
    
// *****************************************************************************
// Set the time and Date only once. Once the Time and Date is set, comment these lines
// and re-flash the code. Else the time will be set every time the controller is reset*/
    RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016

    /* Display the Time and Date continuously */
    PORTBbits.RB5 = 1;
    PORTBbits.RB4 = 1;
    while(1)
    { 
     
        RTC_GetDateTime(&rtc);
        ucSec = rtc.sec;   
        ucMin = rtc.min;        
        ucHours = rtc.hour;        
        ucDate = rtc.date;        
        ucMonth = rtc.month;        
        ucYear = rtc.year;        
        
        
                
        
        PORTD = ucBCD_ARR[ucSec&0x0F];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_MINUTE_UNIT;
        DELAY_ms(DELAY_BTW_LED);        
        
        PORTD = ucBCD_ARR[(ucSec&0xF0) >> 4];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_MINUTE_DOZEN;
        DELAY_ms(DELAY_BTW_LED);        
        
        PORTD = ucBCD_ARR[ucMin&0x0F];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_HOUR_UINT;
        DELAY_ms(DELAY_BTW_LED);        
        
        PORTD = ucBCD_ARR[(ucMin&0xF0) >> 4];        
        PORTB |= LED_CLEAR;
        PORTB &= LED_HOUR_DOZEN;        
        DELAY_ms(DELAY_BTW_LED);        
    }

    return (0);
}










