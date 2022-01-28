#include "../include/EngravingControl.hpp"
#include "../include/ArmControl.hpp"
#include "../include/Laser.hpp"
//コンストラクタ
EngravingControl::EngravingControl(){}
//デストラクタ
EngravingControl::~EngravingControl(){}
//実行
int EngravingControl::run(std::map<int,std::list<CONTOUR_DATE>> _contour_data){
    //引数の輪郭データ取得
    contour_date=_contour_data;
    //輪郭データのイテレーターを設定
    contour_index=contour_date.begin();
    coordinate_data=contour_index->second;
    coordinate_index=coordinate_data.begin();
    while(1){
        //最新状態を取得
        statemanage.stateGetter(&movement_state);
        switch(movement_state){
        //準備状態
        case PREPARATION_MODE:
            //待機状態
            break;
        //初期化状態
        case INIT_MODE:
            printf("INIT_MODE:START\n");
            //初期化動作
            initMove();
            printf("INIT_MODE:END\n");
            printf("NOMAL_MODE:START");
            break;
        //通常動作状態
        case NOMAL_MODE:
            //通常動作
            nomalMove();
            break;
        //終了動作状態
        case END_MODE:
            printf("NOMAL_MODE:END");
            printf("END_MODE:START\n");
            stop();
            printf("END_MODE:END\n");
            return SYS_OK;
            break;
        default:
            break;
        }
    }
    return SYS_OK;
}

//初期化動作
int EngravingControl::initMove(){
    printf("initMove run\n");
    //アーム制御インスタンス取得
    ArmControl &armcontrol = ArmControl::getInstance();
    Laser &laser=Laser::getInstance();
    laser.init();
    stop();
    while(1){
        //最新状態を取得
        statemanage.stateGetter(&movement_state);
        if(movement_state==INIT_ARM){
            stop();
            break;
        }
        if(movement_state==END_MODE){
            return SYS_NG;
        }
        //アーム制御初期化呼び出し
        armcontrol.frontInit(LEFT_ROTATE);
    }
    armcontrol.stop();
    // 140 do
    for(int index=0;index<ARM_INIT_ANGLE_140;++index){
        armcontrol.frontInit(RIGHT_ROTATE);
    }
    
    while(1){
        //printf("syokika2");
        //最新状態を取得
        statemanage.stateGetter(&movement_state);
        if(movement_state==NOMAL_MODE){
            stop();
            break;
        }
        if(movement_state==END_MODE){
            return SYS_OK;
        }
        //アーム制御初期化呼び出し
        armcontrol.backInit(LEFT_ROTATE);
    }
    // 25 do
    for(int index=0;index<ARM_INIT_ANGLE_25;++index){
        armcontrol.backInit(RIGHT_ROTATE);
    }
    return SYS_OK;
}

//正常動作
int EngravingControl::nomalMove(){
    Laser &laser=Laser::getInstance();
    //現在の輪郭の頂点リストを取得し終わったか確認
    if(coordinate_index==coordinate_data.end()){
        //次の輪郭へ移行
        contour_index++;
        //輪郭データの終了確認
        if(contour_index==contour_date.end()){
            //動作終了
            statemanage.stateSetter(END_MODE);
            return SYS_OK;
        }
        //次の輪郭の頂点のリスト取得
        coordinate_data=contour_index->second;
        coordinate_index=coordinate_data.begin();
        
    }
    if(coordinate_index==coordinate_data.begin()){
        laser.stop();
    }else{
        laser.run(DUTY_RATIO_RUN);
    }
    //アーム制御インスタンス取得
    ArmControl &armcontrol=ArmControl::getInstance();
    //アームに座標引き渡し
    armcontrol.run((double)coordinate_index->x,(double)coordinate_index->y);
    //次の座標リストへ
    coordinate_index++;
    return SYS_OK;
}

//停止
int EngravingControl::stop(){
    ArmControl &armcontrol=ArmControl::getInstance();
    Laser &laser=Laser::getInstance();
    //レーザー停止
    laser.stop();
    //アーム停止
    armcontrol.stop();
    return SYS_OK;
}
