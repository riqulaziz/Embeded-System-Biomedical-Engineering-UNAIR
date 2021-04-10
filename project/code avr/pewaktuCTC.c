/*
 * pewaktuCTC.c
 *
 * Created: 5/5/2020 11:00:55 PM
 * Author: Thoriqul Aziz
 */

#include <io.h>
#include <alcd.h>
#include <stdlib.h>

unsigned char lup=0;
unsigned char temp[6];
int waktu;
interrupt [TIM0_OVF] void_timer0_ovf_isr(void)
{
    TCNT0=0x69;
    lup++;
    if (lup>=100) {
    waktu++;
    lup=0;
    };

}
void main(void)
{
TCCR0A=0x00;
TCCR0B=0x05;
TCNT0=0x4F;
OCR0A=0x4E;
OCR0B=0x00;
// OCR0A=0xF9;
TIMSK0=0x01;
//TIFR0=0x01;
#asm("sei")

lcd_init(16);
while (1)
    {
 
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

