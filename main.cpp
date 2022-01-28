#include "include/BackMotor.hpp"
#include "include/FrontMotor.hpp"
#include "include/LaserEngraving.hpp"
//#include "include/Device.hpp"
#include "include/Laser.hpp"
#include <math.h>
#include <iostream>
using namespace std;
/*
#define PI 3.141592653589793
typedef struct th{
	double th0;
	double th1;
}th;

typedef struct length{
	double l0;
	double l1;
}length;

typedef struct pos{
	double x;
	double y;
}pos;

th arm_th(length L,pos P){
	double x=P.x;
	double y=P.y;
	double l0=L.l0;
	double l1=L.l1;

	double norm = sqrt((x*x)+(y*y));

	th T;
	T.th0=atan2(y , x) + acos(((x * x) +(y * y)+(l0*l0)- (l1*l1)) / (2*l0*norm));
	T.th1 = -T.th0 + atan2((y-l0*sin(T.th0)),(x-l0*cos(T.th0)));
	
	return T;
}
*/
#include "include/ArmControl.hpp"

int main(){
    LaserEngraving laserengraving;
    char* filepath="EWsuIVjVcAAzWh7.jpg";
    laserengraving.run(filepath);
    
    /*
    Laser &laser=Laser::getInstance();
    ArmControl &armcontrol=ArmControl::getInstance();
    laser.init();
    delay(1000);
    double inputX,inputY;
    //cout << "X=";
    //cin >> inputX;
    //cout << "Y=";
    //cin >> inputY;
    inputX=80;
    inputY=80;
    //アームに座標引き渡し
    armcontrol.run(inputX,inputY);

   // delay(10000);
   for(int i=0;i<3;i++){
    laser.run(80);
    for(double i=0; i<= 70;i+=0.5){
	armcontrol.run(inputX,inputY+i);
	//delay(1000);
    }
    
    for(double i=0; i<= 70;i+=0.5){
	armcontrol.run(inputX-i,inputY+70);
	//delay(1000);
    }
    
    for(double i=0; i<= 70;i+=0.5){
	armcontrol.run(inputX-70,inputY+70-i);
	//delay(1000);
    }
    
    for(double i=70; i >= 0;i-=0.5){
	armcontrol.run(inputX-i,inputY);
	//delay(1000);
    }
   laser.stop();
   delay(1000);
}
    return 0;
    /*
    BackMotor& backMotor=BackMotor::getInstance();
    backMotor.Init();
    FrontMotor& frontMotor=FrontMotor::getInstance();
    frontMotor.Init();
    backMotor.Stop();
    frontMotor.Stop();

    while(1){
   backMotor.Run(100);
  frontMotor.Run(100);
    delay(1000);
    }
    */

    //Device* laser=new Laser;
    //laser->Run(30);

	/*
	length L={1,1};
	float max=((L.l0+L.l1)/sqrt(2));
	float min=-((L.l0/L.l1)/sqrt(2));
	pos P={0.09,1.39};

	th T=arm_th(L,P);
	double degree0 = T.th0 * 180.0 / PI;
	double degree1 = T.th1 * 180.0 / PI;
	printf("th0=%.16f,th1=%.16f\n",T.th0,T.th1);
	printf("th0=%.16f,th1=%.16f\n",degree0,degree1);
	*/


    //return 0;
}
