/**
  ******************************************************************************
  * Ten Tep      :        lcd_16x2.c
  * Tac Gia      :        Nguyen Quy Nhat
  * Cong Ty      :        MinhHaGroup
  * Website      :        BanLinhKien.Vn
  * Phien Ban    :        V1.0.0
  * Ngay         :        31-07-2012
  * Tom Tat      :        Dinh nghia cac ham dieu khien LCD 16x2.
  *           
  *
  ******************************************************************************
  * Chu Y        :   Phai dinh nghia cac chan su dung cho LCD vao ham main.h
  *                      
  ******************************************************************************
  */
//Tao Xung
//#include <18f4520.h>
#use delay(clock=20000000)
#define LCD_En PIN_C0                        
#define LCD_RS PIN_C3  
#define LCD_RW PIN_C1 
#define LCD_D4 PIN_C4 
#define LCD_D5 PIN_C5 
#define LCD_D6 PIN_C6 
#define LCD_D7 PIN_C7 

void LCD_Enable(void)
{
 output_high(LCD_EN);
 delay_us(3);
 output_low(LCD_EN);
 delay_us(50); 
}
//Ham Gui 4 Bit Du Lieu Ra LCD
 void LCD_Send4Bit( unsigned char Data )
{
 output_bit(LCD_D4,Data&0x01);
 output_bit(LCD_D5,(Data>>1)&1);
 output_bit(LCD_D6,(Data>>2)&1);
 output_bit(LCD_D7,(Data>>3)&1);
}
// Ham Gui 1 Lenh Cho LCD
 void LCD_SendCommand (unsigned char command )
{
LCD_Send4Bit  ( command >>4 );/* Gui 4 bit cao */
LCD_Enable () ;
LCD_Send4Bit  ( command  );      /* Gui 4 bit thap*/
LCD_Enable () ;
}
// Ham Khoi Tao LCD
 void LCD_Init ( void )
{
output_drive(LCD_D4);
output_drive(LCD_D5);
output_drive(LCD_D6);
output_drive(LCD_D7);
output_drive(LCD_EN);
output_drive(LCD_RS);
output_drive(LCD_RW);
LCD_Send4Bit(0x00);
delay_ms(20);
output_low(LCD_RS);
output_low(LCD_RW);
LCD_Send4Bit(0x03);
LCD_Enable();
delay_ms(5);
LCD_Enable();
delay_us(100);
LCD_Enable();
LCD_Send4Bit(0x02);
LCD_Enable();
LCD_SendCommand( 0x28 );      // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
LCD_SendCommand( 0x0c);    // cho phep hien thi man hinh
LCD_SendCommand( 0x06 );      // tang ID, khong dich khung hinh
LCD_SendCommand( 0x01 ); // xoa toan bo khung hinh
}
void LCD_Gotoxy(unsigned char x, unsigned char y)
{
  unsigned char address;
  if(!y)
  address = (0x80+x);
  else
  address = (0xC0+x);
  delay_us(1000);
  LCD_SendCommand(address);
  delay_us(50);
}
// Ham Xoa Man Hinh LCD
void LCD_Clear()
{
  LCD_SendCommand(0x01);  
  delay_ms(10);
}
// Ham Gui 1 Ki Tu Len LCD
 void LCD_PutChar ( unsigned char Data )
{
 output_high(LCD_RS);
 LCD_SendCommand( Data );
 output_low(LCD_RS);
}
void LCD_Puts (char *s)
{
   while (*s)
   {
      LCD_PutChar(*s);
      s++;
   }
}








