#pragma once

class Device{
    public:

    Device(){};
    virtual ~Device(){};

    virtual int run(int arg)=0;
    virtual int stop(void)=0;
    virtual int init(void)=0;
    
    protected:
    private:
};
