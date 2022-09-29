/*
 * File:   main.c
 * Author: Fatih Elibol
 *
 * Created on 26 Eylül 2022 Pazartesi, 07:46
 */
#pragma config FEXTOSC = OFF    // External Oscillator mode Selection bits->Oscillator not enabled
#pragma config RSTOSC = HFINTOSC_1MHZ    // Power-up default value for COSC bits->HFINTOSC with HFFRQ = 4 MHz and CDIV = 4:1

// CONFIG1H
#pragma config CLKOUTEN = OFF    // Clock Out Enable bit->CLKOUT function is disabled
#pragma config CSWEN = ON    // Clock Switch Enable bit->Writing to NOSC and NDIV is allowed
#pragma config FCMEN = ON    // Fail-Safe Clock Monitor Enable bit->Fail-Safe Clock Monitor enabled

// CONFIG2L
#pragma config MCLRE = EXTMCLR    // Master Clear Enable bit->MCLR pin (RE3) is MCLR
#pragma config PWRTE = OFF    // Power-up Timer Enable bit->Power up timer disabled
#pragma config LPBOREN = OFF    // Low-power BOR enable bit->Low power BOR is disabled
#pragma config BOREN = SBORDIS    // Brown-out Reset Enable bits->Brown-out Reset enabled , SBOREN bit is ignored

// CONFIG2H
#pragma config BORV = VBOR_190    // Brown Out Reset Voltage selection bits->Brown-out Reset Voltage (VBOR) set to 1.90V
#pragma config ZCD = OFF    // ZCD Disable bit->ZCD disabled. ZCD can be enabled by setting the ZCDSEN bit of ZCDCON
#pragma config PPS1WAY = ON    // PPSLOCK bit One-Way Set Enable bit->PPSLOCK bit can be cleared and set only once; PPS registers remain locked after one clear/set cycle
#pragma config STVREN = ON    // Stack Full/Underflow Reset Enable bit->Stack full/underflow will cause Reset
#pragma config XINST = OFF    // Extended Instruction Set Enable bit->Extended Instruction Set and Indexed Addressing Mode disabled

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31    // WDT Period Select bits->Divider ratio 1:65536; software control of WDTPS
#pragma config WDTE = OFF    // WDT operating mode->WDT Disabled

// CONFIG3H
#pragma config WDTCWS = WDTCWS_7    // WDT Window Select bits->window always open (100%); software control; keyed access not required
#pragma config WDTCCS = SC    // WDT input clock selector->Software Control

// CONFIG4L
#pragma config WRT0 = OFF    // Write Protection Block 0->Block 0 (000800-001FFFh) not write-protected
#pragma config WRT1 = OFF    // Write Protection Block 1->Block 1 (002000-003FFFh) not write-protected

// CONFIG4H
#pragma config WRTC = OFF    // Configuration Register Write Protection bit->Configuration registers (300000-30000Bh) not write-protected
#pragma config WRTB = OFF    // Boot Block Write Protection bit->Boot Block (000000-0007FFh) not write-protected
#pragma config WRTD = OFF    // Data EEPROM Write Protection bit->Data EEPROM not write-protected
#pragma config SCANE = ON    // Scanner Enable bit->Scanner module is available for use, SCANMD bit can control the module
#pragma config LVP = ON    // Low Voltage Programming Enable bit->Low voltage programming enabled. MCLR/VPP pin function is MCLR. MCLRE configuration bit is ignored

// CONFIG5L
#pragma config CP = OFF    // UserNVM Program Memory Code Protection bit->UserNVM code protection disabled
#pragma config CPD = OFF    // DataNVM Memory Code Protection bit->DataNVM code protection disabled

// CONFIG6L
#pragma config EBTR0 = OFF    // Table Read Protection Block 0->Block 0 (000800-001FFFh) not protected from table reads executed in other blocks
#pragma config EBTR1 = OFF    // Table Read Protection Block 1->Block 1 (002000-003FFFh) not protected from table reads executed in other blocks

// CONFIG6H
#pragma config EBTRB = OFF    // Boot Block Table Read Protection bit->Boot Block (000000-0007FFh) not protected from table reads executed in other blocks

#include"config.h"
#include"eusart1.h"

void OSCILLATOR_Initialize(void)
{
    // NOSC HFINTOSC; NDIV 1; 
    OSCCON1 = 0x60;
    // CSWHOLD may proceed; SOSCPWR Low power; 
    OSCCON3 = 0x00;
    // MFOEN disabled; LFOEN disabled; ADOEN disabled; SOSCEN disabled; EXTOEN disabled; HFOEN disabled; 
    OSCEN = 0x00;
    // HFFRQ 32_MHz; 
    OSCFRQ = 0x06;
    // TUN 0; 
    OSCTUNE = 0x00;
  
}

void UART_send_string(const char *str)
{
       
        if (UART_is_tx_ready())
        {
            while(*str)
            {
                UART_Write(*str++);
            }   
        }      
}

void main(void) {
    OSCILLATOR_Initialize();
    EUSART1_Initialize();
    
    uint8_t counter=0;
    TRISA6=0;
    while (1)
    { 
       
      LATA6 = 1;
      __delay_ms(500);
      printf("");
      LATA6 = 0;
      __delay_ms(500);
     
      counter++;
     
      if(counter == 3)
      {
          UART_send_string("BootloaderStart\n\r");
          __delay_ms(1000);
          asm("goto 0x1500");
          counter = 0;
      }
      
    }
    return;
}
