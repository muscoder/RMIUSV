//------------------------------------------ led blinking code --------------------------------------------------//
#include <bcm2835.h>
#define PIN RPI_GPIO_P1_15
int main()
{
  if (!bcm2835_init()) // initialize the library
    return 1;

  bcm2835_gpio_fsel (PIN, BCM2835_GPIO_FSEL_OUTP); // Set the pin to be an output

  while (1)
    {
      bcm2835_gpio_write(PIN, HIGH); // Turn it on
      bcm2835_delay(500); // wait a bit
      bcm2835_gpio_write(PIN, LOW); // turn it off
      bcm2835_delay(500); // wait a bit
    }
  bcm2835_close(); // close the library

  return 0;
}

//------------------------------------------ led blinking code --------------------------------------------------//
