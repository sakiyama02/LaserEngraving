#include "../include/SteppingMotor.hpp"

SteppingMotor::SteppingMotor()
{
}
SteppingMotor::~SteppingMotor() {}

int SteppingMotor::run(float angle)
{
	unsigned char data[4];
	int step = 0;

	if (angle < 0)
	{
		angle = -angle;
		data[0] = 0x40;
	}
	else
	{
		data[0] = 0x41;
	}

	step = (int)round(angle / ONE_MICRO_STEP);
	printf("step=%d\n", step);

	data[1] = ((step >> 16) & 0xff);
	data[2] = ((step >> 8) & 0xff);
	data[3] = ((step)&0xff);

	outputSPI(data, sizeof(data));

	return 1;
}

int SteppingMotor::run(int step, int dir)
{
	unsigned char data[4];

	if (dir == 1)
	{
		data[0] = 0x41;
	}
	else
	{
		data[0] = 0x40;
	}

	data[1] = ((step >> 16) & 0xff);
	data[2] = ((step >> 8) & 0xff);
	data[3] = ((step)&0xff);

	outputSPI(data, sizeof(data));

	return 1;
}

int SteppingMotor::changeSpeed(char speed)
{

	// 最大速度
	unsigned char data3[] = {0x07, 0x00, speed};

	return 0;
}

int SteppingMotor::init()
{

	if (wiringPiSPISetup(channel, CLOCK_SPEED) < 0)
	{
		cout << "wiringPiSPISetup error\n";
		return -1;
	}

	// レジスタ初期化
	unsigned char data0[] = {0x00, 0x00, 0x00, 0xc0};
	// 加速度
	unsigned char data1[] = {0x05, 0x00, 0x8A};
	// 減速度
	unsigned char data2[] = {0x06, 0x00, 0x8A};
	// 最大速度
	unsigned char data3[] = {0x07, 0x00, 0x01};
	// 最小速度
	unsigned char data4[] = {0x08, 0x00, 0x00};
	// フルステップ速度
	unsigned char data5[] = {0x15, 0x00, 0x01};
	// ホールディングKval
	unsigned char data6[] = {0x09, 0xFF};

	unsigned char data7[] = {0x0A, 0xFF};

	unsigned char data8[] = {0x0B, 0xFF};

	unsigned char data9[] = {0x0C, 0xFF};

	unsigned char data10[] = {0x16, 0x07};

	outputSPI(data1, sizeof(data0));
	delay(10);
	outputSPI(data1, sizeof(data1));
	delay(10);
	outputSPI(data2, sizeof(data2));
	delay(10);
	outputSPI(data3, sizeof(data3));
	delay(10);
	outputSPI(data4, sizeof(data4));
	delay(10);
	outputSPI(data5, sizeof(data5));
	delay(10);
	outputSPI(data6, sizeof(data6));
	delay(10);
	outputSPI(data7, sizeof(data7));
	delay(10);
	outputSPI(data8, sizeof(data8));
	delay(10);
	outputSPI(data9, sizeof(data9));
	delay(10);
	outputSPI(data10, sizeof(data10));

	return 1;
}

int SteppingMotor::getStatus(char *status)
{
	unsigned char data[] = {0xd0, 0x00, 0x00};
	outputSPI(data, sizeof(data));
	printf("data=%02x,data=%02x\n", data[1], data[2]);
	status[0] = data[1];
	status[1] = data[2];

	return 1;
}

void SteppingMotor::outputSPI(unsigned char *data, int length)
{
	unsigned char *pt = data;
	// printf("%d\n",channel);
	for (int i = 0; i < length; i++)
	{
		wiringPiSPIDataRW(channel, pt++, 1);
		// printf("%x,",*pt++);
	}
}

void SteppingMotor::stop()
{
	unsigned char data[] = {0xb0};
	outputSPI(data, sizeof(data));
}
