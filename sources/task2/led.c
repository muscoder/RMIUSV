#include <bcm2835.h>
#include <stdio.h>
#include <time.h>

#define OUT_PIN0 RPI_GPIO_P1_15
#define OUT_PIN1 RPI_GPIO_P1_22
#define OUT_PIN2 RPI_GPIO_P1_24
#define OUT_PIN3 RPI_GPIO_P1_26

#define bool char

void delay_ms(int);
void initLed(void);
void setLedsLow(void);
void turnOnLed(uint8_t);

int main( void ){
  uint8_t result;

  if(!bcm2835_init())
    return 1;
  
  initLed();
  setLedsLow();

  while(1) {
    delay(100);

    scanf("%d", &result);

    turnOnLed(result);
  }
  return 0;
}

void turnOnLed(uint8_t x){
  uint8_t bits[4];

  bits[0] = (((x & 1) + '0') == '1') ? 0x1 : 0x0;
  x >>= 1;
  bits[1] = (((x & 1) + '0') == '1') ? 0x1 : 0x0;
  x >>= 1;
  bits[2] = (((x & 1) + '0') == '1') ? 0x1 : 0x0;
  x >>= 1;
  bits[3] = ((x + '0') == '1') ? 0x1 : 0x0;

  bcm2835_gpio_write(OUT_PIN0, bits[0]);
  bcm2835_gpio_write(OUT_PIN1, bits[1]);
  bcm2835_gpio_write(OUT_PIN2, bits[2]);
  bcm2835_gpio_write(OUT_PIN3, bits[3]);
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


void delay_ms(int milliseconds)
{
  long pause;
  clock_t now,then;

  pause = milliseconds*(CLOCKS_PER_SEC/1000);
  now = then = clock();
  while( (now-then) < pause )
    now = clock();
}
