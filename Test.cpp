#include <wiringPi.h>
#include <stdio.h>
#define SW_PORT 17

void interrupt(){
	delay(10);
	printf("hello interrupt\n");
	while( digitalRead(SW_PORT) == 0){
		
	}

	printf("Bye interrupt\n");
	delay(10);
}

int main(){
	if(wiringPiSetupGpio() < 0) return 1;
	pinMode(SW_PORT,INPUT);
	pullUpDnControl(SW_PORT,PUD_UP);
	wiringPiISR(SW_PORT,INT_EDGE_FALLING,interrupt);

	while(1){
		delay(100);
	}

	return 0;
}