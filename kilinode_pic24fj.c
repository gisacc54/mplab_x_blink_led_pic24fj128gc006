   /* *****************************************************************************
   KiliNode Software Development
   This file contains various functions and macros for PIC24FJ128GC006
   in KiliNode hardware.
   The functions are used as a basic configurations for the MCU.
   Created by: Haji fimbombaya.
   Date Created: 24/08/2018
   Date modified:24/08/2018

   KiliNode Backview pins configuration:

                            **** Antenna Port J1
                            ****
            **********************************
            J2                              J3
            **                              **
        GND #20                            20# GND
        VCC #19                            19# VCC
        GND #18          KiliNode          18# GND
 P43 |  RD9 #17          BACK VIEW         17# P61 | RE1
 P42 |  RD8 #16                            16# P62 | RE2
 P40 | RC15 #15                            15# P63 | RE3
 P39 | RC12 #14                            14# P64 | RE4
       VBUS #13                            13# P1  | RE5
         D+ #12                            12# VCC
         D- #11                            11# P2  | RE6
        GND #10                            10# GND
 P30 | RB15 #9                              9# P3  | RE7
 P33 |  RF3 #8                              8# VCC
 P29 | RB14 #7                              7# P4  | RG6
 P32 |  RF5 #6                              6# GND
 P28 | RB13 #5                              5# P5  | RG7
 P31 |  RF4 #4                              4# GND
        GND #3                              3# GND
        VCC #2                              2# VCC
        GND #1                              1# GND
            **         123456789AB          **
            **     J1  ###########          **
            **********************************

               J1
               **
         MCLR  #1
       V_ICSP  #2
          GND  #3
        PGED2  #4
        PGEC2  #5
          NIL  #6
          NIL  #7
     VStorage  #8
          GND  #9
          GND  #A=10
      VSPanel  #B=11
               **


   This file contains the following functions:
   - PPS_Config()
   - OP_AMP()
   - sd_adc()
***************************************************************************** */

  #include <stdint.h>
  #include "kilinode_pic24fj.h"
  
// ***************** PERIPHERAL PINS MAPPING CONFIGURATION *********************
void PPS_Config(){
 // PERIPHERAL PIN SELECT (PPS) CONFIGURATION
    //SPI1 interfaced to CC2520 tranceiver
 Unlock_IOLOCK();
     PPS_Mapping(22, _INPUT, _SDI1);              // Sets pin RP22 to  DATA Input
     PPS_Mapping(23, _OUTPUT, _SDO1);             // Sets pin RP23 to DATA Ouput
     PPS_Mapping(25, _OUTPUT, _SCK1OUT);          // Sets pin RP25 to SPI1 CLK Output
  PPS_Mapping(25, _INPUT, _SCK1IN);

 Lock_IOLOCK();
}
// ******************************** END ****************************************
// *****************************************************************************

 // *************************** PUBLIC FUNCTIONS *******************************
// Data receiving macros
   uint8_t KiliNode_spiRxTx(uint8_t x)
     {
      uint8_t recData;
           if (SPI1CON1bits.MODE16)          /* word write */
              SPI1BUF = x;
           else
               SPI1BUF = x & 0xff;    /*  byte write  */
           while(SPI1STATbits.SPITBF);        // Check for transmit flag
             recData = SPI1BUF;               // Avoiding overflow when reading
                 while(SPI1STATbits.SPIRBF);  // check for receive buffer
             return recData;
          /*
           SPI1_write(x);
           return SPI1_read();
           */
     }

 /*
// -----------------------------------------------------------------------------
// KiliNode Software Development
// operational Amplifier
// This program aplifies the input analog signal and put to the ADC
// Created by H. S. Fimbombaya
// Created 01/06/2018
// Last time modified 08/06/2018
// -----------------------------------------------------------------------------
// ******************** OP-AMP 1 INITIALIZATION FUNCTION ***********************
void OP_AMP1_Init(){
//Op Amp 1 Initialization and Operation
 AMP1CONbits.AMPSIDL = 0;               //Continue operation in Idle mode
 AMP1CONbits.AMPSLP  = 0;               //Discontinue operation in Sleep mode
 AMP1CONbits.CMPSEL  = 0;               //Op Amp mode
 AMP1CONbits.SPDSEL  = 1;               //High power/high speed operation
 AMP1CONbits.AMPOE   = 1;               //Amplifier output is sent to a pin (amplifier output is not enabled)
 AMP1CONbits.NINSEL  = 2;               //Input negative(inverting) channel
 AMP1CONbits.PINSEL  = 2;               //Input positive(non-inverting) channel
 AMP1CONbits.AMPEN   = 1;               //enabler amplifier operation
//asm volatile("repeat #40"); //Delay 10us
//Nop();
}
//************************** OP-AMP1 READ FUNCTION *****************************
void OP_AMP1_Read(unsigned short opAmpCH_N,unsigned short opAmpCH_P){
 AMP1CONbits.NINSEL = opAmpCH_N;        //Input negative(inverting) channel
 AMP1CONbits.PINSEL = opAmpCH_P;        //Input positive(non-inverting) channel
}
// ******************************** END ****************************************
// -----------------------------------------------------------------------------
// KiliNode Software Development
// Sigma Delta ADC1
// This program perfoms Analog to digital conversion using 16-bit sigma delta ADC
// Created by H. S. Fimbombaya
// Created 01/06/2018
// Last time modified 08/06/2018
// -----------------------------------------------------------------------------
// This is fixed point location
#define FIXED_POINT_POS 15
unsigned char count;
signed long int offset;
signed long int maxValue;
signed long int expectedMaxValue;
signed long int gain;
signed long int channelValue;
signed int calibratedResult;

//************************************************************************
//adc initialization
void SD1_ADC_Init(){                   //sd_adc1 function call
// ADC initialization.
SD1CON1bits.PWRLVL = 0;         // Low power, normal bandwidth
SD1CON1bits.SDREFP = 0;         // Positive Voltage Reference is SVDD
SD1CON1bits.SDREFN = 0;         // Negative Voltage Reference is SVSS
SD1CON1bits.VOSCAL = 1;         // Internal Offset Measurement Enable
SD1CON1bits.DITHER = 1;         // Low Dither
SD1CON1bits.SDGAIN = 0;         // Gain is 1:1
SD1CON2bits.RNDRES = 2;         // Round result to 16-bit
SD1CON2bits.SDWM = 1;           // SDxRESH/SDxRESL updated on every Interrupt
SD1CON2bits.SDINT = 3;          // Interrupt on every data output
SD1CON2bits.CHOP = 3;           // Chopping should be enabled
SD1CON3bits.SDCH = 0;           // Channel 0 (see the specific device data sheet)
SD1CON3bits.SDCS = 1;           // Clock Source is a 8 MHz FRC
SD1CON3bits.SDOSR = 0;          // Oversampling Ratio (OSR) is 1024 (best quality)
SD1CON3bits.SDDIV = 1;          // Input Clock Divider is 2 (SD ADC clock is 4MHz)
 }
//******************************************************************************
// START SENSOR: i=1, STOP SENSOR: i=0
 void SD1_ADC_Start(unsigned short i){
// Enable ADC
SD1CON1bits.SDON = 1;

// Wait for a minimum of five interrupts to be generated. Need to throw at least
// the first four away when using interrupt every period option, since the
// low pass SINC filter needs to be flushed with new data when we change
// ADC channel or initialize the ADC.
for(count=0; count<8; count++)
{
//Clear interrupt flag.
IFS6bits.SDA1IF = 0;
//Wait for the result ready.
while(IFS6bits.SDA1IF == 0);
}
// Save the initial VOSCAL offset value from the ADC.
// This value will be used to correct the offset error for all
// subsequent ADC measurements.
offset = (signed short int)SD1RESH;
// Configure ADC for normal operation.
SD1CON1bits.VOSCAL = 0;

// Measures the reference selected by SDREFP/SDREFN
// (see the specific device data sheet).
SD1CON3bits.SDCH = 0;
// Wait for a minimum of five interrupts to be generated.
for(count=0; count<8; count++)
{
//Clear interrupt flag.
IFS6bits.SDA1IF = 0;
//Wait for the result ready.
while(IFS6bits.SDA1IF == 0);
}
// Save the maximum value to calculate the gain.
maxValue = (signed short int)SD1RESH;
// Correct offset.
maxValue -= offset;
// Calculate gain.
expectedMaxValue = ((signed long int)32767)<<FIXED_POINT_POS;
gain = expectedMaxValue/maxValue;
}

//**************************************************************************
// SCAN FOR SENSOR READING
int SD1_ADC_Read(unsigned short CHANNEL){
// Select channel #0 for the measurement.
// (see the specific device data sheet).
SD1CON3bits.SDCH = CHANNEL;
// Adjust loop end value for desired settling time (value must be >= 5).
for(count=0; count<8; count++)
{
// Clear interrupt flag.
IFS6bits.SDA1IF = 0;
// Wait for the result ready.
while(IFS6bits.SDA1IF == 0);
}
// Not corrected channel #0 result.
channelValue = (signed short int)SD1RESH;
// Correct offset.
channelValue -= offset;
// Correct gain.
channelValue = gain*channelValue;
// 16-bit signed result
calibratedResult = channelValue>>FIXED_POINT_POS;
return   calibratedResult;

}
// ********************************** END *************************************

*/