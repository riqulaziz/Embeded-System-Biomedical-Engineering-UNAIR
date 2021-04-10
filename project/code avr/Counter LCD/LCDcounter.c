/*
 * LCDcounter.c
 *
 * Created: 5/7/2020 12:27:13 AM
 * Author: Thoriqul Aziz
 */

#include <io.h>
#include <alcd.h>
#include <stdlib.h>

unsigned char lup=0;
unsigned char temp[6];
unsigned char temp1[6];
int waktu,data;
//timer_init()
//{
//TCCR0A=0X00;
//TCCR0B=0X05;
//TCNT0=0X69;
//OCR0A=0X00;
//TIMSK0=0X00;
//lup++;
//    if (lup==100)
//    {
//        waktu++;
//        lup=0;
//    }
//}

interrupt [TIM0_OVF] void timer0_int0_isr(void)
{
    TCNT0=0xFE;
    data++; 
}

void main(void)
{
DDRB=0xff;
PORTB=0xff;
TCCR0A=0x00;
TCCR0B=0x07;
TCNT0=0xFE;
OCR0A=0x00;
TIMSK0=0X01;
#asm("sei")
//timer_init();
lcd_init(16);
while (1)
    {
    if (data>=100)
    {
    lcd_clear;
    }
    
//    
    lcd_gotoxy(0,0);
    lcd_putsf("Counter");
    itoa(data,temp1);
    lcd_gotoxy(0,1);
    lcd_puts(temp1);

    }
}
