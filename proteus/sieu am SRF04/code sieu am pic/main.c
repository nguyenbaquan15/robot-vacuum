#include <main.h>
#define LCD_ENABLE_PIN  PIN_C0                                    
#define LCD_RS_PIN      PIN_C3                                    
#define LCD_RW_PIN      PIN_C1                                    
#define LCD_DATA4       PIN_C4                                    
#define LCD_DATA5       PIN_C5                                    
#define LCD_DATA6       PIN_C6                                    
#define LCD_DATA7       PIN_C7  
#include <lcd.c>
#define trig PIN_B3
#define echo PIN_B2
int16 t;
float kc=0;
void start();
void main()
{ 
   
   
   lcd_init(); delay_us(1); 
   lcd_putc("NGUYEN BA QUAN"); delay_ms(100);
   lcd_putc("\f");     
   while(TRUE)
   {
      start();
      delay_ms(5);
      printf(lcd_putc,"kc:%3.2f",kc);  delay_ms(100);
      lcd_putc("\f");
   }

}
void start()
{ 
  output_high(trig);
  delay_us(20);
  output_low(trig);
  while(!input(echo))  {} 
  setup_timer_1(T1_INTERNAL|T1_DIV_BY_4);
  set_timer1(0); 
  while(!input(echo))  {}                      
  set_timer1(0);                         
  while(input(echo))  {}      
  setup_timer_1( T1_DISABLED );
  t=get_timer1();                       
  kc=t*0.017;
  
}


