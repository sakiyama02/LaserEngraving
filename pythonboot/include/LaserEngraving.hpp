#pragma once

//#include "./EngravingControl.hpp"
//opencvのライブラリ取得
#include "./ImageInput.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "./System.hpp"
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include "./src/EngravingControl.cpp"
#include "./src/ImageInput.cpp"
#include "./src/ArmControl.cpp"
#include "./src/BackMotor.cpp"
#include "./src/FrontMotor.cpp"
#include "./src/Laser.cpp"
#include "./src/StateManage.cpp"
#include "./src/SteppingMotor.cpp"
class LaserEngraving {
    public:
        //コンストラクタ
        LaserEngraving();
        //デストラクタ
        ~LaserEngraving();
        //実行
        int Run(char*);
    private:
        //初期化
        int Init();
};
