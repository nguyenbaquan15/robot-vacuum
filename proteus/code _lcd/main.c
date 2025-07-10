#include <main.h>
#define LCD_ENABLE_PIN  PIN_C0                                    
#define LCD_RS_PIN      PIN_C3                                  
#define LCD_RW_PIN      PIN_C1                                   
#define LCD_DATA4       PIN_C4                                    
#define LCD_DATA5       PIN_C5                                    
#define LCD_DATA6       PIN_C6                                    
#define LCD_DATA7       PIN_C7    

#include <lcd.c>


void main()
{
   lcd_init();
   lcd_putc("DO AN TOT NGHIEP"); delay_ms(100);
   lcd_putc("\fSV THUC HIEN"); delay_ms(100);
   lcd_putc("\fNGUYEN BA QUAN\n"); delay_ms(100);
   lcd_putc("\fNGUYEN QUOC VU"); delay_ms(100);
   lcd_putc("\fDINH DUC KHA"); delay_ms(100);
  
 /* cach2 thu vien lcd khac
  int str[20];
  LCD_Clear();
  LCD_Gotoxy(0,0);
  sprintf(str,"SO PHOI THAP");
  LCD_Puts(str);
  delay_ms(1000);
  */
   while(TRUE)
   {   
   
   }

}
