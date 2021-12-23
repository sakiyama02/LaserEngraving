#include <wiringPi.h>
#include <stdio.h>
#define SW_PORT4 4
#define SW_PORT5 5
#define SW_PORT6 6
#define SW_PORT13 13
#define SW_PORT19 19

void interrupt4(){
    delay(20);
    printf("4\n");
}

void interrupt5(){
    delay(20);
    printf("5\n");
}
void interrupt6(){
    delay(20);
    printf("6\n");
}
void interrupt13(){
    delay(20);
    printf("13\n");
}
void interrupt19(){
    delay(20);
    printf("19\n");
}

int main(){
	/*
	if(wiringPiSetupGpio() < 0) return 1;
	pinMode(SW_PORT4,INPUT);
	pinMode(SW_PORT5,INPUT);
	pinMode(SW_PORT6,INPUT);
	pinMode(SW_PORT13,INPUT);
	pinMode(SW_PORT19,INPUT);

	pullUpDnControl(SW_PORT4,PUD_DOWN);
	pullUpDnControl(SW_PORT5,PUD_DOWN);
	pullUpDnControl(SW_PORT6,PUD_DOWN);
	pullUpDnControl(SW_PORT13,PUD_DOWN);
	pullUpDnControl(SW_PORT19,PUD_DOWN);

	wiringPiISR(SW_PORT4,INT_EDGE_RISING,interrupt4);
	wiringPiISR(SW_PORT5,INT_EDGE_RISING,interrupt5);
	wiringPiISR(SW_PORT6,INT_EDGE_RISING,interrupt6);
	wiringPiISR(SW_PORT13,INT_EDGE_RISING,interrupt13);
	wiringPiISR(SW_PORT19,INT_EDGE_RISING,interrupt19);

	while(1){
		// if(digitalRead(SW_PORT5) == 0){
     		// 	printf("interrupt5\n");
  	//		delay(10);
   	//	 }
		delay(100);
	}
	*/
    if (wiringPiSetupGpio() == -1) {
	return 1;
    }
    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(375);
    pwmSetRange(1024);
    
    
    pwmWrite(18, 10.24*70);
    while(1){
    delay(5000);
}
    pwmWrite(18, 10.24*0);
    
	return 0;
}
