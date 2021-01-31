#define FCY 16000000UL 
#include <assert.h>
#include <stdbool.h>
#include "mcc_generated_files/system.h"
#include <stdio.h>
#include <stdlib.h>
#include <libpic30.h>
#include <xc.h>
#include <string.h>
#include "mcc_generated_files/i2c1.h"
#include "mcp9808.h"

#if defined(__dsPIC33E__)
	#include <p33exxxx.h>
#elif defined(__dsPIC33F__)
	#include <p33fxxxx.h>
#elif defined(__dsPIC30F__)
	#include <p30fxxxx.h>
#elif defined(__PIC24E__)
	#include <p24exxxx.h>
#elif defined(__PIC24H__)
	#include <p24hxxxx.h>
#elif defined(__PIC24F__) || defined(__PIC24FK__)
	#include <p24fxxxx.h>
#endif


/*
                         Main application
 */
int main(void){                                 // "main"

    SYSTEM_Initialize();                        // ruft "SYSTEM_Initialize" auf
    MCP9808_Init();                             // ruft "MCP9808_Init" auf
    
    float temperatur;                           // definiert "temperatur"
    
    while (1){                                  // Endloschleife
        temperatur = MCP9808_GetValue();        // schreibt ergebnis von "MCP9808_GetValue" in "temperatur"
        printf("Temp = %.2fC\r\n",temperatur);  // schreibt "Temp = %.2fC\r\n" an UART           
        __delay_ms(500);                        // warte 500ms
    }                                           // 
}                                               // 

