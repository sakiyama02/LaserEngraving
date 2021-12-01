#pragma once

#define PI 3.141592653589793

typedef struct th{
	double th0;
	double th1;
}th;

typedef struct length{
	double l0;
	double l1;
}length;

typedef struct pos{
	double x;
	double y;
}pos;

class ArmMotor {
	public:

	int Run();
	int Stop();
	int Calc();


	static ArmMotor& getInstance(){
		static ArmMotor instance;
		return instance;
    }

	protected:
	private:
	ArmMotor();
	~ArmMotor();
};