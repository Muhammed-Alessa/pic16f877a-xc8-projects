/*
 * File:   main.c
 * Author: muhammedalessa
 *
 * Created on July 6, 2026, 1:57 PM
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void main(void) {

    TRISBbits.TRISB0=0; //set as output
    TRISBbits.TRISB1=0; //set as input
    TRISAbits.TRISA1=1;
   
    for (;;) {
        
        PORTBbits.RB0=1;
        __delay_ms(500);
        PORTBbits.RB0=0;
        __delay_ms(500);
    
    }
    
    return;
}
