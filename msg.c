
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


	char msg[50];
	printf("Enter the msg[max 50 characters]:");
	fgets(msg,50,stdin);

     	char mob[10];
	printf("Enter the Mobile No.:");
	scanf("%s",&mob);


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


 	delay (3000) ;

	//serialPuts (fd, "AT+CMGS=\"your mobile number\"\r\n") ;//take the input from user instead of hardcoding
	serialPuts (fd, "AT+CMGS=\"") ;

	/*char mob[10];
	printf("Enter the Mobile No.:");
	scanf("%s",&mob);
	*/
	serialPuts (fd, mob) ;
	serialPuts (fd, "\"\r\n") ;
	
	delay (1000) ;
	
	//serialPuts (fd, "this is a sample msg from Raspberry Pi 3+B\r\n") ;//hard coded msg , should be prompted to user
	

	/*char msg[50];
	printf("Enter the msg[max 50 characters]:");
	scanf("%s",msg); //does not consider spaces
	*/

	serialPuts (fd, msg) ;
	serialPuts (fd, "\r\n") ;
	delay (1000) ;
	
	serialPuts (fd, "\032") ;//sending cntrl+z
    
	delay (5000) ;

	printf("Bytes to read:%d\n",serialDataAvail (fd));

	while (serialDataAvail (fd))
	{
		printf (" %c ", serialGetchar (fd)) ;
    	}

	printf ("\n") ;
	return 0 ;
}
