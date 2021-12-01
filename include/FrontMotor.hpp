#pragma once

#include "SteppingMotor.hpp"

class FrontMotor :public SteppingMotor{
    public:
    static FrontMotor& getInstance(){
        static FrontMotor instance;
        return instance;
    }
    private:
    FrontMotor();
    ~FrontMotor();
};