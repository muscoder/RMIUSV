#include <bcm2835.h>
#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#define IN_PIN1 RPI_GPIO_P1_07
#define IN_PIN2 RPI_GPIO_P1_22
#define IN_PIN3 RPI_GPIO_P1_18
#define IN_PIN4 RPI_GPIO_P1_16

#define OUT_PIN1 RPI_GPIO_P1_15
#define OUT_PIN2 RPI_V2_GPIO_P1_13
#define OUT_PIN3 RPI_GPIO_P1_12
#define OUT_PIN4 RPI_GPIO_P1_11

void set_pins_input ( void );
void set_pins_output ( void );
void set_output_pins_low ( void );
void button_signal_handler ( int sig, siginfo_t *siginfo, void *context );
void signal_on_state_change_pin1 ( void );
void signal_on_state_change_pin2 ( void );
void signal_on_state_change_pin3 ( void );
void signal_on_state_change_pin4 ( void );
void sig_set_handler ( int signo, void *handler );
void sig_send_val ( pid_t id, int signo, int val );
void sig_send_msg ( pid_t id, int signo, char *msg );
void signal_message_on_input_change ( void );
void main_signal_handler ( int sig, siginfo_t *siginfo, void *context );

int main ( void )
{
  pid_t child_id;

  if (!bcm2835_init())
    return 1;

  set_pins_output ();
  set_output_pins_low ();
  set_pins_input ();
  delay ( 100 );

  sig_set_handler ( SIGUSR1, &main_signal_handler );

  if ( ! ( child_id = fork () ) )
    {
      signal_message_on_input_change ();
      _exit ( 0 );
    }
  else;

  while ( 1 )
    delay ( 1 );

  bcm2835_close();
  return 0;
}

void signal_message_on_input_change ( void )
{
  pid_t child_id [ 5 ];

  sig_set_handler ( SIGUSR1, &button_signal_handler );

  if ( ! ( child_id [ 0 ] = fork () ) )
    {
      signal_on_state_change_pin1 ();
      _exit ( 0 );
    }
  else;

  if ( ! ( child_id [ 1 ] = fork () ) )
    {
      signal_on_state_change_pin2 ();
      _exit ( 0 );
    }
  else;

  if ( ! ( child_id [ 2 ] = fork () ) )
    {
      signal_on_state_change_pin3 ();
      _exit ( 0 );
    }
  else;

  if ( ! ( child_id [ 3 ] = fork () ) )
    {
      signal_on_state_change_pin4 ();
      _exit ( 0 );
    }
  else;

  while ( 1 )
    delay ( 1 );
}

void signal_on_state_change_pin1 ( void )
{
  while ( 1 )
    {
      if ( bcm2835_gpio_lev ( IN_PIN1 ) )
	{
	  delay ( 50 );
	  if ( bcm2835_gpio_lev ( IN_PIN1 ) )
	    {
	      sig_send_val ( getppid (), SIGUSR1, 1 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN1 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN1 ) );

 sig_send_val ( getppid (), SIGUSR1, 1 );
	    }
	  else;
	}else;
      delay ( 1 );
    }
}

void signal_on_state_change_pin2 ( void )
{
  while ( 1 )
    {
      if ( bcm2835_gpio_lev ( IN_PIN2 ) )
	{
	  delay ( 50 );
	  if ( bcm2835_gpio_lev ( IN_PIN2 ) )
	    {
	      sig_send_val ( getppid (), SIGUSR1, 2 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN2 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN2 ) );

 sig_send_val ( getppid (), SIGUSR1, 2 );
	    }
	  else;
	}else;
      delay ( 1 );
    }
}

void signal_on_state_change_pin3 ( void )
{
  while ( 1 )
    {
      if ( bcm2835_gpio_lev ( IN_PIN3 ) )
	{
	  delay ( 50 );
	  if ( bcm2835_gpio_lev ( IN_PIN3 ) )
	    {
	      sig_send_val ( getppid (), SIGUSR1, 3 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN3 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN3 ) );

 sig_send_val ( getppid (), SIGUSR1, 3 );
	    }
	  else;
	}else;
      delay ( 1 );
    }
}

void signal_on_state_change_pin4 ( void )
{
  while ( 1 )
    {
      if ( bcm2835_gpio_lev ( IN_PIN4 ) )
	{
	  delay ( 50 );
	  if ( bcm2835_gpio_lev ( IN_PIN4 ) )
	    {
	      sig_send_val ( getppid (), SIGUSR1, 4 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN4 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN4 ) );

 sig_send_val ( getppid (), SIGUSR1, 4 );
	    }
	  else;
	}else;
      delay ( 1 );
    }
}

void main_signal_handler ( int sig, siginfo_t *siginfo, void *context )
{
  bcm2835_gpio_write ( OUT_PIN1, *( *( ( char ** ) &siginfo -> si_value ) + 0 ) );
  bcm2835_gpio_write ( OUT_PIN2, *( *( ( char ** ) &siginfo -> si_value ) + 1 ) );
  bcm2835_gpio_write ( OUT_PIN3, *( *( ( char ** ) &siginfo -> si_value ) + 2 ) );
  bcm2835_gpio_write ( OUT_PIN4, *( *( ( char ** ) &siginfo -> si_value ) + 3 ) );
}

void button_signal_handler ( int sig, siginfo_t *siginfo, void *context )
{
  switch ( *( ( int * ) &siginfo -> si_value ) )
    {
    case 1:
      sig_send_msg ( getppid (), SIGUSR1, "\1\0\0\0" );
      break;
    case 2:
      sig_send_msg ( getppid (), SIGUSR1, "\0\1\0\0" );
      break;
    case 3:
      sig_send_msg ( getppid (), SIGUSR1, "\0\0\1\0" );
      break;
    case 4:
      sig_send_msg ( getppid (), SIGUSR1, "\0\0\0\1" );
      break;
    };
}

void set_output_pins_low ( void )
{
  bcm2835_gpio_write ( OUT_PIN1, LOW);
  bcm2835_gpio_write ( OUT_PIN2, LOW);
  bcm2835_gpio_write ( OUT_PIN3, LOW);
  bcm2835_gpio_write ( OUT_PIN4, LOW);
}

void set_pins_output ( void )
{
  bcm2835_gpio_fsel ( OUT_PIN1, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN2, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN3, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN4, BCM2835_GPIO_FSEL_OUTP );
}

void set_pins_input ( void )
{
  bcm2835_gpio_fsel ( IN_PIN1, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN1, BCM2835_GPIO_PUD_OFF );

  bcm2835_gpio_fsel ( IN_PIN2, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_set_pud ( IN_PIN2, BCM2835_GPIO_PUD_OFF );

  bcm2835_gpio_fsel ( IN_PIN3, BCM2835_GPIO_FSEL_INPT );
  bcm2835_gpio_fsel ( IN_PIN3, BCM2835_GPIO_FSEL_INPT );

  bcm2835_gpio_set_pud ( IN_PIN4, BCM2835_GPIO_PUD_OFF );
  bcm2835_gpio_set_pud ( IN_PIN4, BCM2835_GPIO_PUD_OFF );
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
