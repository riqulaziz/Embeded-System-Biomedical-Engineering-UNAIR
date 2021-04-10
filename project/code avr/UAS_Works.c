#include <mega328p.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <alcd.h> // Alphanumeric LCD functions

// Global Variables
#define ADC_VREF_TYPE 0x40 // Voltage Ref: AVCC pin

// Fungsi MAP
long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// Fungsi ADC 
unsigned int read_adc(unsigned char adc_input)
{
    ADMUX = adc_input | ADC_VREF_TYPE;
    delay_us(10); // Delay 10 mikro sekon untuk stabilitas ADC
    ADCSRA|=(1<<ADSC); // Mulai konversi Analog ke Digital
    while ((ADCSRA & (1<<ADIF))==0); 
    ADCSRA|=(1<<ADIF);
    return ADCW; // Mengembalikan nilai Digital
}

void main(void)
{
int nilai_adc, speed, ton; 
float toff;
char text[16];

// Declare your local variables here
PORTC  = 0xFF;     // Pull Ups  (Untuk Button) 
PINC.2 = 0x00;     // Pull Down (Untuk Potensiometer)
DDRC   = 0x00;     // DDR 0 -> Input
PORTB  = 0x00;     // Inisialisasi Port B       
DDRB   = 0XFF;     // DDR 1 -> Output

// Crystal Oscillator division factor: 1
#pragma optsize-
CLKPR= 0x80; // System Clock Prescaler: 
CLKPR= 0x00; 
#ifdef _OPTIMIZE_SIZE_
#pragma optsize+
#endif

ACSR  = (1<<ACD) | (0<<ACBG) | (0<<ACO) | (0<<ACI) | (0<<ACIE) | (0<<ACIC) | (0<<ACIS1) | (0<<ACIS0);
DIDR1 = (0<<AIN0D) | (0<<AIN1D);
DIDR0 = (0<<ADC5D) | (0<<ADC4D) | (0<<ADC3D) | (0<<ADC2D) | (0<<ADC1D) | (0<<ADC0D);
ADMUX = ADC_VREF_TYPE;
ADCSRA= (1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (1<<ADPS2) | (0<<ADPS1) | (1<<ADPS0);
ADCSRB= (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
SPCR  = 0x00; // SPI disabled
TWCR  = 0x00; // TWI disabled

lcd_init(16);
lcd_gotoxy(0,0);
lcd_putsf("------IDLE------");

while(1)
{    
    if(PINC.0 == 0) // btn 1 pressed --> CCW              
    {
        lcd_clear();             
        lcd_gotoxy(0,0);
        lcd_putsf("Kec. Putaran (%)");
        delay_ms(2); //debounce tombol
        while(PINC.0 == 0)
        {    
            nilai_adc = read_adc(2); // Baca Nilai Potensiometer
            speed = map(nilai_adc, 0, 1023, 0, 100); //Ubah nilai Analog -> Skala 100
            ton = map(nilai_adc, 0, 1023, 0, 50); //Ubah nilai Analog -> Skala 50
            toff= map(nilai_adc, 0, 1023, 3, 0); //Ubah nilai Analog -> Skala 3
            
            PORTB=0x02;       
            delay_ms(ton);  
            PORTB=0x00;
            delay_ms(toff);  
            
            itoa(speed,text); // Ubah nilai speed jadi string 
            lcd_gotoxy(0,1);
            lcd_puts(text);lcd_puts(" - ");lcd_puts("CCW");
        }
    }
    else if(PINC.1 == 0) // btn 2 pressed --> CW        
    {     
        lcd_clear();             
        lcd_gotoxy(0,0);
        lcd_putsf("Kec. Putaran (%)");
        delay_ms(2); //debounce tombol
        while(PINC.1 == 0)
        {
            nilai_adc = read_adc(2); // Baca Nilai Potensiometer
            speed = map(nilai_adc, 0, 1023, 0, 100); //Ubah nilai Analog -> Skala 100
            ton = map(nilai_adc, 0, 1023, 0, 50); //Ubah nilai Analog -> Skala 50
            toff= map(nilai_adc, 0, 1023, 3, 0); //Ubah nilai Analog -> Skala 3
            
            PORTB=0x01;       
            delay_ms(ton);  
            PORTB=0x00;
            delay_ms(toff);  
            
            itoa(speed,text); // Ubah nilai speed jadi string 
            lcd_gotoxy(0,1);
            lcd_puts(text);lcd_puts(" - ");lcd_puts("CW");
        }     
    }
    else // no btn pressed --> IDLE 
    {   
        PORTB=0x00;               
    }                        
}
}
