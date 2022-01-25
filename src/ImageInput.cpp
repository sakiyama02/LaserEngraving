#include "../include/ImageInput.hpp"
#include <string>
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
    //cvShowImage ("src", *inputfile);
        cvWaitKey (0);

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
	cvShowImage("dst",*_outputimage);
	cvWaitKey(0);

    return 0;
}

//輪郭抽出
int InputImage::ImageContour(IplImage* _inputimage){
    if(_inputimage == NULL){
        return -2;
    }
        Mat img=cvarrToMat(_inputimage);
    
	copyMakeBorder(img,img,20*(_inputimage->height/200),20*(_inputimage->height/200),20*(_inputimage->width/400),20*(_inputimage->width/400),BORDER_CONSTANT,0);
	IplImage iplImage1 = img;
	_inputimage=&iplImage1;
    cvShowImage ("src", _inputimage);

    cvWaitKey(0);
    CvSeq *firstcontours = NULL;
    CvMemStorage *storage = cvCreateMemStorage (0);
    //輪郭データ取得
    cvAdaptiveThreshold (_inputimage, _inputimage,  255, CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY,17,13);
    //cvThreshold (_inputimage, _inputimage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    int allcontourcnt = cvFindContours(_inputimage,storage,&firstcontours,sizeof (CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    if (firstcontours != NULL){
	//輪郭の描画
	NextContour( firstcontours, 1,_inputimage);
    }
    //メモリストレージの解放
	cvReleaseMemStorage (&storage);
    return 0;
}

//輪郭の最外層
int InputImage::NextContour(CvSeq *Contour,int Contourcnt,IplImage* _inputimage)
{
    std::list<CONTOURData> listtemp;
    CONTOURData structdata;
    double temp=0;
    double temp1=0;
    double temp2=0;
    //writing_file.open(filename, std::ios::out);
	//輪郭を構成する頂点座標を取得
	for ( int index = 0; index < Contour->total;index++){
	    CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, Contour,index);
	    //printf("%d\n",point->y);
	    if(_inputimage->width<_inputimage->height){
		temp1=(double)_inputimage->height/BASICWIDTH;
		temp2=(double)_inputimage->width/BASICHEIGHT;
		if(temp1<temp2){
		    temp=temp2;
		}else{temp=temp1;}
	    }else{
            temp1=(double)_inputimage->width/BASICWIDTH;
            temp2=(double)_inputimage->height/BASICHEIGHT;
		if(temp1<temp2){
		    temp=temp2;
		}else{temp=temp1;}
	    }
	    //printf("%d,%d\n",_inputimage->width,_inputimage->height)
	    //printf("temp:%lf,temp1:%lf,temp2:%lf\n",temp,temp1,temp2);
	    structdata.x=((double)point->x/temp);
	    structdata.y=((double)point->y/temp);
        if(structdata.x>BASICWIDTH||structdata.y>BASICHEIGHT){
	        //printf("rinkakusu%d\n",Contourcnt);
		printf("zahyou:x%lf,y%lf\n",structdata.x,structdata.y);
		structdata.x=BASICWIDTH;
		structdata.y=BASICHEIGHT;
        }
	    structdata.x=structdata.x-80;
	    structdata.y=structdata.y+70.2;
	   // printf("zahyou:x%lf,y%lf\n",structdata.x,structdata.y);
	    listtemp.push_back(structdata);
	}
	//printf("rinkaku:%d\n",Contourcnt);
	mp[Contourcnt]=listtemp;
	if (Contour->h_next != NULL){
	    //次の輪郭がある場合は次の輪郭を描画
	    NextContour(Contour->h_next, Contourcnt+1,_inputimage);
	}
    return 0;
}

int InputImage::ContourGetter(std::map<int,std::list<CONTOURData>>* _CONTOURData){
    _CONTOURData->insert(mp.begin(),mp.end());
    return SYS_OK;
}
