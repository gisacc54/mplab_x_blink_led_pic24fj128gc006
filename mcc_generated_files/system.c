/**
  @Generated PIC24 / dsPIC33 / PIC32MM MCUs Source File

  @Company:
    Microchip Technology Inc.

  @File Name:
    system.h

  @Summary:
    This is the sysetm.h file generated using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.167.0
        Device            :  PIC24FJ128GC006
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.50
        MPLAB             :  MPLAB X v5.35
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

// Configuration bits: selected in the GUI

// CONFIG4
#pragma config DSWDTPS = DSWDTPS1F    //Deep Sleep Watchdog Timer Postscale Select bits->1:68719476736 (25.7 Days)
#pragma config DSWDTOSC = LPRC    //DSWDT Reference Clock Select->DSWDT uses LPRC as reference clock
#pragma config DSBOREN = ON    //Deep Sleep BOR Enable bit->DSBOR Enabled
#pragma config DSWDTEN = ON    //Deep Sleep Watchdog Timer Enable->DSWDT Enabled
#pragma config DSSWEN = ON    //DSEN Bit Enable->Deep Sleep is controlled by the register bit DSEN
#pragma config RTCBAT = ON    //RTC Battery Operation Enable->RTC operation is continued through VBAT
#pragma config PLLDIV = DIS    //PLL Input Prescaler Select bits->PLL is disabled
#pragma config I2C2SEL = SEC    //Alternate I2C2 Location Select bit->I2C2 is multiplexed to SDA2/RF4 and SCL2/RF5
#pragma config IOL1WAY = ON    //PPS IOLOCK Set Only Once Enable bit->Once set, the IOLOCK bit cannot be cleared

// CONFIG3
#pragma config WPFP = WPFP127    //Write Protection Flash Page Segment Boundary->Page 127 (0x1FC00)
#pragma config SOSCSEL = OFF    //SOSC Selection bits->Digital (SCLKI) mode
#pragma config WDTWIN = PS25_0    //Window Mode Watchdog Timer Window Width Select->Watch Dog Timer Window Width is 25 percent
#pragma config BOREN = ON    //Brown-out Reset Enable->Brown-out Reset Enable
#pragma config WPDIS = WPDIS    //Segment Write Protection Disable->Disabled
#pragma config WPCFG = WPCFGDIS    //Write Protect Configuration Page Select->Disabled
#pragma config WPEND = WPENDMEM    //Segment Write Protection End Page Select->Write Protect from WPFP to the last page of memory

// CONFIG2
#pragma config POSCMD = NONE    //Primary Oscillator Select->Primary Oscillator Disabled
#pragma config WDTCLK = LPRC    //WDT Clock Source Select bits->WDT uses LPRC
#pragma config OSCIOFCN = OFF    //OSCO Pin Configuration->OSCO/CLKO/RC15 functions as CLKO (FOSC/2)
#pragma config FCKSM = CSDCMD    //Clock Switching and Fail-Safe Clock Monitor Configuration bits->Clock switching and Fail-Safe Clock Monitor are disabled
#pragma config FNOSC = FRCDIV    //Initial Oscillator Select->Fast RC Oscillator with Postscaler (FRCDIV)
#pragma config ALTADREF = AVREF_RB    //External 12-Bit A/D Reference Location Select bit->AVREF+/AVREF- are mapped to RB0/RB1
#pragma config ALTCVREF = CVREF_RB    //External Comparator Reference Location Select bit->CVREF+/CVREF- are mapped to RB0/RB1
#pragma config WDTCMX = WDTCLK    //WDT Clock Source Select bits->WDT clock source is determined by the WDTCLK Configuration bits
#pragma config IESO = OFF    //Internal External Switchover->Disabled

// CONFIG1
#pragma config WDTPS = PS32768    //Watchdog Timer Postscaler Select->1:32768
#pragma config FWPSA = PR128    //WDT Prescaler Ratio Select->1:128
#pragma config WINDIS = OFF    //Windowed WDT Disable->Standard Watchdog Timer
#pragma config FWDTEN = WDT_DIS    //Watchdog Timer Enable->WDT disabled in hardware; SWDTEN bit disabled
#pragma config ICS = PGx1    //Emulator Pin Placement Select bits->Emulator functions are shared with PGEC1/PGED1
#pragma config LPCFG = OFF    //Low power regulator control->Disabled - regardless of RETEN
#pragma config GWRP = OFF    //General Segment Write Protect->Disabled
#pragma config GCP = OFF    //General Segment Code Protect->Code protection is disabled
#pragma config JTAGEN = OFF    //JTAG Port Enable->Disabled

#include "pin_manager.h"
#include "clock.h"
#include "system.h"
#include "interrupt_manager.h"
#include "traps.h"

void SYSTEM_Initialize(void)
{
    PIN_MANAGER_Initialize();
    CLOCK_Initialize();
    INTERRUPT_Initialize();
}

/**
 End of File
*/