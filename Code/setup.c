void setup()
{
   lcd_init();
   enable_interrupts(GLOBAL);
   enable_interrupts(INT_EXT);
   enable_interrupts(INT_EXT1);
   enable_interrupts( INT_EXT_L2H );
   enable_interrupts( INT_EXT1_L2H );
   setup_timer_2(T2_DIV_BY_4,74,1);      //100 us overflow, 100 us interrupt
   setup_ccp1(CCP_PWM|CCP_SHUTDOWN_AC_L|CCP_SHUTDOWN_BD_L);
   setup_comparator(NC_NC_NC_NC);
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_4);
   setup_adc(ADC_CLOCK_INTERNAL );
   setup_adc_ports(AN0);
   set_adc_channel(0);
}
