# SIMCOM
Programs for SimCom SIM900A Module

Requirement: WiringPi library should be installed on Raspberrypi

File Info

msg.c : Program to send text message.

tcp.c : Program to send data to a TCP Server.

Compile 

gcc -c msg.c

gcc -o msg msg.o -l wiringPi


gcc -c tcp.c

gcc -o tcp tcp.o -l wiringPi


Credits : WiringPi@https://github.com/WiringPi/WiringPi
