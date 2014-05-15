#include <bcm2835.h>
#include <stdio.h>

#define IN_PIN0 RPI_GPIO_P1_16

#define bool char

void initButton(void);
bool getButton( uint8_t );

int main( void ){

  if(!bcm2835_init())
    return 1;
  
  initButton();

  while(1) {
    bool but1;
    static bool prev1 = 0;
    static uint8_t set = 0;
    
    prev1 = but1;
    but1 = getButton(IN_PIN0);

    if((but1 & !prev2)) {
      printf("1\n");
    } else;

    fflush(stdout);
  }

  return 0;
}

void initButton( void ){
  bcm2835_gpio_fsel ( IN_PIN0, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN0, BCM2835_GPIO_PUD_OFF );
}

bool getButton( uint8_t pin ){
  static bool prev = 0;
  bool sample;
  sample = (bool) bcm2835_gpio_lev(pin);
  if(sample != prev) {
    delay(50);
  }

  prev = sample;
  return (bool) sample;
}
