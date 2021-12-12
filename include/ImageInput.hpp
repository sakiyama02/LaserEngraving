#pragma once
//opencvのライブラリ取得
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>
#include <list>
#include "System.hpp"
using namespace std;


//サイズ変更を行いたい数値に変更できる
#define BASICWIDTH 100
#define BASICHEIGHT 100
class InputImage
{
    public:
        //コンストラクタ
        InputImage();
        //デストラクタ
        ~InputImage();
        //画像読み込み
        int Input(char*,IplImage**);
        //画像サイズ変換
        //画像のサイズを指定したサイズ二合わせて拡大縮小を行う
        int ImageSizeChange(IplImage*,IplImage**);
        //画像の輪郭抽出
        //IpImege型の画像を送信することで変換した値を返す
        int ImageContour(IplImage*);
        int ContourGetter(std::map<int,std::list<CONTOURData>>*);
    private:
        std::map<int,std::list<CONTOURData>> mp;
        //輪郭最外層の頂点取得
        int NextContour(CvSeq *Contour,int Contourcnt);

};
