#include "hw.h"

int main( void ){
  if (!bcm2835_init())
    return 1;
  // initialize the RPI peripherals
  initButtons(); // There are 2 buttons
  initLEDs();    // There are 4 LEDs

  while(1){
    setLED(0, HIGH);
  }

  return 0;
}
