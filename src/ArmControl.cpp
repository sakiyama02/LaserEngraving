#include "../include/ArmControl.hpp"


ArmControl::ArmControl()
{
	length.l1 = 100;
	length.l2 = 100;
	degree.deg1 = 0;
	degree.deg2 = 0;
	BackMotor &bMotor = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	bMotor.init();
	fMotor.init();
}

ArmControl::~ArmControl() {}

int ArmControl::stop()
{
	BackMotor &bMotor = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	bMotor.stop();
	fMotor.stop();

	return 1;
}

int ArmControl::changeSpeed(char speed)
{
	FrontMotor &fMotor = FrontMotor::getInstance();
	BackMotor &bMotor = BackMotor::getInstance();

	fMotor.changeSpeed(speed);
	bMotor.changeSpeed(speed);

	return 0;
}

int ArmControl::frontinit(int dir)
{
	FrontMotor &fMotor = FrontMotor::getInstance();
	fMotor.run(1, dir);
	delay(2);
	return 1;
}
int ArmControl::backinit(int dir)
{
	BackMotor &bMotor = BackMotor::getInstance();
	bMotor.run(1, dir);
	delay(2);
	return 1;
}

int ArmControl::run(double x, double y)
{
	BackMotor &bMotor = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();

	POS pos;
	pos.x = x;
	pos.y = y;
	// 逆運動学で座標から各ラジアンを取得
	TH t = calc(pos);
	// ラジアンから角度に変換
	double degree0 = t.th0 * 180.0 / PI;
	double degree1 = t.th1 * 180.0 / PI;
	// char bStatus[2]={0,0};
	// char fStatus[2]={0,0};
	int step1 = 0;
	int step2 = 0;
	int dir1 = 0;
	int dir2 = 0;
	int max = 0;

	// printf("%f,%f\n",degree0,degree1);

	// 角度からstep数を取得
	step1 = (int)round((degree0 - deg.deg0) / ONE_MICRO_STEP);
	step2 = (int)round((degree1 - deg.deg1) / ONE_MICRO_STEP);

	// printf("%d    %d\n",step1,step2);
	(degree0 - deg.deg0 > 0) ? dir1 = 1 : dir1 = 0;
	(degree1 - deg.deg1 > 0) ? dir2 = 1 : dir2 = 0;
	(step1 < 0) ? step1 = -step1 : step1;
	(step2 < 0) ? step2 = -step2 : step2;
	deg.deg0 = degree0;
	deg.deg1 = degree1;
	// 最大値を取得
	max = step1;
	(max < step2) ? max = step2 : max;
	// 一ステップずつ実行
	for (int i = 0; i < max; i++)
	{
		if (i < step1)
		{
			bMotor.run(1, dir1);
		}
		if (i < step2)
		{
			fMotor.run(1, dir2);
		}
		delay(2);
	}

	// printf("MotorStop\n");
	return 1;
}

TH ArmControl::calc(POS pos)
{
	double x = pos.x;
	double y = pos.y;
	double l0 = length.l0;
	double l1 = length.l1;

	double norm = sqrt((pos.x * pos.x) + (pos.y * pos.y));

	TH T;
	T.th0 = atan2(y, x) - acos(((x * x) + (y * y) + (l0 * l0) - (l1 * l1)) / (2 * l0 * norm));
	T.th1 = -T.th0 + atan2((y - l0 * sin(T.th0)), (x - l0 * cos(T.th0)));

	return T;
}
