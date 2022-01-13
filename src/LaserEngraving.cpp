#include "../include/LaserEngraving.hpp"
#include "../include/EngravingControl.hpp"
//コンストラクタ
LaserEngraving::LaserEngraving(){
    if(wiringPiSetupGpio() < 0) return 1;
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

	wiringPiISR(SW_PORT4,INT_EDGE_RISING,interrupt4);
	wiringPiISR(SW_PORT5,INT_EDGE_RISING,interrupt5);
	wiringPiISR(SW_PORT6,INT_EDGE_RISING,interrupt6);
	wiringPiISR(SW_PORT13,INT_EDGE_RISING,interrupt13);
	wiringPiISR(SW_PORT19,INT_EDGE_RISING,interrupt19);

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
    Inpu@tImage inputimage;
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
    //engravingcontrol.Stop();
    return 0;
}
