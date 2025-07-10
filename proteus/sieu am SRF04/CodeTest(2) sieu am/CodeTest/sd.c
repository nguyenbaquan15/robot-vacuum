/**
  ******************************************************************************
  * Ten Tep          :   Main.c
  * Tac Gia          : 
  * Cong Ty          :   
  * Website          :   Mualinhkien.Vn
  * Ngay             :
  * Tom Tat          :
  *
  *
  ******************************************************************************
  *                        SRF05 + 89S52 + LCD1602
  *                                                                 
  ******************************************************************************
  */
#include <AT89X52.H>
#include <stdio.h>
#define Line_1 0x80
#define Line_2 0xC0
#define Clear_LCD 0x01

/* Dinh nghia cac chan dieu khien LCD */
#define LCD_RS P2_0
#define LCD_WR P2_1
#define LCD_EN P2_2
/*Dinh Nghia Cac Chan DaTa */
#define LCD_D4 P2_4
#define LCD_D5 P2_5
#define LCD_D6 P2_6
#define LCD_D7 P2_7
/*Dinh nghia chan dieu khien SRF05 */
#define TRIGGER P3_1
#define ECHO    P3_2
/* Khai bao bien */
bit range_ok;
unsigned int distance;
float range;
float temp1;
char str[20];
char str2[20];
unsigned char data_recv[10];
unsigned char index;
 
void delay_us(unsigned int time)
{
unsigned int temp;
for(temp=0;temp<time;temp++);
}
void delay_ms(unsigned int time)
{
unsigned int i,j;
for(i=0;i<time;i++)
for(j=0;j<125;j++);
}
void  StartRange()
{
TRIGGER=1;
delay_ms(12);        // Phai tao 1 xung len co do lon it nhat 10ms
ECHO=1;                      // set chan ECHO la cong vao
delay_us(1);
TRIGGER=0;        // Bat dau phep do.
while(!(ECHO));        // Doi cho den khi chan ECHO duoc keo len cao
//TR0=1;                // Cho phep timer 0 hoat dong
TR0=IT0=EX0=EA=1;// cho phep ngat toan cuc
}
 
void lcd_enable_pulse(void)
{
LCD_EN=1;
delay_us(1);
LCD_EN=0;
delay_us(1);
}
void lcd_send_4bit_data ( unsigned char Data )
{
LCD_D4= Data&0x01;
LCD_D5=((Data>>1)&1);
LCD_D6=((Data>>2)&1);
LCD_D7=((Data>>3)&1);
}
#ifdef USE_LCD_READ
unsigned char lcd_read_4bit_data(void)
{
  unsigned char n = 0x00;
  /* Read the data port */
  n |= LCD_D4;
  n |= (LCD_D5) << 1;
  n |= (LCD_D6) << 2;
  n |= (LCD_D7) << 3;
  return(n);
}
unsigned char lcd_read_byte(void)
{
  unsigned char low,high;
  LCD_D4=LCD_D5=_LCD_D6=_LCD_D7=1;
  LCD_RS=1;
  delay_us(1);
  LCD_EN=1;
  delay_us(1);
  high = lcd_read_4bit_data();
  LCD_EN=0;
  delay_us(1);
  LCD_EN=1;
  delay_us(1);
  low = lcd_read_4bit_data();
  LCD_EN=0;
  return( (high<<4) | low);
}
char lcd_getc(unsigned char x, unsigned char y)            //lay 1 ky tu tai dia chi x,y
{
  char value;
  lcd_gotoxy(x,y);
  // Wait until busy flag is low.
  while(bit_test(lcd_read_byte(),7));
  LCD_RS=1;     
  value = lcd_read_byte();
  LCD_RS=0;
  return(value);
}                           
#endif           
void lcd_send_command (unsigned char Data )
{
#ifdef  USE_LCD_READ
  while ( 0x80&lcd_read_byte() ) ;
#else
  delay_us(20);
#endif                   
lcd_send_4bit_data  ( Data >>4 );      /* send 4 bit high  */
lcd_enable_pulse () ;
lcd_send_4bit_data  ( Data  );      /* send 4 bit low  */
lcd_enable_pulse () ;
}
void lcd_init ( void )
{
lcd_send_4bit_data  ( 0x00 );
delay_ms(10);                  //Was 200
LCD_RS=0;            // che do gui lenh
LCD_WR=0;            // che do ghi
LCD_EN=0;           
lcd_send_4bit_data  ( 0x03 );        // ket noi 8 bit
lcd_enable_pulse () ;
lcd_enable_pulse () ;
lcd_enable_pulse () ;
lcd_send_4bit_data  ( 0x02 );        // ket noi 4 bit
lcd_enable_pulse () ;
lcd_send_command( 0x2C );          // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
delay_ms(5);
lcd_send_command( 0x80);
lcd_send_command( 0x0c);      // cho phep hien thi man hinh
lcd_send_command( 0x06 );          // tang ID, khong dich khung hinh
delay_ms(5);
lcd_send_command( Clear_LCD );      // xoa toan bo khung hinh
delay_ms(10);
}
void lcd_gotoxy(unsigned char x, unsigned char y)
{
  unsigned char address;
  if(!y)
  address = (Line_1+x);
  else
  address = (Line_2+x);
  delay_us(1000);
  lcd_send_command(address);
  delay_us(50);
}
void lcd_clear()
{
  lcd_send_command( Clear_LCD );
  delay_us(10);
}
void lcd_putchar ( unsigned int Data )
{
LCD_RS=1;              // che do gui du lieu
lcd_send_command( Data );
LCD_RS=0;              // che do gui lenh
}
void lcd_puts(char *s)
{
  while (*s)
  {
      lcd_putchar(*s);
      s++;
  }
}
void ngatngoai0(void)interrupt 0
{
distance=TH0;
distance<<=8;
distance|=TL0;
range=(float)distance*12;
temp1=((58*11.0592));
//temp1= 641;
range=range/(temp1);
TR0=IT0=EX0= 0;    // Ngung timer
TL0=TH0=0;                // Xoa du lieu trong thanh ghi Timer 0 
range_ok=1;
}
void main()
{

lcd_init();
TMOD=0x01;
sprintf(str, "MUA LINH KIEN.VN");
lcd_gotoxy(0,0);
lcd_puts(str);
delay_ms(4000);
lcd_gotoxy(3,1) ;;
lcd_puts("TEST SRF05") ;
delay_ms(2000) ;
lcd_clear() ;
while(1)
{
if(!range_ok)
      {
StartRange();
delay_ms(100);
      }
      if(range_ok)
      {
//sprintf(str, "Khoang Canh La:");
sprintf(str,"Val_Timer: %u ",distance);
sprintf(str2,"Range:%.2f Cm",range);
    lcd_gotoxy(0,0);
    lcd_puts(str);
	lcd_puts ("     ") ;
    lcd_gotoxy(0,1);
    lcd_puts(str2);
    delay_ms(200);
    range_ok=0;
    }
}
}