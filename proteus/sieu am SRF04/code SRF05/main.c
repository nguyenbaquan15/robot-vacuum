#include <main.h>
#define LCD_ENABLE_PIN  PIN_C0                                    
#define LCD_RS_PIN      PIN_C3                                    
#define LCD_RW_PIN      PIN_C1                                    
#define LCD_DATA4       PIN_C4                                    
#define LCD_DATA5       PIN_C5                                    
#define LCD_DATA6       PIN_C6                                    
#define LCD_DATA7       PIN_C7  
#include <lcd.c>
#define NO_OBJECT       0
float32 num_pulse,range;
#int_TIMER1
void  TIMER1_isr(void) 
{
   disable_interrupts(GLOBAL);
   num_pulse+=0xffff; 
   enable_interrupts(GLOBAL);
}
#int_EXT2
void  EXT2_isr(void) 
{
   disable_interrupts(GLOBAL);
   num_pulse+=get_timer1();
   enable_interrupts(GLOBAL);
}
#define trig PIN_B3
#define echo PIN_B2
 
void start();
float32 kc();  
void main()
{
   enable_interrupts(INT_EXT2);
   enable_interrupts( INT_EXT2_L2H );
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);      //21.8 ms overflow
   enable_interrupts(INT_TIMER1);
   disable_interrupts(GLOBAL);
   port_b_pullups (TRUE);
   lcd_init(); delay_us(1); 
   lcd_putc("NGUYEN BA QUAN"); delay_ms(100);
   lcd_putc("\f");     
   while(TRUE)
   {
      range=kc();
            if(range==NO_OBJECT)
            {  
               lcd_putc("\f");
               lcd_putc("ko co vat can");
            }
            else
            {
               lcd_putc("\f");
               printf(lcd_putc,"khoang cach:%3.2f",range); delay_ms(50);
              
            }

   }

}
void start()
{ 
  output_high(trig);
  delay_us(50);
  output_low(trig);
  while(!(input(echo)));
  set_timer1(0);
  enable_interrupts(GLOBAL);
  delay_ms(50);
}
float32 kc()
{
   float32 time_us=0,distance=0;
   start();
   disable_interrupts(GLOBAL);
   if(num_pulse>180000)
   {
      num_pulse=0;
   return NO_OBJECT;
   }
   else
   {
      time_us=num_pulse/6;
      distance=time_us/58;
      num_pulse=0;
      
   return distance;
   }
}

