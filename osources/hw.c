#include "Button.h"

void initButtons( void ){
  if (!bcm2835_init())
    return 1;
  // Set RPI pin to be an input
  bcm2835_gpio_fsel ( BUTTON_0, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_fsel ( BUTTON_1, BCM2835_GPIO_FSEL_INPT );
  // with a pullup
  bcm2835_gpio_set_pud ( BUTTON_0, BCM2835_GPIO_PUD_OFF );
  bcm2835_gpio_set_pud ( BUTTON_1, BCM2835_GPIO_PUD_OFF );
}

void initLEDs( void ){
  if (!bcm2835_init())
    return 1;
  // Set RPI pin to be an input 
  bcm2835_gpio_fsel ( LED_0, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( LED_1, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( LED_2, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( LED_3, BCM2835_GPIO_FSEL_OUTP );
}

uint8_t getButton( uint8_t pin ){
  while ( 1 ) {
    if ( bcm2835_gpio_lev ( pin ) ) {
      delay ( 50 );
      if ( bcm2835_gpio_lev ( pin ) ) {
        return 1; //sig_send_val ( getppid (), SIGUSR1, 1 );
        do {
          while ( bcm2835_gpio_lev ( pin ) )
            delay ( 1 );
          delay ( 50 );}
        while ( bcm2835_gpio_lev ( pin ) );
        return 1; //sig_send_val ( getppid (), SIGUSR1, 1 );
      }else;
    }else;
    delay ( 1 );
  }
}

void setLED(uint8_t pin, uint8_t on){
  bcm2835_gpio_write(pin, on);
}
