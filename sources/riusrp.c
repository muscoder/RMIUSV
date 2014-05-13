#include <bcm2835.h>
#include <unistd.h>
#include <signal.h>
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
void button_signal_handler ( int signo );
void signal_on_state_change_pin1 ( void );
void signal_on_state_change_pin2 ( void );
void signal_on_state_change_pin3 ( void );
void signal_on_state_change_pin4 ( void );

pid_t child_id [ 4 ];

int main ( void )
{
  int i;

  if (!bcm2835_init())
    return 1;

  set_pins_output ();
  set_output_pins_low ();
  set_pins_input ();
  delay ( 100 );

  signal ( SIGUSR1, button_signal_handler );

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

  bcm2835_close();
  return 0;
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
	      kill ( getppid(), SIGUSR1 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN1 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN1 ) );

 kill ( getppid(), SIGUSR1 );
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
	      kill ( getppid(), SIGUSR1 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN2 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN2 ) );

 kill ( getppid(), SIGUSR1 );
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
	      kill ( getppid(), SIGUSR1 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN3 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN3 ) );

 kill ( getppid(), SIGUSR1 );
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
	      kill ( getppid(), SIGUSR1 );

do
  {
    while ( bcm2835_gpio_lev ( IN_PIN4 ) )
      delay ( 1 );
    delay ( 50 );
  }
 while ( bcm2835_gpio_lev ( IN_PIN4 ) );

 kill ( getppid(), SIGUSR1 );
	    }
	  else;
	}else;
      delay ( 1 );
    }
}

void button_signal_handler ( int signo )
{
  bcm2835_gpio_write ( OUT_PIN1, bcm2835_gpio_lev ( IN_PIN1 ) );
  bcm2835_gpio_write ( OUT_PIN2, bcm2835_gpio_lev ( IN_PIN2 ) );
  bcm2835_gpio_write ( OUT_PIN3, bcm2835_gpio_lev ( IN_PIN3 ) );
  bcm2835_gpio_write ( OUT_PIN4, bcm2835_gpio_lev ( IN_PIN4 ) );
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
