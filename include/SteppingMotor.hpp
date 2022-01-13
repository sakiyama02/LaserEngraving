#pragma once

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


#define SPI_CHANNEL0 0
#define SPI_CHANNEL1 1
#define CLOCK_SPEED 1000000
#define ONE_MICRO_STEP 0.00703125f

class SteppingMotor {
    public:
        SteppingMotor();
        ~SteppingMotor();
        int init();
        int run(float angle);
		int run(int step);
        void stop();
		int getStatus(char* status);
    protected:
        int channel;
    private:
        
        void outputSPI(unsigned char *data, int length);
};
