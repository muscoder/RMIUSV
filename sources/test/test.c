#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define IN_PIN0 RPI_GPIO_P1_16
#define IN_PIN1 RPI_GPIO_P1_18

#define OUT_PIN0 RPI_GPIO_P1_15
#define OUT_PIN1 RPI_GPIO_P1_22
#define OUT_PIN2 RPI_GPIO_P1_24
#define OUT_PIN3 RPI_GPIO_P1_26

void set_pins_input ( void );
void set_pins_output ( void );
void set_output_pins_low ( void );
void button_signal_handler ( int sig, siginfo_t *siginfo, void *context );
void signal_on_state_change_pin0 ( void );
void signal_on_state_change_pin1 ( void );
void sig_set_handler ( int signo, void *handler );
void sig_send_val ( pid_t id, int signo, int val );

pid_t child_id [ 2 ];

int main ( void )
{
  int i;

  if (!bcm2835_init())
    return 1;

  set_pins_input ();
  set_pins_output();
  set_output_pins_low();
  delay ( 100 );

  printf("Input/Outputs are set...\n");

  sig_set_handler ( SIGUSR1, &button_signal_handler );

  if ( ! ( child_id [ 0 ] = fork () ) )
    {
      signal_on_state_change_pin0 ();
      _exit ( 0 );
    }
  else;

  if ( ! ( child_id [ 1 ] = fork () ) )
    {
      signal_on_state_change_pin1 ();
      _exit ( 0 );
    }
  else;

  while ( 1 )
    delay ( 1 );

  bcm2835_close();
  return 0;
}

void signal_on_state_change_pin0 ( void ) {
  while ( 1 ) {
    if ( bcm2835_gpio_lev ( IN_PIN0 ) ) {
      delay ( 50 );
      if ( bcm2835_gpio_lev ( IN_PIN0 ) ) {
	sig_send_val ( getppid (), SIGUSR1, 1 );
	do {
	  while ( bcm2835_gpio_lev ( IN_PIN0 ) )
	    delay ( 1 );
	  delay ( 50 );}
	while ( bcm2835_gpio_lev ( IN_PIN0 ) );
	//sig_send_val ( getppid (), SIGUSR1, 1 ); 
      }else;
    }else;
    delay ( 1 );
  }
}

void signal_on_state_change_pin1 ( void ) {
  while ( 1 ) {
    if ( bcm2835_gpio_lev ( IN_PIN1 ) ) {
      delay ( 50 );
      if ( bcm2835_gpio_lev ( IN_PIN1 ) ) {
        sig_send_val ( getppid (), SIGUSR1, 2 );
        do {
          while ( bcm2835_gpio_lev ( IN_PIN1 ) )
            delay ( 1 );
          delay ( 50 );}
        while ( bcm2835_gpio_lev ( IN_PIN1 ) );
        //sig_send_val ( getppid (), SIGUSR1, 2 );
      }else;
    }else;
    delay ( 1 );
  }
}


void button_signal_handler ( int sig, siginfo_t *siginfo, void *context )
{
  static char set1 = 0; char buffer[500];
  static int bitCount = 0; static uint8_t dataReg = 0;
  if ( 1 == *( ( int * ) &siginfo -> si_value ) ){
    set1 = ~set1;
    bcm2835_gpio_write( OUT_PIN0, set1 );
  }else;

  if ( 2 == *( ( int * ) &siginfo -> si_value ) ){
    dataReg = (dataReg << 1) | set1;
    bitCount++;
    if(bitCount == 2){
      sprintf (buffer, "echo %d >> /tmp/my_fifo &", dataReg);
      system(buffer);
      dataReg = 0;
      bitCount = 0;
    }
  }else;

}

void set_pins_input ( void )
{
  bcm2835_gpio_fsel ( IN_PIN0, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN0, BCM2835_GPIO_PUD_OFF );
  bcm2835_gpio_fsel ( IN_PIN1, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN1, BCM2835_GPIO_PUD_OFF );
}

void sig_send_val ( pid_t id, int signo, int val )
{
  union sigval *sigdata;

  sigdata = malloc ( sizeof ( union sigval ) );
  sigdata -> sival_int = val;

  sigqueue ( id, signo, *sigdata );

  free ( sigdata );
}

void sig_set_handler ( int signo, void *handler )
{
  struct sigaction *act;
  act = malloc ( sizeof ( struct sigaction ) );
  act -> sa_sigaction = handler;
  act -> sa_flags = SA_SIGINFO;

  sigaction ( signo, act, NULL );
}

void set_pins_output ( void )
{
  bcm2835_gpio_fsel ( OUT_PIN0, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN1, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN2, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN3, BCM2835_GPIO_FSEL_OUTP );
}

void set_output_pins_low ( void )
{
  bcm2835_gpio_write ( OUT_PIN0, LOW);
  bcm2835_gpio_write ( OUT_PIN1, LOW);
  bcm2835_gpio_write ( OUT_PIN2, LOW);
  bcm2835_gpio_write ( OUT_PIN3, LOW);
}
