#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

#define IN_PIN1 RPI_GPIO_P1_16

#define OUT_PIN1 RPI_GPIO_P1_15

void set_pins_input ( void );
void set_pins_output ( void );
void set_output_pins_low ( void );
void button_signal_handler ( int sig, siginfo_t *siginfo, void *context );
void signal_on_state_change_pin1 ( void );
void sig_set_handler ( int signo, void *handler );
void sig_send_val ( pid_t id, int signo, int val );

pid_t child_id [ 2 ];

int main ( void )
{
  int i;

  if (!bcm2835_init())
    return 1;

  set_pins_output ();
  set_output_pins_low ();
  set_pins_input ();
  delay ( 100 );

  printf("Input/Outputs are set...\n");

  sig_set_handler ( SIGUSR1, &button_signal_handler );

  if ( ! ( child_id [ 0 ] = fork () ) )
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

void signal_on_state_change_pin1 ( void ) {
  while ( 1 ) {
    if ( bcm2835_gpio_lev ( IN_PIN1 ) ) {
      delay ( 50 );
      if ( bcm2835_gpio_lev ( IN_PIN1 ) ) {
	sig_send_val ( getppid (), SIGUSR1, 1 );
	do {
	  while ( bcm2835_gpio_lev ( IN_PIN1 ) )
	    delay ( 1 );
	  delay ( 50 );}
	while ( bcm2835_gpio_lev ( IN_PIN1 ) );
	sig_send_val ( getppid (), SIGUSR1, 1 ); 
      }else;
    }else;
    delay ( 1 );
  }
}

void button_signal_handler ( int sig, siginfo_t *siginfo, void *context )
{
  static char led1 = 0; 

  if ( 1 == *( ( int * ) &siginfo -> si_value ) ){
    led1 = ~led1;
    bcm2835_gpio_write ( OUT_PIN1, led1 );
  }else;
}

void set_output_pins_low ( void )
{
  bcm2835_gpio_write ( OUT_PIN1, LOW);
}

void set_pins_output ( void )
{
  bcm2835_gpio_fsel ( OUT_PIN1, BCM2835_GPIO_FSEL_OUTP );
}

void set_pins_input ( void )
{
  bcm2835_gpio_fsel ( IN_PIN1, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN1, BCM2835_GPIO_PUD_OFF );
}

void sig_send_msg ( pid_t id, int signo, char *msg )
{
  union sigval *sigdata;

  sigdata = malloc ( sizeof ( union sigval ) );
  sigdata -> sival_ptr = msg;

  sigqueue ( id, signo, *sigdata );

  free ( sigdata );
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

