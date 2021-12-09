#include <wiringPi.h>
#include <stdio.h>
#define SW_PORT5 5
#define SW_PORT6 6
#define SW_PORT13 13

void interrupt5(){
	delay(10);
	printf("hello interrupt5\n");
	while( digitalRead(SW_PORT5) == 0){}

	printf("Bye interrupt5\n");
	delay(10);
}
void interrupt6(){
	delay(10);
	printf("hello interrupt6\n");
	while( digitalRead(SW_PORT6) == 0){}

	printf("Bye interrupt6\n");
	delay(10);
}
void interrupt13(){
	delay(10);
	printf("hello interrupt13\n");
	while( digitalRead(SW_PORT13) == 0){}

	printf("Bye interrupt13\n");
	delay(10);
}

int main(){
	if(wiringPiSetupGpio() < 0) return 1;
	pinMode(SW_PORT5,INPUT);
	pinMode(SW_PORT6,INPUT);
	pinMode(SW_PORT13,INPUT);

	pullUpDnControl(SW_PORT5,PUD_DOWN);
	pullUpDnControl(SW_PORT6,PUD_DOWN);
	pullUpDnControl(SW_PORT13,PUD_DOWN);

	wiringPiISR(SW_PORT5,INT_EDGE_FALLING,interrupt5);
	wiringPiISR(SW_PORT6,INT_EDGE_FALLING,interrupt5);
	wiringPiISR(SW_PORT13,INT_EDGE_FALLING,interrupt5);


	while(1){
		delay(100);
	}
	return 0;
}