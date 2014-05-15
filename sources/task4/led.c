#include <bcm2835.h>
#include <stdio.h>

#define OUT_PIN0 RPI_GPIO_P1_15
#define OUT_PIN1 RPI_GPIO_P1_22
#define OUT_PIN2 RPI_GPIO_P1_24
#define OUT_PIN3 RPI_GPIO_P1_26

#define bool char

void initLed(void);
void setLedsLow(void);
void turnOnLed(uint8_t);

int main( void ){

  if(!bcm2835_init())
    return 1;
  
  initLed();
  setLedsLow();

  while(1) {
    char state;
    static uint8_t result = 0;
    char bits[4];
    char str1[60] = "\0";

    scanf("%s", str1);
    state = (strcmp(str1, "") >= 50) ? 1 : 0;
    
    switch(state){
    case 0:
      bits[3] = (result & 1) + '0';
      result >>= 1;
      bits[2] = (result & 1) + '0';
      result >>= 1;
      bits[1] = (result & 1 + '0');
      result >>= 1;
      bits[0] = result + '0';
      turnOnLed(bits);
      break;
    case 1:
      printf("%s\n", str1);
      sscanf(str1, "%d", &result);
      break;
    }
  }
  return 0;
}

void turnOnLed(char result){
  bcm2835_gpio_write(OUT_PIN0, (uint8_t)result[3]);
  bcm2835_gpio_write(OUT_PIN1, (uint8_t)result[2]);
  bcm2835_gpio_write(OUT_PIN2, (uint8_t)result[1]);
  bcm2835_gpio_write(OUT_PIN3, (uint8_t)result[0]);
}

void initLed(void){
  bcm2835_gpio_fsel ( OUT_PIN0, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN1, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN2, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN3, BCM2835_GPIO_FSEL_OUTP );
}

void setLedsLow (void)
{
  bcm2835_gpio_write ( OUT_PIN0, LOW);
  bcm2835_gpio_write ( OUT_PIN1, LOW);
  bcm2835_gpio_write ( OUT_PIN2, LOW);
  bcm2835_gpio_write ( OUT_PIN3, LOW);
}


