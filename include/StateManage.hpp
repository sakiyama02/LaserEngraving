#pragma once

#include "./System.hpp"
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

        //状態クラスシングルトン
        static StateManage& getInstance(){
            static StateManage instance;
            return instance;
        }
    private:
    //現在の状態
        int curentstate=PREPARATION_MODE;
};
