
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <malloc.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main ()
{
  int fd ;
  int count ;
  unsigned int nextTime ;

  if ((fd = serialOpen ("/dev/ttyS0",9600)) < 0)
  {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1 ;
  }

  if (wiringPiSetup () == -1)
  {
    fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
    return 1 ;
  }

/*Check the connection*/
	serialPuts (fd, "AT\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 10)
	{
		printf("Connection not established try again");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Check if the SIM is Locked*/

	serialPuts (fd, "AT+CPIN?\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 32)
	{
		printf("SIM is Locked");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Check if the SIM is registered*/

	serialPuts (fd, "AT+CREG?\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 30)
	{
		printf("SIM not registered");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Check if GPRS is attached*/

	serialPuts (fd, "AT+CGATT?\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 30)
	{
		printf("GPRS not attached");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Reset the IP Session if any*/

	serialPuts (fd, "AT+CIPSHUT\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 23)
	{
		printf("IP Session invalid");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Initialize the IP Stack*/

	serialPuts (fd, "AT+CIPSTATUS\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 41)
	{
		printf("IP Stack not initialized");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Setup Single connection*/

	serialPuts (fd, "AT+CIPMUX=0\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 19)
	{
		printf("Connection not initialized");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Login*/

	serialPuts (fd, "AT+CSTT=\"www\",\" \",\" \"\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 29)
	{
		printf("Login failed");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;
/*Start Wireless*/

	serialPuts (fd, "AT+CIICR\r\n") ;
	
	delay (6000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 16)
	{
		printf("Couldn't start wireless service");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;
/*Get the IP Address*/

	serialPuts (fd, "AT+CIFSR\r\n") ;
	
	delay (1000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 16)
	{
		printf("Couldn't retrieve the IP address");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Connect to Server*/

	serialPuts (fd, "AT+CIPSTART=\"TCP\",\"XXX.XXX.XXX.XXX\",8000\r\n") ;/*your IP address*/
	
	delay (5000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 62)
	{
		printf("Couldn't connect to the server");
		exit(0);
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;
/*Send the data*/

	serialPuts (fd, "AT+CIPSEND\r\n") ;
	
	delay (1000) ;

	serialPuts (fd, "Hello Server from Pi") ;
	serialPuts (fd, "\r\n") ;
	delay (1000) ;
	
	serialPuts (fd, "\032") ;//sending cntrl+z

	delay (8000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 38)
	{
		printf("Error in sending the data");
		/*exit(0);*/
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}


 	delay (2000) ;

/*Close the connection*/

	serialPuts (fd, "AT+CIPSHUT\r\n") ;
	
	delay (5000) ;
	
	printf("Bytes to read:%d\n",serialDataAvail (fd));
	if(serialDataAvail (fd) < 23)
	{
		printf("Error in closing connection");
		/*exit(0);*/
	}
	

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
 	}

	printf ("\n") ;
	return 0 ;
}
