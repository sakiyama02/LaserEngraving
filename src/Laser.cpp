
#include "../include/Laser.hpp"
#include "../include/Device.hpp"

Laser::Laser(){}
Laser::~Laser(){}

int Laser::Init(){
    /*
    if (wiringPiSetupGpio() == -1) {
        return 1;
    }
    pinMode(18, PWM_OUTPUT);
    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(375);
    pwmSetRange(1024);
    */
    return 0;
}

int Laser::Run(int duty){

    //pwmWrite(18, 10.24*duty);
    printf("duty=%d\n",duty);
    return 0;
}

int Laser::Stop(){

    //pwmWrite(18, 10.24*0);
    return 0;
}