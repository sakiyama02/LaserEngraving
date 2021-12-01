#include "../include/SteppingMotor.hpp"

SteppingMotor::SteppingMotor(){
}
SteppingMotor::~SteppingMotor(){}

int SteppingMotor::Run(float angle){
    unsigned char data[4];
    int step=0;

    if(angle<0){
        angle=-angle;
        data[0]=0x40;
    }else{
        data[0]=0x41;
    }

    step = (int)(angle/ONE_MICRO_STEP);

    data[1]=((step>>16)&0xff);
    data[2]=((step>>8)&0xff);
    data[3]=((step)&0xff);

    OutputSPI(data,sizeof(data));

    return 1;
}

int SteppingMotor::Init(){
    
    if(wiringPiSPISetup(channel, CLOCK_SPEED) < 0) {
        cout << "wiringPiSPISetup error\n";
        return -1;
    }
    
    unsigned char data1[]={0x05,0x00,0x8A};
    unsigned char data2[]={0x06,0x00,0x8A};
    unsigned char data3[]={0x07,0x00,0x41};
    unsigned char data4[]={0x08,0x00,0x00};
    unsigned char data5[]={0x15,0x00,0x27};
    unsigned char data6[]={0x09,0xFF};
    unsigned char data7[]={0x0A,0xFF};
    unsigned char data8[]={0x0B,0xFF};
    unsigned char data9[]={0x0C,0xFF};
    unsigned char data10[]={0x16,0x07};

    OutputSPI(data1, sizeof(data1));
    OutputSPI(data2, sizeof(data2));
    OutputSPI(data3, sizeof(data3));
    OutputSPI(data4, sizeof(data4));
    OutputSPI(data5, sizeof(data5));
    OutputSPI(data6, sizeof(data6));
    OutputSPI(data7, sizeof(data7));
    OutputSPI(data8, sizeof(data8));
    OutputSPI(data9, sizeof(data9));
    OutputSPI(data10, sizeof(data10));

    return 1;
}

void SteppingMotor::OutputSPI(unsigned char *data, int length){
    unsigned char *pt = data;
    //printf("%d\n",channel);
    for(int i = 0; i < length; i++) {
        wiringPiSPIDataRW(channel, pt++, 1);
        //printf("%x,",*pt++);
    }
}

void SteppingMotor::Stop(){
    unsigned char data[] ={0xb0};
    OutputSPI(data,sizeof(data));
}
