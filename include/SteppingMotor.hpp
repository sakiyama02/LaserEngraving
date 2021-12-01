#pragma once

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
using namespace std;


#define SPI_CHANNEL0 0
#define SPI_CHANNEL1 1
#define CLOCK_SPEED 1000000
#define ONE_MICRO_STEP 0.00703125f

class SteppingMotor {
    public:
        SteppingMotor();
        ~SteppingMotor();
        int Init();
        int Run(float angle);
        void Stop();
    protected:
        int channel;
    private:
        
        void OutputSPI(unsigned char *data, int length);
};