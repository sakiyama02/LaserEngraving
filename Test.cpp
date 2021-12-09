#include <wiringPi.h>
#include <stdio.h>
#define SW_PORT5 5
#define SW_PORT6 6
#define SW_PORT13 13

void interrupt5(){
	delay(150);
	if(digitalRead(SW_PORT5)==1){
		printf("hello interrupt5\n");
		printf("status=%d\n",digitalRead(SW_PORT5));
	}else{

	}
}

void interrupt6(){
	delay(150);
	if(digitalRead(SW_PORT6)==1){
		printf("hello interrupt6\n");
		printf("status=%d\n",digitalRead(SW_PORT6));
	}else{

	}
}
void interrupt13(){
	delay(150);
	if(digitalRead(SW_PORT13)==1){
		printf("hello interrupt13\n");
		printf("status=%d\n",digitalRead(SW_PORT13));
	}else{

	}
}

class test{
	public:
	test(){
		
		pinMode(SW_PORT5,INPUT);
		pinMode(SW_PORT6,INPUT);
		pinMode(SW_PORT13,INPUT);

		pullUpDnControl(SW_PORT5,PUD_DOWN);
		pullUpDnControl(SW_PORT6,PUD_DOWN);
		pullUpDnControl(SW_PORT13,PUD_DOWN);

		wiringPiISR(SW_PORT5,INT_EDGE_BOTH,&interrupt5);
		wiringPiISR(SW_PORT6,INT_EDGE_RISING,&interrupt6);
		wiringPiISR(SW_PORT13,INT_EDGE_RISING,&interrupt13);
	}
	~test(){}

};

int main(){
	if(wiringPiSetupGpio() < 0) return 1;
	test a;

	while(1){
		delay(100);
	}
	return 0;
}