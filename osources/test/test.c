#include "hw.h"

int main( void ){
  // initialize the RPI peripherals
  initButtons(); // There are 2 buttons
  initLEDs();    // There are 4 LEDs

  while(1){
    if(getButton(0) == 1){
      setLED(0,HIGH);
    }else{
      setLED(0,LOW);
    }
  }

  return 0;
}
