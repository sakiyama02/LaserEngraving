#pragma once
#define SYS_OK 0    //正常終了
#define SYS_NG 1    //異常終了
#define SYS_PARAM 2 //引数エラー
#include "./StateManage.hpp"
//opencvのライブラリ取得
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "System.hpp"
#include <iostream>
#include <map>
#include <wiringPi.h>
#include <stdio.h>
#include <list>
class EngravingControl {
    public:
        //コンストラクタ
        EngravingControl();
        //デストラクタ
        ~EngravingControl();
        //初期化動作
        int InitMove();
        //通常動作
        int NomalMove();
        //実行
        int Run(std::map<int,std::list<CONTOURData>>);
        //停止
        int Stop();
    private:
        //状態管理インスタンス取得
        StateManage &statemanage=StateManage::getInstance();
        int movementstate=0;
        //すべての輪郭のリスト情報
        std::map<int,std::list<CONTOURData>> contourdata;
        //頂点のリスト情報
        std::list<CONTOURData> coordinatedata;
        //すべての輪郭のリスト情報の索引
        std::map<int,std::list<CONTOURData>>::iterator contourindex;
        //頂点座標リスト情報の索引
        std::list<CONTOURData>::iterator coordinateindex;
};
