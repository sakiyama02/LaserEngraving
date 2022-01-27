#pragma once
/* ------------------------------------------------------------------------- */
/* SteppingMotor.hpp														 */
/* ステッピングモータ制御の規定クラス										 */
/* 																			 */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* 番号		更新履歴										日付		氏名 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								  2022/01/27	崎山勇人 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#include <wiringPi.h>							/* ラズパイ用ライブラリ		 */
#include <wiringPiSPI.h>						/* ラズパイ用ライブラリ		 */
#include <iostream>								/* 入出力ライブラリ			 */
#include <vector>								/* 配列型ライブラリ			 */
#include <cmath>								/* 計算用ライブラリ			 */
using namespace std;

/* ------------------------------------------------------------------------- */
/* define宣言																 */
/* ------------------------------------------------------------------------- */
#define SPI_CHANNEL0 			(         0 )	/* SPIチャンネル0 			 */
#define SPI_CHANNEL1 			(         1 )	/* SPIチャンネル1			 */
#define CLOCK_SPEED 			(   1000000 )	/* クロック速度				 */
#define ONE_MICRO_STEP 			(0.00703125f)	/* 一ステップの角度			 */

/* ------------------------------------------------------------------------- */
/* class宣言																 */
/* ------------------------------------------------------------------------- */
/* ステッピングモータ制御の基底クラス -------------------------------------- */
class SteppingMotor
{
public:
	/* コンストラクタ ------------------------------------------------------ */
	SteppingMotor();
	/* デストラクタ -------------------------------------------------------- */
	~SteppingMotor();
	/* 初期化 -------------------------------------------------------------- */
	int init();
	/* 実行 ---------------------------------------------------------------- */
	int run(float angle);
	/* 実行 ---------------------------------------------------------------- */
	int run(int step, int dir);
	/* 停止 ---------------------------------------------------------------- */
	void stop();
	/* 状態取得 ------------------------------------------------------------ */
	int getStatus(char *status);
	/* 速度変更 ------------------------------------------------------------ */
	int changeSpeed(char speed);

protected:
	int channel;								/* チャンネル				 */

private:
	/* SPI通信 ------------------------------------------------------------- */
	void outputSPI(unsigned char *data, int length);
};

/* ------------------------------------------------------------------------- */
/*				Copyright HAL College of Technology & Design				 */
/* ------------------------------------------------------------------------- */