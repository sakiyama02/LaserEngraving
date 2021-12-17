#include "../include/ArmControl.hpp"
#include "../include/FrontMotor.hpp"
#include "../include/BackMotor.hpp"
#include <math.h>

ArmControl::ArmControl(){
	length.l0=100;
	length.l1=100;
	deg.deg0=0;
	deg.deg1=0;
	BackMotor &bMotor  = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	bMotor.init();
	fMotor.init();
}

ArmControl::~ArmControl(){}
int ArmControl::stop(){
	BackMotor &bMotor  = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	bMotor.stop();
	fMotor.stop();
	return 1;
}
int ArmControl::init(){
	return 1;
}
int ArmControl::run(double x,double y){
	BackMotor &bMotor  = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	POS pos;
	pos.x=x;
	pos.y=y;
	// 逆運動学で座標から各ラジアンを取得
	TH t=calc(pos);
	// ラジアンから角度に変換
	double degree0 = t.th0 * 180.0 / PI;
	double degree1 = t.th1 * 180.0 / PI;
	
	printf("%f,%f\n",degree0,degree1);

	// 指定した角度に回転させる
	printf("Back=");
	bMotor.run(degree0-deg.deg0);
	printf("Front=");
	fMotor.run(degree1-deg.deg1);
	//printf("_%f,_%f\n",degree0-deg.deg0,degree1-deg.deg1);
	deg.deg0=degree0;
	deg.deg1=degree1;
	char bStatus[2];
	char fStatus[2];

	// 両方のモータが止まるまで待つ

	do{
		bMotor.getStatus(bStatus);
		fMotor.getStatus(fStatus);
		delay(100);
		printf("bSta=%x,fSta=%x",(bStatus[1]),(fStatus[1]));
	}while((bStatus[1]&0x60)||(fStatus[1]&0x60));
	
	//delay(15000);
	printf("MotorStop\n");
	return 1;
}

TH ArmControl::calc(POS pos){
	double x = pos.x;
	double y = pos.y;
	double l0 = length.l0;
	double l1 = length.l1;

	double norm = sqrt((pos.x*pos.x)+(pos.y*pos.y));

	TH T;
	T.th0=atan2(y , x) + acos(((x * x) +(y * y)+(l0*l0)- (l1*l1)) / (2*l0*norm));
	T.th1 = -T.th0 + atan2((y-l0*sin(T.th0)),(x-l0*cos(T.th0)));
	
	return T;
}
