#include <main.h>
#include <var.h>
#include "lcd.c"
#define SRF05_TRIGGER1   PIN_B1
#define SRF05_TRIGGER2   PIN_B2
#define SRF05_TRIGGER3   PIN_B3
#define SRF05_ECHO      PIN_B0
#define NO_OBJECT       0
#INT_EXT
void Ngat_Ngoai(void)
{  
   disable_interrupts(GLOBAL);
   num_pulse+=get_timer1();
   range_ok=1;
   enable_interrupts(GLOBAL);
}
#INT_TIMER1           
void  Ngat_Timer1(void) 
{
   disable_interrupts(GLOBAL);
   num_pulse+=0xffff; 
   enable_interrupts(GLOBAL);
}
void  SRF05_StartRange()
{
   while(!range_ok)
   {
         output_high(SRF05_TRIGGER1);
         delay_ms(15);                          // Phai tao 1 xung len co do lon it nhat 10ms
         output_low(SRF05_TRIGGER1);             // Bat dau phep do.
         while(!(input(SRF05_ECHO)));           // Doi cho den khi chan ECHO duoc keo len cao
         set_timer1(0);
         enable_interrupts(GLOBAL);
         delay_ms(50);
   }
}
float32 SRF05_GetDistance()
{
   float32 time_us=0,distance=0;
   SRF05_StartRange();
   disable_interrupts(GLOBAL);
   if(num_pulse>180000)
   {
      num_pulse=0;
      range_ok=0;
   return NO_OBJECT;
   }
   else
   {
      time_us=num_pulse/6;
      distance=time_us/58;
      num_pulse=0;
      range_ok=0;
   return distance;
   }
}
void main()
{  
   unsigned char str[20],i=0;
   float32 range;
   output_float(SRF05_ECHO);
   output_drive(SRF05_TRIGGER1);
   output_drive(SRF05_TRIGGER2);
   output_drive(SRF05_TRIGGER3);
   LCD_Init();
   sprintf(str,"DEMO SRF05");
   delay_ms(10);
   LCD_Puts(str);
   delay_ms(1000);
   LCD_Clear();
   sprintf(str,"BanLinhKien.Vn");
   LCD_Gotoxy(1,0);
   LCD_Puts(str); 
   port_b_pullups (TRUE);
   ext_int_edge(H_TO_L);                  // ngat canh xuong
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_1);//F_TIMER1=F_OSC/4
   enable_interrupts(INT_TIMER1);
   enable_interrupts(INT_EXT);            // kich hoat ngat ngoai
   disable_interrupts(GLOBAL);
   while(TRUE)
   {
            range=SRF05_GetDistance();
            if(range==NO_OBJECT)
            {
               LCD_Gotoxy(0,1);
               sprintf(str,"Khong Co Vat Can");
               LCD_Puts(str);
               delay_ms(500);
            }
            else
            {
               LCD_Gotoxy(0,1);
               sprintf(str,"Dis : %3.2f Cm  ",range);
               LCD_Puts(str);
            }
     }
   
}
                
