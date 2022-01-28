#pragma once

//#include "./EngravingControl.hpp"
//opencvのライブラリ取得
#include "./ImageInput.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "./System.hpp"
class LaserEngraving {
    public:
        //コンストラクタ
        LaserEngraving();
        //デストラクタ
        ~LaserEngraving();
        //実行
        int run(char*);
    private:
        //初期化
        int init();
};
