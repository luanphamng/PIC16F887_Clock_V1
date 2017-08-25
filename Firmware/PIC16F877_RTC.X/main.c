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

#define _XTAL_FREQ 8000000
#define INCREASE 1
#define DECCREASE 0


int main() 
{
// *****************************************************************************    
// Init all IO    
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    TRISDbits.TRISD0 = 0;
    TRISDbits.TRISD1 = 0;
    
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1; // Increase button
    TRISBbits.TRISB2 = 1; // Decrease button
    TRISBbits.TRISB7 = 0; // Test output
    
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    WPUBbits.WPUB2 = 1;
    OPTION_REGbits.nRBPU = 0;
    
    ANSELHbits.ANS12 = 0;   //Disable Anolog for RB0, RB1, RB2
    ANSELHbits.ANS10 = 0;
    ANSELHbits.ANS8 = 0;
    
    IOCB = 0x00;// Disable interrupt on change
// *****************************************************************************    
    PORTBbits.RB7 = 1;
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
    rtc.hour = 0x23; //  10:40:20 am
    rtc.min =  0x59;
    rtc.sec =  0x56;

    rtc.date = 0x31; //1st Jan 2016
    rtc.month = 0x12;
    rtc.year = 0x16;
    rtc.weekDay = 5; // Friday: 5th day of week considering monday as first day.
    
// *****************************************************************************
// Set the time and Date only once. Once the Time and Date is set, comment these lines
// and re-flash the code. Else the time will be set every time the controller is reset*/
    RTC_SetDateTime(&rtc);  //  10:40:20 am, 1st Jan 2016

    /* Display the Time and Date continuously */
    while(1)
    { 
        if(PORTBbits.RB0 == 0)
        {
            DELAY_ms(50);
            if(PORTBbits.RB0 == 0)
            {
                ucSetCnt++;
                if(ucSetCnt > 6)
                {
                    ucSetCnt = 0;
                }
            } 
        }
        
        if(ucSetCnt)
        {
             // if Decrease button was pressed
            if(PORTBbits.RB2 == 0)
            {
                DELAY_ms(50);
                if(PORTBbits.RB2 == 0)
                {
                    ucSetData =  DECCREASE;                    
                    PORTBbits.RB7 = 0;
                } 
            }
            else
            {
                //Nothing
            }
            
            // If increase button was pressed        
            if(PORTBbits.RB1 == 0)
            {
                DELAY_ms(50);
                if(PORTBbits.RB1 == 0)
                {
                    ucSetData = INCREASE;
                    PORTBbits.RB7 = 1;
                } 
            }
            else
            {
                //Nothing
            }                                  
        }
        else
        {
            //Do nothing if ucSetCnt == 0;
        }
        
        RTC_GetDateTime(&rtc);
        LED1 = 1; LED2 = 1;
        ucSec = rtc.sec;   
        ucMin = rtc.min;        
        ucHours = rtc.hour;        
        ucDate = rtc.date;        
        ucMonth = rtc.month;        
        ucYear = rtc.year;        
        
                
        vSendData595(~ucBCD_ARR[(ucSec & 0xF0) >> 4]);
        vSendData595(~ucBCD_ARR[(ucMin & 0xF0) >> 4]);
        vSendData595(~ucBCD_ARR[(ucHours & 0xF0) >> 4]);
        vSendData595(~ucBCD_ARR[(ucYear & 0xF0) >> 4]);
        vSendData595(~ucBCD_ARR[(ucMonth & 0xF0) >> 4]);
        vSendData595(~ucBCD_ARR[(ucDate & 0xF0) >> 4]);        
        SCL_595 = 0;
        DELAY_us(10);
        SCL_595 = 1;
        
        LED1 = 0; LED2 = 1;
        DELAY_ms(5);
        
        LED2 = 1; LED1 = 1;
        vSendData595(~ucBCD_ARR[ucSec & 0x0F]);
        vSendData595(~ucBCD_ARR[ucMin & 0x0F]);
        vSendData595(~ucBCD_ARR[ucHours & 0x0F]);
        vSendData595(~ucBCD_ARR[ucYear & 0x0F]);
        vSendData595(~ucBCD_ARR[ucMonth & 0x0F]);
        vSendData595(~ucBCD_ARR[ucDate & 0x0F]);        
        SCL_595 = 0;
        DELAY_us(10);
        SCL_595 = 1;
        
        LED1 = 1; LED2 = 0;
        DELAY_ms(5);
    }

    return (0);
}










