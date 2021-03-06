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
    static char dataReg;
    char state;
    static int bitCount = 0;
    uint8_t result = 0;
    char str1[60] = "\0";
    static char str2[3] = "\0";

    scanf("%s", str1);
    state = (strcmp(str1, "") >= 50) ? 1 : 0;
    
    switch(state){
    case 0:
      bitCount++;
      str2[bitCount] = str1[0];
      if(bitCount == 2){
	result = (str2[1] == '1') ? ((str2[2] == '1') ? 3 : 1) : ((str2[2] == '1') ? 2 : 0) ;
	turnOnLed(result);
	dataReg = 0;
	bitCount = 0;
      } else;
      break;
    case 1:
      printf("%s\n", str1);
    }
  }
  return 0;
}

void turnOnLed(uint8_t result){
  if(result == 0){
    bcm2835_gpio_write(OUT_PIN0, HIGH);
    bcm2835_gpio_write(OUT_PIN1, LOW);
    bcm2835_gpio_write(OUT_PIN2, LOW);
    bcm2835_gpio_write(OUT_PIN3, LOW);
  } else if(result == 1){
    bcm2835_gpio_write(OUT_PIN0, LOW);
    bcm2835_gpio_write(OUT_PIN1, HIGH);
    bcm2835_gpio_write(OUT_PIN2, LOW);
    bcm2835_gpio_write(OUT_PIN3, LOW);
  } else if(result == 2){
    bcm2835_gpio_write(OUT_PIN0, LOW);
    bcm2835_gpio_write(OUT_PIN1, LOW);
    bcm2835_gpio_write(OUT_PIN2, HIGH);
    bcm2835_gpio_write(OUT_PIN3, LOW);
  } else if(result == 3){
    bcm2835_gpio_write(OUT_PIN0, LOW);
    bcm2835_gpio_write(OUT_PIN1, LOW);
    bcm2835_gpio_write(OUT_PIN2, LOW);
    bcm2835_gpio_write(OUT_PIN3, HIGH);
  } else;

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


