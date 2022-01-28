#include "../include/LaserEngraving.hpp"
#include "../include/EngravingControl.hpp"
#include "pigpiod_if2.h"
//緊急停止割込み
unsigned int uintTime=0;
unsigned int uintPreTime=0;
void EmergencyInterrupt(){
    uintTime=millis();
    if(500>(uintTime-uintPreTime)){
        uintPreTime=uintTime;
        return;
    }
    uintPreTime=uintTime;
    StateManage &statemanage=StateManage::getInstance();
    statemanage.triggerStateSetter(EMERGENCY_SWITCH);
    return;
}
//左上アームスイッチ割込み
void LeftUpInterrupt(){
    uintTime=millis();    
    if(500>(uintTime-uintPreTime)){
	    uintPreTime=uintTime;
	    return;
    }
    uintPreTime=uintTime;
    printf("左上アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    statemanage.triggerStateSetter(EMERGENCY_LEFTUP);
    return;
}
//左下アームスイッチ割込み
void LeftDownInterrupt(){
    uintTime=millis();    
    if(500>(uintTime-uintPreTime)){
        uintPreTime=uintTime;
        return;
    }
    uintPreTime=uintTime;
    printf("左下アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    statemanage.triggerStateSetter(EMERGENCY_LEFTDOWN);
    return;
}
//右上アームスイッチ割込み
void RightUpInterrupt(){
    uintTime=millis();    
    if(500>(uintTime-uintPreTime)){
	    uintPreTime=uintTime;
	    return;
    }
    uintPreTime=uintTime;
    printf("右上アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    statemanage.triggerStateSetter(EMERGENCY_RIGHTUP);
    return;
}
//右下アームスイッチ割込み
void RightDownInterrupt(){
    uintTime=millis();    
    if(500>(uintTime-uintPreTime)){
        uintPreTime=uintTime;
        return;
    }
    uintPreTime=uintTime;
    printf("右下アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    statemanage.triggerStateSetter(EMERGENCY_RIGHTDOWN);
    return;
}

//コンストラクタ
LaserEngraving::LaserEngraving(){
	uintTime=millis(); 
	if(wiringPiSetupGpio() < 0) return ;
	pinMode(SW_PORT4,INPUT);
	pinMode(SW_PORT5,INPUT);
	pinMode(SW_PORT6,INPUT);
	pinMode(SW_PORT13,INPUT);
	pinMode(SW_PORT18, PWM_OUTPUT);
	pinMode(SW_PORT19,INPUT);

	pullUpDnControl(SW_PORT4,PUD_DOWN);
	pullUpDnControl(SW_PORT5,PUD_DOWN);
	pullUpDnControl(SW_PORT6,PUD_DOWN);
	pullUpDnControl(SW_PORT13,PUD_DOWN);
	pullUpDnControl(SW_PORT19,PUD_DOWN);

	wiringPiISR(SW_PORT4,INT_EDGE_RISING,EmergencyInterrupt);
	wiringPiISR(SW_PORT5,INT_EDGE_RISING,LeftUpInterrupt);
	wiringPiISR(SW_PORT6,INT_EDGE_RISING,LeftDownInterrupt);
	wiringPiISR(SW_PORT13,INT_EDGE_RISING,RightUpInterrupt);
	wiringPiISR(SW_PORT19,INT_EDGE_RISING,RightDownInterrupt);
}
//デストラクタ
LaserEngraving::~LaserEngraving(){}
//実行
int LaserEngraving::run(char* _filepath){
    //輪郭取得クラス宣言
    InputImage inputimage;
    //彫刻制御クラス宣言
    EngravingControl engravingcontrol;
    //入力画像IpImage型宣言
    IplImage* inputfile;
    //輪郭情報格納用
    std::map<int,std::list<CONTOUR_DATE>> contour;
    //初期化
    init();
    //輪郭データ取得
    inputimage.input(_filepath,&inputfile);
    //輪郭取得
    inputimage.imageContour(inputfile);

    cvReleaseImage(&inputfile);

    //輪郭の頂点座標取得
    inputimage.contourGetter(&contour);
    //彫刻制御のrun
    engravingcontrol.run(contour);
    return SYS_OK;
}
int LaserEngraving::init(){
    //彫刻制御クラス宣言
    EngravingControl engravingcontrol;
    //彫刻制御を停止
    engravingcontrol.stop();
    return SYS_OK;
}
