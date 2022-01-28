#include "../include/ImageInput.hpp"
#include <string>
//コンストラクタ
InputImage::InputImage(){}
//デストラクタ
InputImage::~InputImage(){}
//画像読み込み
int InputImage::input(char* _FilePath,IplImage** _inputfile){
    if(_FilePath==NULL){
        return SYS_PARAM;
    }
    //画像データの読込（グレースケールで読込）
    //opencv上のエラーで処理の停止を防ぐ
    try{
        *_inputfile = cvLoadImage((const char*)_FilePath, CV_LOAD_IMAGE_GRAYSCALE);
    }catch(cv::Exception& e){
        printf("cvLoadImage:opencv上でエラーが発生");
        return SYS_NG;
    }

    return SYS_OK;
}

//画像のサイズ変更
int InputImage::imageSizeChange(CvSeq *_contour,int _contourcnt, IplImage* _inputimage,CONTOUR_DATE* _coordinate ){
    double calcNum=0;
    double calcLargeNum=0;
    double calcSmallNum=0;
    //CvPointは構造体で(int x,int y)という構造をしている
    //CV_GET_SEQ_ELEM内では第三引数で指定下CvSeq内に格納された輪郭座標(CvPoint)を抜き出す役割をしている
	CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, _contour,_contourcnt);
    
	if(_inputimage->width<_inputimage->height){
        calcLargeNum=(double)_inputimage->height/BASIC_WIDTH;
        calcSmallNum=(double)_inputimage->width/BASIC_HEIGHT;
        if(calcLargeNum<calcSmallNum){
            calcNum=calcSmallNum;
        }else{
            calcNum=calcLargeNum;
        }
	}else{
        calcLargeNum=(double)_inputimage->width/BASIC_WIDTH;
        calcSmallNum=(double)_inputimage->height/BASIC_HEIGHT;
        if(calcLargeNum<calcSmallNum){
            calcNum=calcSmallNum;
        }else{
            calcNum=calcLargeNum;
        }
	}

	_coordinate->x=((double)point->x/calcNum);
	_coordinate->y=((double)point->y/calcNum);

    if(_coordinate->x>BASIC_WIDTH||_coordinate->y>BASIC_HEIGHT){
        _coordinate->x=BASIC_WIDTH;
        _coordinate->y=BASIC_HEIGHT;
    }
	_coordinate->x=_coordinate->x-ARM_COODINATE_WIDTH;
	_coordinate->y=_coordinate->y+ARM_COODINATE_HEIGHT;

    return SYS_OK;
}

//輪郭抽出
int InputImage::imageContour(IplImage* _inputimage){
    if(_inputimage == NULL){
        return SYS_PARAM;
    }
    IplImage* outputfile;
    CvSeq *firstcontours = NULL;
    CvMemStorage *storage = cvCreateMemStorage (0);
    //白黒に二値化を行う
    cvAdaptiveThreshold (_inputimage, _inputimage,  255, CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,17,13);
    //輪郭取得
    cvFindContours(_inputimage,storage,&firstcontours,sizeof (CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    if (firstcontours != NULL){
        //輪郭の描画
        nextContour( firstcontours, 1,_inputimage);
    }
    //メモリストレージの解放
    cvClearSeq(firstcontours);
    cvReleaseMemStorage (&storage);
    return SYS_OK;
}

//輪郭の最外層
int InputImage::nextContour(CvSeq *_contour,int _contourcnt,IplImage* _inputimage)
{
    std::list<CONTOUR_DATE> list_temp;
    CONTOUR_DATE coordinate;
	//輪郭を構成する頂点座標を取得
	for ( int index = 0; index < _contour->total;index++){
	    imageSizeChange(_contour, index,_inputimage, &coordinate);
	    list_temp.push_back(coordinate);
	}
	contour_map[_contourcnt]=list_temp;
	if (_contour->h_next != NULL){
	    //次の輪郭がある場合は次の輪郭をmap型に格納
	    nextContour(_contour->h_next, _contourcnt+1,_inputimage);
	}
    return SYS_OK;
}

int InputImage::contourGetter(std::map<int,std::list<CONTOUR_DATE>>* _contour_date){
    _contour_date->insert(contour_map.begin(),contour_map.end());
    return SYS_OK;
}
