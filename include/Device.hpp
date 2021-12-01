#pragma once

class Device{
    public:

    Device(){};
    virtual ~Device(){};

    virtual int Run(int arg)=0;
    virtual int Stop(void)=0;
    virtual int Init(void)=0;
    
    protected:
    private:
};