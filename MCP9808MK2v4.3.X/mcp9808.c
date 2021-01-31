#include <xc.h>
#include "mcc_generated_files/i2c1.h"
#include "mcp9808.h"

I2C1_MESSAGE_STATUS status;                                             // 

uint8_t Slave_Address = 0x18;                                           // definiert "Slave_Address" 
uint8_t Temp_Register = 0x05;                                           // definiert "Temp_Register" 

uint8_t  writeBuffer[3] = {0x00, 0x00, 0x00};                           // definiert "writeBuffer"
uint8_t  readBuffer[2] = {0x00, 0x00};                                  // definiert "readBuffer" 
uint16_t retryTimeOut1;                                                  // definiert "retryTimeOut1" 
uint16_t retryTimeOut2;                                                  // definiert "retryTimeOut2" 

void MCP9808_Init(void){                                                // "MCP9808_Init"
    writeBuffer[0] = 0x01;                                              // schreibt "0x01" in "writeBuffer[0]"
    writeBuffer[1] = 0x00;                                              // schreibt "0x00" in "writeBuffer[1]"
    I2C1_MasterWrite(&writeBuffer[0], 2, Slave_Address, &status);       // schreibt 2 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    
    writeBuffer[0] = 0x05;                                              // schreibt "0x05" in "writeBuffer[0]"
    I2C1_MasterWrite(&writeBuffer[0], 1, Slave_Address, &status);       // schreibt 1 Byte (writeBuffer[0]) an I2C1
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
}                                                                       // 

float MCP9808_GetValue(void){                                           // "MCP9808_GetValue"                                           
    float tempDataAnz;                                                  // definiert "tempDataAnz" 
    
    I2C1_MasterWrite(&Temp_Register, 1, Slave_Address, &status);        // schreibt 1 Byte (Temp_Register) an I2C1                      ???
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf 
    
    I2C1_MasterRead(&readBuffer[0], 2, Slave_Address, &status);         // liest von I2C1 in 2 Byte (readBuffer[0]) 
    i2c1_message_pending_100();                                         // ruft "i2c1_message_pending_100" auf
        
    if ((readBuffer[0] & 0x10) == 0x10){                                                // wenn "readBuffer[0]" maskiert mit "0x10" gleich "0x10" ist 
        tempDataAnz = (((readBuffer[0] & 0x0F) * 16) + (readBuffer[1] * 0.0625)) - 256; // temp < 0C
    }else{                                                                              // sonst
        tempDataAnz = ((readBuffer[0] & 0x0F) * 16) + (readBuffer[1] * 0.0625);         // temp > 0C      
    }                                                                                   // 
    return tempDataAnz;                                                                 // gibt "tempDataAnz" zurück     
}                                                                                       // 

void i2c1_message_pending_100(void){                                    // "i2c1_message_pending_100"
    retryTimeOut1 = 0;                                                  // setzt "retryTimeOut1" auf 0
    retryTimeOut2 = 0;                                                  // setzt "retryTimeOut2" auf 0
    while(status == I2C1_MESSAGE_PENDING){                              // solange "status" gleich "I2C1_MESSAGE_PENDING" ist
        if (retryTimeOut2 == 100){                                      // wenn "retryTimeOut2" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut2++;                                            // "retryTimeOut2" +1
        }                                                               // 
    }
    while(status != I2C1_MESSAGE_FAIL){                                 // solange "status" nicht gleich "I2C1_MESSAGE_FAIL" ist
        if (retryTimeOut1 == 100){                                      // wenn "retryTimeOut1" gleich 100 ist
            break;                                                      // Abbruch der Schleife
        }else{                                                          // sonst
            retryTimeOut1++;                                            // "retryTimeOut1" +1
        }                                                               // 
    }                                                                   // 
}                                                                       // 