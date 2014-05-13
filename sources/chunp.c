#include <bcm2835.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define OUT_PIN1 RPI_GPIO_P1_15
#define OUT_PIN2 RPI_V2_GPIO_P1_13
#define OUT_PIN3 RPI_GPIO_P1_12
#define OUT_PIN4 RPI_GPIO_P1_11

#define OUR_INPUT_FIFO_NAME "/tmp/my_fifo"

void set_pins_output ( void );
void set_output_pins_low ( void );

unsigned char rx_buffer [ 256 ];
int rx_length;
int our_input_fifo_filestream = -1;
int result;

int main ()
{
  if (!bcm2835_init())
    return 1;
  set_pins_output ();
  set_output_pins_low ();

  result = mkfifo ( OUR_INPUT_FIFO_NAME, 0777 );
  our_input_fifo_filestream = open ( OUR_INPUT_FIFO_NAME, ( O_RDONLY | O_NONBLOCK ) );

  while ( 1 )
    {
      rx_length = read ( our_input_fifo_filestream, ( void* ) rx_buffer, 255 );
      if ( rx_length > 0 )
	{
	  rx_buffer [ rx_length ] = '\0';

	  if ( 0 == strncmp ( "10", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN1, LOW );
	  else;
	  if ( 0 == strncmp ( "11", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN1, HIGH );
	  else;
	  if ( 0 == strncmp ( "20", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN2, LOW );
	  else;
	  if ( 0 == strncmp ( "21", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN2, HIGH );
	  else;
	  if ( 0 == strncmp ( "30", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN3, LOW );
	  else;
	  if ( 0 == strncmp ( "31", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN3, HIGH );
	  else;
	  if ( 0 == strncmp ( "40", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN4, LOW );
	  else;
	  if ( 0 == strncmp ( "41", rx_buffer, 2 ) )
	    bcm2835_gpio_write ( OUT_PIN4, HIGH );
	  else;
	}else;
    }
}

void set_pins_output ( void )
{
  bcm2835_gpio_fsel ( OUT_PIN1, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN2, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN3, BCM2835_GPIO_FSEL_OUTP );
  bcm2835_gpio_fsel ( OUT_PIN4, BCM2835_GPIO_FSEL_OUTP );
}

void set_output_pins_low ( void )
{
  bcm2835_gpio_write ( OUT_PIN1, LOW);
  bcm2835_gpio_write ( OUT_PIN2, LOW);
  bcm2835_gpio_write ( OUT_PIN3, LOW);
  bcm2835_gpio_write ( OUT_PIN4, LOW);
}
