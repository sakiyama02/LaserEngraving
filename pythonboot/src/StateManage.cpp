#include "../include/StateManage.hpp"
//コンストラクタ
StateManage::StateManage(){}
//デストラクタ
StateManage::~StateManage(){}
//状態取得
int StateManage::StateGetter(int* _inputstate){
    memcpy(_inputstate,&curentstate,sizeof(int));
    return SYS_OK;
}
//状態更新
int StateManage::StateSetter(int _inputstate){
    curentstate=_inputstate;
    return SYS_OK;
}
int StateManage::TriggerStateSetter(int _inputstate){
    curentstate=statetable[_inputstate][curentstate];
    printf("State:%d\n",curentstate);
    return SYS_OK;
}
