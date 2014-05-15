#include <bcm2835.h>
#include <stdio.h>

#define IN_PIN0 RPI_GPIO_P1_16
#define IN_PIN1 RPI_GPIO_P1_18

#define bool char

void initButton(void);
bool getButton( uint8_t );

int main( void ){

  if(!bcm2835_init())
    return 1;
  
  initButton();

  while(1) {
    bool but1, but2;
    static bool prev1 = 0;
    static bool prev2 = 0;
    static uint8_t set = 0;
    
    prev1 = but1;
    prev2 = but2;
    but1 = getButton(IN_PIN0);
    but2 = getButton(IN_PIN1);

    if(but1 & !prev1){
      set = ~set;
    }else;

    if((but2 & !prev2)&set) {
      printf("1\n");
    } else if((but2 & !prev2)&!set) {
      printf("0\n");
    } else;

    fflush(stdout);
  }

  return 0;
}

void initButton( void ){
  bcm2835_gpio_fsel ( IN_PIN0, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN0, BCM2835_GPIO_PUD_OFF );
  bcm2835_gpio_fsel ( IN_PIN1, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN1, BCM2835_GPIO_PUD_OFF );
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
