#include "../include/FrontMotor.hpp"

FrontMotor::FrontMotor(){
    channel=SPI_CHANNEL0;
    cout<<"FrontMotor Constructor\n";
}

FrontMotor::~FrontMotor(){}