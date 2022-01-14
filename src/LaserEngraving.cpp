#include "../include/LaserEngraving.hpp"
#include "../include/EngravingControl.hpp"
//緊急停止割込み
void EmergencyInterrupt(){
    printf("緊急停止ボタン");
    StateManage &statemanage=StateManage::getInstance();
    delay(20);
    statemanage.TriggerStateSetter(EMERGENCY_SWITCH);
}
//左上アームスイッチ割込み
void LeftUpInterrupt(){
    printf("左上アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    delay(20);
    statemanage.TriggerStateSetter(EMERGENCY_LEFTUP);
}
//左下アームスイッチ割込み
void LeftDownInterrupt(){
    printf("左下アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    delay(20);
    statemanage.TriggerStateSetter(EMERGENCY_LEFTDOWN);
}
//右上アームスイッチ割込み
void RightUpInterrupt(){
    printf("右上アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    delay(20);
    statemanage.TriggerStateSetter(EMERGENCY_RIGHTUP);
}
//右下アームスイッチ割込み
void RightDownInterrupt(){
    printf("右下アームスイッチ");
    StateManage &statemanage=StateManage::getInstance();
    delay(20);
    statemanage.TriggerStateSetter(EMERGENCY_RIGHTDOWN);
}

//コンストラクタ
LaserEngraving::LaserEngraving(){
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

    pwmSetMode(PWM_MODE_MS);
    pwmSetClock(375);
    pwmSetRange(1024);
    pwmWrite(SW_PORT18, 10.24*70);
}
//デストラクタ
LaserEngraving::~LaserEngraving(){}
//実行
int LaserEngraving::Run(char* _filepath){
    //輪郭取得クラス宣言
    InputImage inputimage;
    //彫刻制御クラス宣言
    EngravingControl engravingcontrol;
    //入力画像IpImage型宣言
    IplImage* inputfile;
    //出力画像IpImage型宣言
    IplImage* outputfile;
    std::map<int,std::list<CONTOURData>> contour;
    //初期化
    Init();
    //輪郭データ取得
    inputimage.Input(_filepath,&inputfile);
    inputimage.ImageSizeChange(inputfile,&outputfile);
    inputimage.ImageContour(outputfile);
    cvReleaseImage(&inputfile);
    cvReleaseImage(&outputfile);
    //輪郭の頂点座標取得
    inputimage.ContourGetter(&contour);
    //彫刻制御のRun
    engravingcontrol.Run(contour);
    return 0;
}
int LaserEngraving::Init(){
    //彫刻制御クラス宣言
    EngravingControl engravingcontrol;
    //彫刻制御を停止
    engravingcontrol.Stop();
    return 0;
}
