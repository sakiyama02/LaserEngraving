#include "../include/EngravingControl.hpp"
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
             statemanage.StateSetter(NOMAL_MODE);           
            break;
        //初期化状態
        case INIT_MODE:
            //初期化動作
            InitMove();
            break;
        //通常動作状態
        case NOMAL_MODE:
            //通常動作
            NomalMove();
            break;
        //緊急停止状態
        //アーム上の緊急停止スイッチ*4
        case EMERGENCY_LEFTUP:
        case EMERGENCY_LEFTDOWN:
        case EMERGENCY_RIGHTUP:
        case EMERGENCY_RIGHTDOWN:
        //ドア緊急停止スイッチ
        case EMERGENCY_DOOR:
        //緊急ボタン
        case EMERGENCY_SWITCH:
            statemanage.StateSetter(END_MODE);
            break;
        case END_MODE:
            Stop();
            return SYS_OK;
            break;
        default:break;
        }
    }
}

//初期化動作
int EngravingControl::InitMove(){
    int state=0;
    //アーム制御インスタンス取得
    //ArmMotor &armmotor=ArmMotor::getInstance();
    //アーム制御初期化呼び出し
    //armmotor.init();
    state=statemanage.StateGetter(&movementstate);
    if(state==NOMAL_MODE){
        return SYS_OK;
    }else{
        //異常終了しているためエラーコードを返す
        return -1;
    }
}

//正常動作
int EngravingControl::NomalMove(){
    //Laser laser;
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
        //laser.Stop();
    }else{
        //laser.Run();
    }
    //アーム制御インスタンス取得
    //ArmMotor &armmotor=ArmMotor::getInstance();

    //アームに座標引き渡し
    //armmotor.Run(coordinateindex->x,coordinateindex->y);
    //次の座標リストへ
    coordinateindex++;
}

//停止
int EngravingControl::Stop(){
    //ArmMotor &armmotor=ArmMotor::getInstance();
    //Laser laser;
    //レーザー停止
    //laser.Stop();
    //アーム停止
    //armmotor.Stop();
    statemanage.StateGetter(&movementstate);
    return SYS_OK;
}
