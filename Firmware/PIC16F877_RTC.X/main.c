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
#include <xc.h>
#include "userdefine.h"
#include "display.h"

// PIC16F887 Configuration Bit Settings
//

#define _XTAL_FREQ 16000000



int main() 
{
// *****************************************************************************    
// Init all IO    
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    
    TRISD = 0x00;
    
    TRISBbits.TRISB0 = 1;   // Up button
    TRISBbits.TRISB1 = 1;   // Down button
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
    
    uint8_t ui8SetMode;
    uint8_t ui8SetValue;
    
    rtc_t rtc;

// *****************************************************************************
// Assign initials value for newly defined variables    
    ucSec = 0;
    ucMin = 0;
    ucHours = 0;
    ucDate = 0;
    ucMonth = 0;
    ucYear = 0;
    
    ui8SetMode = 0;
    ui8SetValue = 0;
    
    
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
    //RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016

    /* Display the Time and Date continuously */
    while(1)
    { 
        //Check button first
        
        if(BUTTON_MODE == 0)    //If pressed mode button
        {
            DELAY_ms(100);
            if(BUTTON_MODE == 0)    //If pressed
            {
                ui8SetMode++;
            }
            
        }
        
            if(BUTTON_MODE == 0)    //If pressed mode button
            {
                DELAY_ms(100);
                if(BUTTON_MODE == 0)    //If pressed
                {
                    ui8SetMode++;
                    if(ui8SetMode > ENDMODE)
                    {
                        ui8SetMode = NOCHANGE;  /*  Do the limit for ui8SetMode */
                    }
                }

            }
            if(BUTTON_ADJUST == 0)    //If pressed
            {
                DELAY_ms(100);
                if(BUTTON_ADJUST == 0)    //If pressed
                {
                    ui8SetValue = 1;                
                }            
            }
            /*  Get date and time before process    */
            RTC_GetDateTime(&rtc);
            ucSec = rtc.sec;   
            ucMin = ui8Hex2DECDisplay(rtc.min);        
            ucHours = ui8Hex2DECDisplay(rtc.hour);        
            ucDate = ui8Hex2DECDisplay(rtc.date);        
            ucMonth = ui8Hex2DECDisplay(rtc.month);        
            ucYear = ui8Hex2DECDisplay(rtc.year); 

            /*  Check input from user   */
            switch(ui8SetMode)
            {
                case SEC:
                {
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucSec = 56;
                        if(ucSec >= 60)
                        {
                            ucSec = 0;
                        }                    
                    }
                    

                    vDisplay(H_SYMBOL,0,ucSec/10, ucSec%10);

                    break;
                }
                case MINUTE:
                {
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucMin++;
                        if(ucMin >=60)
                        {
                            ucMin = 0;
                        }
                    }
                    vDisplay(0,0,0,ui8SetMode);
                    break;
                }
                case HOUR:
                {
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucHours++;
                        if(ucHours >=13)
                        {
                            ucHours = 0;
                        }
                    }
                    vDisplay(0,0,0,ui8SetMode);
                    break;
                }
                case DAY:
                {
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucDate++;
                        if(ucDate >=31)
                        {
                            ucDate = 0;
                        }
                    }
                    vDisplay(0,0,0,ui8SetMode);
                    break;
                }
                case MONTH:
                {
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucMonth++;
                        if(ucMonth >=13)
                        {
                            ucMonth = 0;
                        }
                    }
                    vDisplay(0,0,0,ui8SetMode);
                    break;
                }
                case YEAR:
                {   
                    if(ui8SetValue == 1)
                    {
                        ui8SetValue = 0;
                        ucYear++;
                        if(ucYear >= 2099)
                        {
                            ucYear = 0;
                        }
                    }
                    vDisplay(0,0,0,ui8SetMode);
                    break;
                }
                case WEEKDAY:
                {   
                    vDisplay(0,0,0,ui8SetMode);
                    break;

                }
                case ENDMODE:
                {
                    /* Copy rtc time    */
                    rtc.sec = ui8Dec2HexDisplay(ucSec);
                    rtc.min = ui8Dec2HexDisplay(ucMin);
                    rtc.hour = ui8Dec2HexDisplay(ucHours);
                    rtc.date = ui8Dec2HexDisplay(ucDate);
                    rtc.month = ui8Dec2HexDisplay(ucMonth);
                    rtc.year = ui8Dec2HexDisplay(ucYear);

                    /*  Save rtc time to DS1307   */
                    RTC_SetDateTime(&rtc);
                    ui8SetMode = 0;
//                    vDisplay(((rtc.min & 0xF0) >> 4), (rtc.min & 0x0F),((rtc.sec & 0xF0) >> 4), (rtc.sec & 0x0F));
                    vDisplay(1,2,3,4);
                    break;
                }
                default: //NOCHANGE
                {
                    vDisplay(((0x25 & 0xF0) >> 4), (0x25 & 0x0F),((0x17 & 0xF0) >> 4), (0x17 & 0x0F));
                    break;
                }
            }
    }

    return (0);
}










