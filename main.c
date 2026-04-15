#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

// Configuration settings
#pragma config FOSC = XT        // Oscillator Selection (LP Oscillator, Low-power crystal connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer off
#pragma config PWRTE = OFF      // Power-up Timer off
#pragma config MCLRE = ON       // MCLR Pin Enabled
#pragma config CP = OFF         // Code Protection off
#pragma config CPD = OFF        // Data Code Protection off
#pragma config BOREN = OFF      // Brown-out Reset Disabled
#pragma config CLKOUTEN = OFF   // Clock Out disabled
#pragma config IESO = OFF       // Internal/External Switchover mode off
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor off

#define _XTAL_FREQ 8000000 // Define the crystal frequency

void LCD_setup(void);
void timer1(void);
void displaySegment(int integer1, int integer2, int integer3);
void displaySegment2(int integer2, int integer3, int integer4);


void main() {
    // Configure LCD segment pins as output
    //TRISA0 = 0; // Set RA0 as output
    //RA0 = 0; 
    // Initialize Timer1 and interrupts
    timer1();
    LCD_setup();
    
    //displaySegment(0, 0, 0); // Display the digit 0 at first
    
    //LCDDATA0 = 0xF9;
	//LCDDATA3 = 0xF9;
	//LCDDATA6 = 0xF9;
	//LCDDATA9 = 0xF9;
    
    while(1) {
        //LCDDATA0 = LCDDATA0 ^ 0x40;
        //__delay_ms(1000);
    }
}
void LCD_setup() {
    LCDSE0 = 0xF9; // Enable SEG0 to SEG7 except SEG1,2 because they use RA6 and RA7 OSC pins
    LCDSE1 = 0x0F; //Enable SEG0 to SEG1
    //LCDDATA0 = 0xF9;
    LCDDATA0 = 0x00;
    LCDDATA1 = 0x00;
    LCDDATA3 = 0x00;
    LCDDATA4 = 0x00;
    LCDDATA6 = 0x00;
    LCDDATA7 = 0x00;
    LCDDATA9 = 0x00;
    LCDDATA10 = 0x00;
    
    LCDPS = 0x33; //1:2 Prescaler, Writing allowed, LCD active, 1/2 Bias mode, Type-A waveform
    LCDCON = 0xC7; //LCD Driver enable, LCD in Sleep mode enable, LCD error disabled, Clock T1OSC, COM1/2
    LCDREF = 0xA0; //LCD contrast is powered by VDD, internal LCD ref. enabled
            
    LCDCST = 0x00; //set the contrast (does not really change anything)
    LCDRL = 0xF0; //Medium power mode for type A and B waveforms, no mode switching   
    
    //LCDPS = 0x32; //1:3 Prescaler, Writing allowed, LCD active, Static mode, Type-A waveform
    //LCDCON = 0xC4; //LCD Driver enable, LCD in Sleep mode enable, LCD error disabled, Clock T1OSC, Static COM0
    //LCDREF = 0x80;
            
    //LCDCST = 0x07; //set min contrast
    //LCDRL = 0xA0; //Medium power mode for type A and B waveforms, no mode switching   
}
// Define arrays to store values of LCDDATA registers
unsigned char LCDDATA_array[11]; // Assuming LCDDATA0, LCDDATA1, LCDDATA2, LCDDATA3, LCDDATA4

void displaySegment(int integer1, int integer2, int integer3) {
    uint8_t lcdData0 = 0;
    uint8_t lcdData3 = 0;
    uint8_t lcdData6 = 0;
    uint8_t lcdData9 = 0;
    
    uint8_t lcdData0_2 = 0;
    uint8_t lcdData3_2 = 0;
    uint8_t lcdData6_2 = 0;
    uint8_t lcdData9_2 = 0;
    
    uint8_t lcdData0_3 = 0;
    uint8_t lcdData3_3 = 0;
    uint8_t lcdData6_3 = 0;
    uint8_t lcdData9_3 = 0;  

    switch (integer1) {
        case 0: //abcdef
            lcdData0 = 0b01000000;
            lcdData3 = 0b11000000;
            lcdData6 = 0b10000000;
            lcdData9 = 0b11000000;
            break;
        case 1: //bc
            lcdData0 = 0b00000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b10000000;
            lcdData9 = 0b00000000;
            break;
        case 2: //abdeg
            lcdData0 = 0b01000000;
            lcdData3 = 0b01000000;
            lcdData6 = 0b11000000;
            lcdData9 = 0b10000000;
            break;
        case 3: //abcdg
            lcdData0 = 0b01000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b11000000;
            lcdData9 = 0b10000000;
            break;
        case 4: //bcfg
            lcdData0 = 0b00000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b11000000;
            lcdData9 = 0b01000000;
            break;
        case 5: //acdfg
            lcdData0 = 0b01000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b01000000;
            lcdData9 = 0b11000000;
            break;
        case 6: //acdefg
            lcdData0 = 0b01000000;
            lcdData3 = 0b11000000;
            lcdData6 = 0b01000000;
            lcdData9 = 0b11000000;
            break;
        case 7: //abc
            lcdData0 = 0b00000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b10000000;
            lcdData9 = 0b10000000;
            break;
        case 8: //abcdefg
            lcdData0 = 0b01000000;
            lcdData3 = 0b11000000;
            lcdData6 = 0b11000000;
            lcdData9 = 0b11000000;
            break;
        case 9: //abcdfg
            lcdData0 = 0b01000000;
            lcdData3 = 0b10000000;
            lcdData6 = 0b11000000;
            lcdData9 = 0b11000000;
            break;
        default:
            return;
    }

    switch (integer2) {
        case 0: //abcdef
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00110000;
            lcdData6_2 = 0b00100000;
            lcdData9_2 = 0b00110000;
            break;
        case 1: //bc
            lcdData0_2 = 0b00000000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00100000;
            lcdData9_2 = 0b00000000;
            break;
        case 2: //abdeg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00010000;
            lcdData6_2 = 0b00110000;
            lcdData9_2 = 0b00100000;
            break;
        case 3: //abcdg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00110000;
            lcdData9_2 = 0b00100000;
            break;
        case 4: //bcfg
            lcdData0_2 = 0b00000000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00110000;
            lcdData9_2 = 0b00010000;
            break;
        case 5: //acdfg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00010000;
            lcdData9_2 = 0b00110000;
            break;
        case 6: //acdefg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00110000;
            lcdData6_2 = 0b00010000;
            lcdData9_2 = 0b00110000;
            break;
        case 7: //abc
            lcdData0_2 = 0b00000000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00100000;
            lcdData9_2 = 0b00100000;
            break;
        case 8: //abcdefg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00110000;
            lcdData6_2 = 0b00110000;
            lcdData9_2 = 0b00110000;
            break;
        case 9: //abcdfg
            lcdData0_2 = 0b00010000;
            lcdData3_2 = 0b00100000;
            lcdData6_2 = 0b00110000;
            lcdData9_2 = 0b00110000;
            break;
        default:
            return;
    }

    switch (integer3) {
        case 0: //abcdef
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001001;
            lcdData6_3 = 0b00001000;
            lcdData9_3 = 0b00001001;
            break;
        case 1: //bc
            lcdData0_3 = 0b00000000;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00001000;
            lcdData9_3 = 0b00000000;
            break;
        case 2: //abdeg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00000001;
            lcdData6_3 = 0b00001001;
            lcdData9_3 = 0b00001000;
            break;
        case 3: //abcdg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00001001;
            lcdData9_3 = 0b00001000;
            break;
        case 4: //bcfg
            lcdData0_3 = 0b00000000;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00001001;
            lcdData9_3 = 0b00000001;
            break;
        case 5: //acdfg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00000001;
            lcdData9_3 = 0b00001001;
            break;
        case 6: //acdefg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001001;
            lcdData6_3 = 0b00000001;
            lcdData9_3 = 0b00001001;
            break;
        case 7: //abc
            lcdData0_3 = 0b00000000;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00001000;
            lcdData9_3 = 0b00001000;
            break;
        case 8: //abcdefg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001001;
            lcdData6_3 = 0b00001001;
            lcdData9_3 = 0b00001001;
            break;
        case 9: //abcdfg
            lcdData0_3 = 0b00000001;
            lcdData3_3 = 0b00001000;
            lcdData6_3 = 0b00001001;
            lcdData9_3 = 0b00001001;
            break;
        default:
            return;
    }

    LCDDATA0 = lcdData0 | lcdData0_2 | lcdData0_3;
    LCDDATA3 = lcdData3 | lcdData3_2 | lcdData3_3;
    LCDDATA6 = lcdData6 | lcdData6_2 | lcdData6_3;
    LCDDATA9 = lcdData9 | lcdData9_2 | lcdData9_3;
}

void displaySegment2(int integer2, int integer3, int integer4) {
    uint8_t lcdData0 = 0;
    uint8_t lcdData3 = 0;
    uint8_t lcdData6 = 0;
    uint8_t lcdData9 = 0;

    uint8_t lcdData0_2 = 0;
    uint8_t lcdData3_2 = 0;
    uint8_t lcdData6_2 = 0;
    uint8_t lcdData9_2 = 0;

    uint8_t lcdData9_3 = 0;

    switch (integer2) {
        case 0: //abcdef
            lcdData0 = 0b00001100;
            lcdData3 = 0b00000100;
            lcdData6 = 0b00001100;
            lcdData9 = 0b00000100;
            break;
        case 1: //bc
            lcdData0 = 0b00000000;
            lcdData3 = 0b00000100;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000000;
            break;
        case 2: //abdeg
            lcdData0 = 0b00000100;
            lcdData3 = 0b00001100;
            lcdData6 = 0b00001000;
            lcdData9 = 0b00000100;
            break;
        case 3: //abcdg
            lcdData0 = 0b00000100;
            lcdData3 = 0b00001100;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000100;
            break;
        case 4: //bcfg
            lcdData0 = 0b00001000;
            lcdData3 = 0b00001100;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000000;
            break;
        case 5: //acdfg
            lcdData0 = 0b00001100;
            lcdData3 = 0b00001000;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000100;
            break;
        case 6: //acdefg
            lcdData0 = 0b00001100;
            lcdData3 = 0b00001000;
            lcdData6 = 0b00001100;
            lcdData9 = 0b00000100;
            break;
        case 7: //abc
            lcdData0 = 0b00000100;
            lcdData3 = 0b00000100;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000000;
            break;
        case 8: //abcdefg
            lcdData0 = 0b00001100;
            lcdData3 = 0b00001100;
            lcdData6 = 0b00001100;
            lcdData9 = 0b00000100;
            break;
        case 9: //abcdfg
            lcdData0 = 0b00001100;
            lcdData3 = 0b00001100;
            lcdData6 = 0b00000100;
            lcdData9 = 0b00000100;
            break;
        default:
            return;
    }

    switch (integer3) {
        case 0: //abcdef
            lcdData0_2 = 0b00000011;
            lcdData3_2 = 0b00000001;
            lcdData6_2 = 0b00000011;
            lcdData9_2 = 0b00000001;
            break;
        case 1: //bc
            lcdData0_2 = 0b00000000;
            lcdData3_2 = 0b00000001;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000000;
            break;
        case 2: //abdeg
            lcdData0_2 = 0b00000001;
            lcdData3_2 = 0b00000011;
            lcdData6_2 = 0b00000010;
            lcdData9_2 = 0b00000001;
            break;
        case 3: //abcdg
            lcdData0_2 = 0b00000001;
            lcdData3_2 = 0b00000011;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000001;
            break;
        case 4: //bcfg
            lcdData0_2 = 0b00000010;
            lcdData3_2 = 0b00000011;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000000;
            break;
        case 5: //acdfg
            lcdData0_2 = 0b00000011;
            lcdData3_2 = 0b00000010;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000001;
            break;
        case 6: //acdefg
            lcdData0_2 = 0b00000011;
            lcdData3_2 = 0b00000010;
            lcdData6_2 = 0b00000011;
            lcdData9_2 = 0b00000001;
            break;
        case 7: //abc
            lcdData0_2 = 0b00000001;
            lcdData3_2 = 0b00000001;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000000;
            break;
        case 8: //abcdefg
            lcdData0_2 = 0b00000011;
            lcdData3_2 = 0b00000011;
            lcdData6_2 = 0b00000011;
            lcdData9_2 = 0b00000001;
            break;
        case 9: //abcdfg
            lcdData0_2 = 0b00000011;
            lcdData3_2 = 0b00000011;
            lcdData6_2 = 0b00000001;
            lcdData9_2 = 0b00000001;
            break;
        default:
            return;
    }

    switch (integer4) {
        case 0: //no dot
            lcdData9_3 = 0b00000000;
            break;
        case 1: //dot present
            lcdData9_3 = 0b00000010;
            break;

        default:
            return;
    }

    LCDDATA1 = lcdData0 | lcdData0_2;
    LCDDATA4 = lcdData3 | lcdData3_2;
    LCDDATA7 = lcdData6 | lcdData6_2;
    LCDDATA10 = lcdData9 | lcdData9_2 | lcdData9_3;
}


void timer1() {
    // Timer1 configuration
    T1CONbits.TMR1CS = 0b10; // Timer1 Clock Source: External
    T1CONbits.T1OSCEN = 1;   // Timer1 Oscillator Enable for LP 32 kHz
    nT1SYNC = 0;    // Do not synchronize external clock input
    
    //T1CONbits.T1CKPS = 0b11; // 1:8 Prescaler
    
    // Enable Timer1 overflow interrupt
    PIE1bits.TMR1IE = 1; // Enable Timer1 overflow interrupt
    INTCONbits.PEIE = 1; // Enable peripheral interrupts
    INTCONbits.GIE = 1;  // Enable global interrupts
    
    // Timer1 preload for overflow interrupt
    TMR1H = 0x80; // Preload Timer1 high byte
    TMR1L = 0x00; // Preload Timer1 low byte
    
    // Enable Timer1
    T1CONbits.TMR1ON = 1; // Enable Timer1
}

void __interrupt() isr(void) {
    if (PIR1bits.TMR1IF) { // Check if Timer1 overflow interrupt flag is set
        PIR1bits.TMR1IF = 0; // Clear Timer1 overflow interrupt flag
        //LCDDATA0 ^= 0xF9; // Toggle LCD
        //LCDDATA1 ^= 0x03; //Toggle LCD 2
        //LATA0 ^= 1; // Toggle LED
        static int counter = 0;
        static int counter2 = 0;
        counter = counter + 1;
        if (counter == 10) {
            counter = 0; // Reset counter to 0 when it reaches 10
            counter2 = counter2 + 1;
            if (counter2 == 10) {
                counter2 = 0; // increasing count of the second display
            }
        }
        
        // Display the incremented counter value on the LCD
        displaySegment(counter, counter, counter); // Display the digit
        displaySegment2(counter, counter, 0);
        if (counter %2 == 1){
            //LCDDATA0 = LCDDATA0 ^ 0x40; //blinking the dot segment
            //LCDDATA6 = LCDDATA6 ^ 0x40; //blinking the dot segment
            displaySegment2(counter, counter, 1);
        }
        else {
            //LCDDATA3 = LCDDATA3 ^ 0x40; // blinking the other dot segment
            displaySegment2(counter, counter, 0);
        }
        // Preload Timer1 for next overflow interrupt
        TMR1H = 0x80; // Preload Timer1 high byte
        TMR1L = 0x00; // Preload Timer1 low byte
    }
}
