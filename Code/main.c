#include <main.h>
#include "lcd.c"
#include "setup.c"
#define coi PIN_B5
#define hut PIN_B4
#define CB1 PIN_E1
#define CB2 PIN_E2
float x=0.5,t;
int16 value,adc;
#int_EXT
void  giam(void) 
{ 
  x=x-0.1;
  if(x<0.5) x=0.5;
}

#int_EXT1
void tang(void) 
{
  x=x+0.1;
  if(x>1) x=1;
}
void tien();
void lui();
void trai();
void phai();
void dung();
void dongco();
void hutbui();
void tudong();
void PWM();
void nhietdo();
void main()
{  
   setup();
   output_high(hut);
   output_low(coi);
   dung();
   lcd_putc("\fDO AN TOT NGHIEP"); delay_ms(1000);
   lcd_putc("\fSV THUC HIEN"); delay_ms(1000);
   lcd_putc("\fNGUYEN BA QUAN"); delay_ms(1000);
   lcd_putc("\fNGUYEN QUOC VU"); delay_ms(1000);
   lcd_putc("\fDINH DUC KHA"); delay_ms(1000);
   lcd_putc("\f");
   nhietdo(); delay_ms(500);
   printf(lcd_putc,"nhiet do:%2.1f",t); delay_ms(2000);
   
   while(TRUE)
   {   
       if(input(PIN_E0)==1) tudong();
       else
       { PWM();  
         printf(lcd_putc,"PWM:%2.1f",x); delay_ms(1000);
         dongco();
         lcd_putc("\f");
       }
       
   }
   
}
void hutbui()
{ 
  
  if(input(PIN_A5)==1) 
   {
     output_low(hut);
     lcd_putc("\f");
     lcd_putc("hut bui"); delay_ms(100);
   }
   else 
    {
      output_high(hut);
      lcd_putc("\f");
    }
}
void nhietdo()
{
    adc=read_adc(); delay_ms(500);
    t=adc*0.48828125; delay_ms(50);
}
void PWM()
{
   value=x*4*75;  /* duty cycle(x)= value/[4*(PR2+1)]  trong do duty la phan tram PWM
                                                       value la gia tri dua vao 
                                                       PR2 lay tu timer 2 ben tren */
   set_pwm1_duty(value);
}
void tien()
{
    output_d(0x0A);        //1010 tien
    lcd_putc("\f Robot tien"); 
}
void lui()
{
    output_d(0x05);       //0101 lui
    lcd_putc("\f Robot lui"); 
}
void trai()
{
    output_d(0x08);          //1000 trai
    lcd_putc("\f Re trai");
}
void phai()
{
    output_d(0x02);          //0010    phai      
    lcd_putc("\f Re phai");
}
void dung()
{
  output_d(0x00);
  lcd_putc("\f Robot dung");
}
void dongco()
{  if((input(CB1)==0)||(input(CB2)==1)) 
    { 
      dung();
      output_high(coi);  
      delay_ms(30);
      output_low(coi);
    }
    else output_low(coi);
   if(((input(PIN_A2)==1)&&input(CB1)==1&&input(CB2)==0))          
    { 
        tien(); delay_ms(100);
        hutbui(); delay_ms(10);
        
        
    }   
     else if(input(PIN_A4)==1)   
      { 
        lui();  delay_ms(100);
        hutbui(); delay_ms(10);
        
      }
     else if((input(PIN_A1)==1)&&input(CB1)==1&&input(CB2)==0)  
      { 
        trai();  delay_ms(100);
        hutbui(); delay_ms(10);
        
      }
     else if((input(PIN_A3)==1)&&input(CB1)==1&&input(CB2)==0)   
      { 
        phai(); delay_ms(100);
        hutbui(); delay_ms(10);
        
      }
     else 
      { dung();
        delay_ms(500);
      }
}

void tudong()
{
    while(input(CB1)==1&&input(CB2)==0)
     {  
       PWM();
       tien(); delay_ms(500);
       hutbui(); delay_ms(10);
      if(input(PIN_E0)==0)  break;
     }
       dung(); delay_ms(1000);
       hutbui();  delay_ms(10);
       PWM();
       lui();  delay_ms(1500);
       phai(); delay_ms(3500);
       while(input(CB1)==1&&input(CB2)==0)  /*khi chua co vat can va ho thi dieu kien
                                              trong while dung vat luon chay thang.
                                              khi 1 trong 2 dk sai thi thoat vong lap*/                                       
       {
         PWM();
         tien(); delay_ms(500);
         hutbui();
         if(input(PIN_E0)==0)  break;
       }  
       
       PWM();
       hutbui();
       dung(); delay_ms(1000);
       lui(); delay_ms(1500);
       trai(); delay_ms(3500);
       
}


