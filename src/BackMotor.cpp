#include "../include/BackMotor.hpp"

BackMotor::BackMotor(){
    channel=SPI_CHANNEL1;
    cout<<"BackMotor Constructor\n";
}

BackMotor::~BackMotor(){};
