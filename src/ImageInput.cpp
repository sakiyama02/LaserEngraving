#include "../include/ImageInput.hpp"
//コンストラクタ
InputImage::InputImage(){}
//デストラクタ
InputImage::~InputImage(){}
//画像読み込み
int InputImage::Input(char* _FilePath,IplImage** inputfile){
    if(_FilePath==NULL){
        return -2;
    }
    //画像データの読込（グレースケールで読込）
    //opencv上のエラーで処理の停止を防ぐ
    try{
        *inputfile = cvLoadImage((const char*)_FilePath, CV_LOAD_IMAGE_GRAYSCALE);
    }catch(cv::Exception& e){
        printf("cvLoadImage:opencv上でエラーが発生");
        return -1;
    }
    return 0;
}

//画像のサイズ変更
int InputImage::ImageSizeChange(IplImage* _inputimage,IplImage** _outputimage){
    float rewidth=_inputimage->width;
    float reheight=_inputimage->height;

    rewidth=BASICWIDTH/rewidth;
    reheight=BASICHEIGHT/reheight;
    //opencv上のエラーで処理の停止を防ぐ
    try{
        *_outputimage = cvCreateImage(cvSize((int)_inputimage->width*rewidth,(int)_inputimage->height*reheight),_inputimage->depth,1);
        cvResize(_inputimage, *_outputimage, CV_INTER_LINEAR);
    }catch(cv::Exception& e){
        printf("cvCreateImage,cvResize:opencv上でエラーが発生");
        return -1;
    }

    return 0;
}

//輪郭抽出
int InputImage::ImageContour(IplImage* _inputimage){
    if(_inputimage == NULL){
        return -2;
    }
    CvSeq *firstcontours = NULL;
    CvMemStorage *storage = cvCreateMemStorage (0);
    //輪郭データ取得
    cvThreshold (_inputimage, _inputimage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    int allcontourcnt = cvFindContours(_inputimage,storage,&firstcontours,sizeof (CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_SIMPLE);

    if (firstcontours != NULL){
	//輪郭の描画
	NextContour( firstcontours, 1);
    }
    //メモリストレージの解放
	cvReleaseMemStorage (&storage);
}

//輪郭の最外層
int InputImage::NextContour(CvSeq *Contour,int Contourcnt)
{
    std::list<CONTOURData> listtemp;
    CONTOURData structdata;
	//輪郭を構成する頂点座標を取得
	for ( int index = 0; index < Contour->total;index++){
	    CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, Contour,index);
	    structdata.x=point->x;
	    structdata.y=point->y;
	    listtemp.push_back(structdata);
	}
	mp[Contourcnt]=listtemp;
	if (Contour->h_next != NULL){
	    //次の輪郭がある場合は次の輪郭を描画
	    NextContour(Contour->h_next, Contourcnt+1);
	}
    return 0;
}

int InputImage::ContourGetter(std::map<int,std::list<CONTOURData>>* _CONTOURData){
    _CONTOURData->insert(mp.begin(),mp.end());
    return SYS_OK;
}
