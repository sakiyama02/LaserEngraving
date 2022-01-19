#include "../include/EngravingControl.hpp"
#include "../include/ArmControl.hpp"
#include "../include/Laser.hpp"
//コンストラクタ
EngravingControl::EngravingControl(){}
//デストラクタ
EngravingControl::~EngravingControl(){}
//実行
int EngravingControl::Run(std::map<int,std::list<CONTOURData>> _contourdata){
    //引数の輪郭データ取得
    contourdata=_contourdata;
    //輪郭データのイテレーターを設定
    contourindex=contourdata.begin();
    coordinatedata=contourindex->second;
    coordinateindex=coordinatedata.begin();
    while(1){
        //最新状態を取得
        statemanage.StateGetter(&movementstate);
        switch(movementstate){
        //準備状態
        case PREPARATION_MODE:
            //待機状態
            //printf("PREPARATION_MODE");
            break;
        //初期化状態
        case INIT_MODE:
            printf("INIT_MODE:START");
            //初期化動作
            InitMove();
            printf("INIT_MODE:END");
            break;
        //通常動作状態
        case NOMAL_MODE:
            //printf("NOMAL_MODE:START");
            //通常動作
            NomalMove();
            //printf("NOMAL_MODE:END");
            break;
        //終了動作状態
        case END_MODE:
            printf("END_MODE:START");
            Stop();
            printf("END_MODE:END");
            return SYS_OK;
            break;
        default:
            break;
        }
    }
}

//初期化動作
int EngravingControl::InitMove(){
    printf("initMove run\n");
    int movementstate=0;
    //アーム制御インスタンス取得
    ArmControl &armcontrol=ArmControl::getInstance();
    Laser &laser=Laser::getInstance();
    laser.init();
    while(1){
        //最新状態を取得
        statemanage.StateGetter(&movementstate);
        if(movementstate==INIT_ARM){
            Stop();
            break;
        }
        if(movementstate==END_MODE){
            return SYS_NG;
        }
        //アーム制御初期化呼び出し
        armcontrol.frontinit(0);
    }
    armcontrol.stop();
    for(int index=0;index<12800;++index){
        armcontrol.frontinit(1);
    }
    
    while(1){
        //printf("syokika2");
        //最新状態を取得
        statemanage.StateGetter(&movementstate);
        if(movementstate==NOMAL_MODE){
            Stop();
            break;
        }
        if(movementstate==END_MODE){
            return SYS_NG;
        }
        //アーム制御初期化呼び出し
        armcontrol.backinit();
    }
    return SYS_OK;
}

//正常動作
int EngravingControl::NomalMove(){
    Laser &laser=Laser::getInstance();
    int duty=80;
    //現在の輪郭の頂点リストを取得し終わったか確認
    if(coordinateindex==coordinatedata.end()){
        //次の輪郭へ移行
        contourindex++;
        //輪郭データの終了確認
        if(contourindex==contourdata.end()){
            //動作終了
            statemanage.StateSetter(END_MODE);
            return SYS_OK;
        }
        //次の輪郭の頂点のリスト取得
        coordinatedata=contourindex->second;
        coordinateindex=coordinatedata.begin();
        
    }
    if(coordinateindex==coordinatedata.begin()){
        //printf("rinkakustart\n");
        //printf("laser on\n");
        laser.stop();
    }else{
        //printf("laser off\n");
        laser.run(duty);
    }
    //アーム制御インスタンス取得
    ArmControl &armcontrol=ArmControl::getInstance();
    //printf("zahyou:%f,%f\n",(double)coordinateindex->x,(double)coordinateindex->y);
    //アームに座標引き渡し
    armcontrol.run((double)coordinateindex->x,(double)coordinateindex->y);
    //次の座標リストへ
    coordinateindex++;
}

//停止
int EngravingControl::Stop(){
    ArmControl &armcontrol=ArmControl::getInstance();
    Laser &laser=Laser::getInstance();
    //レーザー停止
    laser.stop();
    //アーム停止
    armcontrol.stop();
    return SYS_OK;
}
