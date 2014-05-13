#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define OUR_INPUT_FIFO_NAME "/tmp/my_fifo"

unsigned char rx_buffer [ 256 ];
int rx_length;
int our_input_fifo_filestream = -1;

int result;

int main ()
{
  printf ( "Making FIFO...\n" );
  result = mkfifo ( OUR_INPUT_FIFO_NAME, 0777 );
  our_input_fifo_filestream = open ( OUR_INPUT_FIFO_NAME, ( O_RDONLY | O_NONBLOCK ) );

  while ( 1 )
    {
      rx_length = read ( our_input_fifo_filestream, ( void* ) rx_buffer, 255 ); //Filestream, buffer to store in, number of bytes to read (max)
      if ( rx_length > 0 )
	{
	  rx_buffer [ rx_length ] = '\0';
	  printf ( "FIFO %i bytes read : %s\n", rx_length, rx_buffer );
	}else;
    }
}
