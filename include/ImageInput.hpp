#pragma once
/* ------------------------------------------------------------------------- */
/* ImageInput.hpp															 */
/* 画像取得のクラス					    　 								 	   */
/* 																			 */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* 番号		更新履歴								日付		氏名		   */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2022/01/29	渡部 湧也  	  */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#include "System.hpp"
//opencvのライブラリ取得
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <map>
#include <list>
/* ------------------------------------------------------------------------- */
/* using宣言																 */
/* ------------------------------------------------------------------------- */
using namespace cv;
using namespace std;
/* ------------------------------------------------------------------------- */
/* define宣言																 */
/* ------------------------------------------------------------------------- */
#define BASIC_WIDTH 200
#define BASIC_HEIGHT 115
#define ARM_COODINATE_WIDTH 100
#define ARM_COODINATE_HEIGHT 70
/* ------------------------------------------------------------------------- */
/* class宣言																 */
/* ------------------------------------------------------------------------- */
class InputImage
{
    public:
        //コンストラクタ
        InputImage();
        //デストラクタ
        ~InputImage();
        //画像読み込み
        int input(char*,IplImage**);
        //画像の輪郭抽出
        //IpImege型の画像を送信することで変換した値を返す
        int imageContour(IplImage*);
        int contourGetter(std::map<int,std::list<CONTOUR_DATE>>*);
    private:
        std::map<int,std::list<CONTOUR_DATE>> contour_map;
        //輪郭最外層の頂点取得
        int nextContour(CvSeq *Contour,int Contourcnt,IplImage*);
        //画像のサイズを指定したサイズ二合わせて拡大縮小を行う
        int imageSizeChange(CvSeq *_contour,int _contourcnt, IplImage* _inputimage,CONTOUR_DATE* _coordinate);
};

/* ------------------------------------------------------------------------- */
/*				Copyright HAL College of Technology & Design				 */
/* ------------------------------------------------------------------------- */