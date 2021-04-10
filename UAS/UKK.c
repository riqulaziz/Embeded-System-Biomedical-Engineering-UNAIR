#include <mega8535.h>
#include <delay.h>
int stat = 0;
void fer(int a,int b,int c){
     PORTD.4 = a;
     PORTD.5 = b;
     delay_ms(c);
}
void main(void)
{
PORTB=255; //Buat Setting PORT Input
DDRD=255;  //Buat Setting PORT Output
while (1)
      {
           if(PINB.0 == 0){
             stat = 1;
           }
           if(PINB.1 == 0){
             stat = 2;
           }
           if(PINB.2 == 0){
           stat = 0;
             fer(0,1,3000);
             fer(0,0,3000);
             fer(1,0,3000);
           }
           if(stat ==1){
             fer(0,1,1);
             fer(0,0,1);
           }
           if(stat ==2){           
             fer(1,0,1);
             fer(0,0,1);
             }
      }
}
