/*
 * PewaktuTimer1.c
 *
 * Created: 5/6/2020 2:28:26 AM
 * Author: Thoriqul Aziz
 */

#include <io.h>
#include <alcd.h>
#include <stdlib.h>


unsigned char temp[6];
int waktu;
interrupt [TIM1_OVF] void timer1_ovf_isr(void) { 
TCNT1H=0xC2F7 >> 8; 
TCNT1L=0xC2F7 & 0xff;
waktu++;
}

void main(void)
{
TCCR1A=0x00; 
TCCR1B=0x05; 
TCNT1H=0xC2; 
TCNT1L=0xF7; 
ICR1H=0x00; 
ICR1L=0x00; 
OCR1AH=0x00; 
OCR1AL=0x00; 
OCR1BH=0x00; 
OCR1BL=0x00;

TIMSK1=0x01;
lcd_init(16);
#asm("sei")
while (1)
    {
    if(waktu==100)
        {
        lcd_clear();
        waktu=0;
        };
        
    lcd_gotoxy(0,0);
    lcd_putsf("Waktu : ");
    itoa(waktu,temp);
    lcd_gotoxy(0,1);
    lcd_puts(temp);
    }
    
}
