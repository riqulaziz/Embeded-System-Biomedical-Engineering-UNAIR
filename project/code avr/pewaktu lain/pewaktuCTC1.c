/*
 * pewaktuCTC1.c
 *
 * Created: 5/6/2020 12:03:40 AM
 * Author: Thoriqul Aziz
 */

#include <io.h>
#include <alcd.h>
#include <stdlib.h>

unsigned char lup=0;
unsigned char temp[6];
int waktu;

void main(void)
{
lcd_init(16);

while (1)
    {
    TCCR0A=0x02;
    TCCR0B=0x05;
    TCNT0=0x00;
    TIMSK0=0x01;
    OCR0A=0x9B;
    
    while (TIFR0 & (0x01)>0)
{
    lup++;
    if(lup==10)
    {
        waktu++;
        lup=0;
    }
    
}
    TIFR0=0x01;
    if(waktu==60)
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

