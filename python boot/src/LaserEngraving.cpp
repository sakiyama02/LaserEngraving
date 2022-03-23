#include "../include/LaserEngraving.hpp"
//コンストラクタ
LaserEngraving::LaserEngraving(){}
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
    //engravingcontrol.Stop();
    return 0;
}
