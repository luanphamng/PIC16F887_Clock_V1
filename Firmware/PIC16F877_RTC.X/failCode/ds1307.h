/* 
 * File:   ds1307.h
 * Author: Liam
 *
 * Created on June 22, 2017, 3:09 PM
 */

#ifndef DS1307_H
#define	DS1307_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    
#ifdef	__cplusplus
}
#endif

unsigned short read_ds1307(unsigned short address);
void write_ds1307(unsigned short address,unsigned short w_data);
unsigned char BCD2UpperCh(unsigned char bcd);
unsigned char BCD2LowerCh(unsigned char bcd);
int Binary2BCD(int a);
int BCD2Binary(int a);

#endif	/* DS1307_H */

