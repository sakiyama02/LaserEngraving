#pragma once
#define MAIN_EVENT 3
#define TRIGGER_EVENT 5
#include "./System.hpp"
int statetable[TRIGGER_EVENT][MAIN_EVENT]={
    //準備状態      初期化状態       正常運転状態 
    {INIT_MODE,    END_MODE        ,END_MODE},//緊急停止
    {END_MODE ,    INIT_MODE       ,END_MODE},//アーム(左上)
    {END_MODE ,    NOMAL_MODE      ,END_MODE},//アーム(左下)
    {END_MODE ,    END_MODE        ,END_MODE},//アーム(右上)
    {END_MODE ,    END_MODE        ,END_MODE},//アーム(右下)
};
class StateManage {
    public:
        //コンストラクタ
        StateManage();
        //デストラクタ
        ~StateManage();
        //状態ゲッター
        int StateGetter(int*);
        //状態セッター
        int StateSetter(int);
        int TriggerStateSetter(int);

        //状態クラスシングルトン
        static StateManage& getInstance(){
            static StateManage instance;
            return instance;
        }
    private:
    //現在の状態
        int curentstate=PREPARATION_MODE;
};
