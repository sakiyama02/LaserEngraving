#pragma once
//opencvのライブラリ取得
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>
#include <list>
#include "System.hpp"
#include "opencv2/imgcodecs.hpp"
using namespace cv;
using namespace std;


//サイズ変更を行いたい数値に変更できる
#define BASIC_WIDTH 200
#define BASIC_HEIGHT 115
#define ARM_COODINATE_WIDTH 80
#define ARM_COODINATE_HEIGHT 70

class InputImage
{
    public:
        //コンストラクタ
        InputImage();
        //デストラクタ
        ~InputImage();
        //画像読み込み
        int imageSizeChange(char*,IplImage**);
        //画像の輪郭抽出
        //IpImege型の画像を送信することで変換した値を返す
        int imageContour(IplImage*);
        int contourGetter(std::map<int,std::list<CONTOUR_DATE>>*);
    private:
        std::map<int,std::list<CONTOUR_DATE>> contour_map;
        //輪郭最外層の頂点取得
        int nextContour(CvSeq *Contour,int Contourcnt,IplImage*);
        //画像のサイズを指定したサイズ二合わせて拡大縮小を行う
        int imageSizeChange(CvSeq *_contour,int _contourcnt, IplImage* _inputimage,CONTOUR_DATE _coordinate);
};
