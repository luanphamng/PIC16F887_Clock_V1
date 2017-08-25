/*
 * File:   pic16f887_rtc.c
 * Author: Liam
 * PIC16F887 connect with RTC DS 1307, control home automatic-light
 * Created on June 22, 2017, 1:36 PM
 */

#include <xc.h>
#include "pic16f887.h"
#include <stdio.h>
#include <stdbool.h>

#include "i2c.h"
#include "ds1307.h"
// ****************************************************************************
// CONFIG
#pragma config FOSC = XT   // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF  // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF   // Low-Voltage In-Circuit Serial Programming Enable bit
#pragma config CPD = OFF   // Data EEPROM Memory Code Protection bit 
#pragma config WRT = OFF   // Flash Program Memory Write Enable bits 
#pragma config CP = OFF    // Flash Program Memory Code Protection bit
// ****************************************************************************

// ****************************************************************************
#define _XTAL_FREQ 8000000
// ****************************************************************************


void main(void) {
    
    // *************************************************************************
    unsigned short second;
    // *************************************************************************
    second = 0;
    // *************************************************************************
    TRISAbits.TRISA0 = 0;
    PORTAbits.RA0 = 0;
    I2C_Master_Init(100000);
    for(;;)
    {
        second = read_ds1307(0) % 2;
        if(0 == second)
        {
            PORTAbits.RA0 = 0;
        }
        else
        {
            PORTAbits.RA0 = 1;
        }
    }
    return;
}
