#pragma once

#include "Device.hpp"
#include <iostream>
#include <wiringPi.h>
#define SW_PORT5 5
#define SW_PORT6 6
#define SW_PORT13 13
// 基底クラスのpublicメソッドを継承する場合はpublicを入れないといけない
// publicを入れないとpublicメソッドを使えない
// class Laser:Deice  ダメ  
// class Laser:public Devaice 〇
class Laser : public Device{
	public:
	static Laser& getInstance(){
		static Laser instance;
		return instance;
	}
	Laser();
	~Laser();

	int run(int arg);
	int stop(void);
	int init(void);

	protected:
	private:
};
