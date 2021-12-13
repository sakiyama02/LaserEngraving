#pragma once

#include "Device.hpp"
#include <iostream>
#include <wiringPi.h>
// 基底クラスのpublicメソッドを継承する場合はpublicを入れないといけない
// publicを入れないとpublicメソッドを使えない
// class Laser:Deice  ダメ  
// class Laser:public Devaice 〇
class Laser : public Device{
	public:

	Laser();
	~Laser();

	int run(int arg);
	int stop(void);
	int init(void);

	protected:
	private:
};
