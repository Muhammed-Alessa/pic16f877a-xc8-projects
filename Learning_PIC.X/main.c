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

    TRISBbits.TRISB0=0; //set LED pin as output
    TRISBbits.TRISB1=1; //set Button as input

   
    for (;;) {
        
        if (PORTBbits.RB1) {
            PORTBbits.RB0=1;
        } else {               
            PORTBbits.RB0=0;
        }
    
    }
    
    return;
}
