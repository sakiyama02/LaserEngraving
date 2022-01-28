#include "../include/StateManage.hpp"
//コンストラクタ
StateManage::StateManage(){}
//デストラクタ
StateManage::~StateManage(){}
//状態取得
int StateManage::stateGetter(int* _inputstate){
    memcpy(_inputstate,&curent_state,sizeof(int));
    return SYS_OK;
}
//状態更新
int StateManage::stateSetter(int _inputstate){
    curent_state=_inputstate;
    return SYS_OK;
}
int StateManage::triggerStateSetter(int _inputstate){
    curent_state=state_table[_inputstate][curent_state];
    return SYS_OK;
}
