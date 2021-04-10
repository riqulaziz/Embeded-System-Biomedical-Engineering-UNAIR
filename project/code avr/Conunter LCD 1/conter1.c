/*
 * conter1.c
 *
 * Created: 5/7/2020 10:34:08 AM
 * Author: Thoriqul Aziz
 */

#include <io.h>
#include <alcd.h>
#include <stdlib.h>

int data;
unsigned char temp[6];
interrupt [TIM0_OVF] void timer0_int0_isr(void)
{
    TCNT0=0xFD;
    data++; 
}
void main(void)
{
PORTD=0x10;
DDRD=0x10;
TCCR0A=0x00;
TCCR0B=0x07;
TCNT0=0xFD;
OCR0A=0x00;
TIMSK0=0X01;
#asm("sei")
lcd_init(16);
while (1)
    {
    if (data>=256) { 
    lcd_clear(); 
    } 
    lcd_gotoxy(0,0); 
    lcd_putsf("timer"); 
    itoa(data,temp); //menampilkan di 
    lcd_gotoxy(0,1); 
    lcd_puts(temp);
    }
}
