/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __USER_DEFINE__
#define	__USER_DEFINE__

#include <xc.h> // include processor files - each processor file is guarded.  

#define LED_MINUTE_UNIT     0xDF
#define LED_MINUTE_DOZEN    0xEF
#define LED_HOUR_UNIT       0xF7
#define LED_HOUR_DOZEN      0xFB
#define LED_CLEAR           0x3C    /*  Clear all LED   */
#define DELAY_BTW_LED       5       /*  milisecond  */

#define BUTTON_ADJUST     PORTBbits.RB0

#define INCREASE 1
#define DECCREASE 0
#define ON 1
#define OFF 0

#define BUTTON_MODE       PORTBbits.RB1
#define NOCHANGE    0
#define SEC         1
#define MINUTE      2
#define HOUR        3
#define DAY         4
#define MONTH       5
#define YEAR        6
#define WEEKDAY     7
#define ENDMODE     8
#define SEC_SYMBOL      0xB6

#define I_SYMBOL     0xEC
#define H_SYMBOL     0x6E
#define O_SYMBOL      0xFC
#define A_SYMBOL      0xFC
#define Y_SYMBOL      0xFC

#define MONTH_SYMBOL    0xB6
#define YEAR_SYMBOL     0xB6

unsigned char ucBCD_ARR[10]= {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

