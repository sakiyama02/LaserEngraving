#pragma once

#include "SteppingMotor.hpp"

class BackMotor :public SteppingMotor{
    public:
    static BackMotor& getInstance(){
        static BackMotor instance;
        return instance;
    }
    private:

    BackMotor();
    ~BackMotor();
};
