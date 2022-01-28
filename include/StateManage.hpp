#pragma once
#define MAIN_EVENT 4
#define TRIGGER_EVENT 5
#include "./System.hpp"
const int state_table[TRIGGER_EVENT][MAIN_EVENT]={
    //準備状態      左下アーム初期化状態  左上アーム初期化状態     正常運転状態    終了状態
    {INIT_MODE,    END_MODE            ,END_MODE               ,END_MODE     ,END_MODE},//緊急停止
    {END_MODE ,    END_MODE            ,NOMAL_MODE             ,END_MODE     ,END_MODE},//アーム(左上)
    {END_MODE ,    INIT_ARM            ,END_MODE               ,END_MODE     ,END_MODE},//アーム(左下)
    {END_MODE ,    END_MODE            ,END_MODE               ,END_MODE     ,END_MODE},//アーム(右上)
    {END_MODE ,    END_MODE            ,END_MODE               ,END_MODE     ,END_MODE},//アーム(右下)
};
class StateManage {
    public:
        //コンストラクタ
        StateManage();
        //デストラクタ
        ~StateManage();
        //状態ゲッター
        int stateGetter(int*);
        //状態セッター
        int stateSetter(int);
        int triggerStateSetter(int);

        //状態クラスシングルトン
        static StateManage& getInstance(){
            static StateManage instance;
            return instance;
        }
    private:
    //現在の状態
        int curent_state=INIT_MODE;
};
