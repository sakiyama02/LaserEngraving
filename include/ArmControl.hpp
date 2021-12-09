#pragma once

#define PI 3.141592653589793

typedef struct TH{
	double th0;
	double th1;
}TH;

typedef struct LENGTH{
	double l0;
	double l1;
}LENGTH;

typedef struct POS{
	double x;
	double y;
}POS;

class ArmControl {
	public:

	int run(double x,double y);
	int stop();
	int init();

	static ArmControl& getInstance(){
		static ArmControl instance;
		return instance;
    }

	protected:
	private:
	ArmControl();
	~ArmControl();

	POS arm_pos;
	TH th;
	LENGTH length;

	TH calc(POS pos);
};