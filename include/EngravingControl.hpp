#pragma once

#define ARM_INIT_ANGLE_140 19750
#define ARM_INIT_ANGLE_25 2844
#define DUTY_RATIO_RUN 80
#define DUTY_RATIO_STOP 0
#define LEFT_ROTATE 0
#define RIGHT_ROTATE 1
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
        int initMove();
        //通常動作
        int nomalMove();
        //実行
        int run(std::map<int,std::list<CONTOUR_DATE>>);
        //停止
        int stop();
    private:
        //状態管理インスタンス取得
        StateManage &statemanage=StateManage::getInstance();
        int movement_state=0;
        //すべての輪郭のリスト情報
        std::map<int,std::list<CONTOUR_DATE>> contour_date;
        //頂点のリスト情報
        std::list<CONTOUR_DATE> coordinate_data;
        //すべての輪郭のリスト情報の索引
        std::map<int,std::list<CONTOUR_DATE>>::iterator contour_index;
        //頂点座標リスト情報の索引
        std::list<CONTOUR_DATE>::iterator coordinate_index;
};
