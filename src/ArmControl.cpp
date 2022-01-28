/* ------------------------------------------------------------------------- */
/* ArmControl.cpp															 */
/*																			 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* ------------------------------------------------------------------------- */
/* 番号		更新履歴								日付		氏名		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2022/01/27	崎山　勇人	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#include "../include/ArmControl.hpp"

/* ------------------------------------------------------------------------- */
/* 関数名		： ArmControl												 */
/* 機能名		： コンストラクタ											 */
/* 機能概要		： メンバー変数の初期化										 */
/* 引数			： なし														 */
/* 戻り値		： 															 */
/* 作成日		： 2022/02/27		 崎山　勇人		 新規作成			 	 */
/* ------------------------------------------------------------------------- */
ArmControl::ArmControl()
{
	BackMotor  &bMotor = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	/* 初期化 */
	length.l1 = 100;
	length.l2 = 100;
	degree.deg1 = 0;
	degree.deg2 = 0;
	bMotor.init();
	fMotor.init();
}
ArmControl::~ArmControl() {}

/* ------------------------------------------------------------------------- */
/* 関数名		： stop														 */
/* 機能名		： 停止														 */
/* 機能概要		： 両方のモータを止める										 */
/* 引数			： なし														 */
/* 戻り値		： int				:0				:正常終了				 */
/* 作成日		： 2022/02/27		 崎山　勇人		 新規作成			 	 */
/* ------------------------------------------------------------------------- */
int ArmControl::stop()
{
	BackMotor &bMotor = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();
	bMotor.stop();
	fMotor.stop();

	return 1;
}


int ArmControl::init(int dir,char select)
{
	FrontMotor &fMotor = FrontMotor::getInstance();
	BackMotor  &bMotor = BackMotor::getInstance();

	/* selectの値によって駆動するモータを選ぶ */
	if( select == FRONT )
	{
		fMotor.run( 1, dir );
	} else {
		bMotor.run( 1, dir );
	}
	delay( 2 );
	return SYS_OK;
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

/* ------------------------------------------------------------------------- */
/* 関数名		： run														 */
/* 機能名		： 実行														 */
/* 機能概要		： 逆運動計算を行い各角度でモータを動かす						 */
/* 引数			： なし														 */
/* 戻り値		： int				:0				:正常終了				 */
/* 作成日		： 2022/02/27		 崎山　勇人		 新規作成			 	 */
/* ------------------------------------------------------------------------- */
int ArmControl::run(double x, double y)
{
	BackMotor &bMotor  = BackMotor::getInstance();
	FrontMotor &fMotor = FrontMotor::getInstance();

	POSITION pos;
	pos.x = x;
	pos.y = y;
	// 逆運動学で座標から各ラジアンを取得
	THETA t = calc(pos);
	// ラジアンから角度に変換
	double degree0 = t.th1 * 180.0 / PI;
	double degree1 = t.th2 * 180.0 / PI;
	int step1 = 0;
	int step2 = 0;
	int dir1 = 0;
	int dir2 = 0;
	int max = 0;

	// 角度からstep数を取得
	step1 = (int)round((degree0 - degree.deg1) / ONE_MICRO_STEP);
	step2 = (int)round((degree1 - degree.deg2) / ONE_MICRO_STEP);

	(degree0 - degree.deg1 > 0) ? dir1 = 1 : dir1 = 0;
	(degree1 - degree.deg2 > 0) ? dir2 = 1 : dir2 = 0;
	(step1 < 0) ? step1 = -step1 : step1;
	(step2 < 0) ? step2 = -step2 : step2;
	degree.deg1 = degree0;
	degree.deg2 = degree1;
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

	return 1;
}

/* ------------------------------------------------------------------------- */
/* 関数名		： calc														 */
/* 機能名		： 逆運動													 */
/* 機能概要		： 逆運動計算を行う											 */
/* 引数			： POSITION			:				:座標					 */
/* 戻り値		： THETA			:0				:正常終了				 */
/* 作成日		： 2022/02/27		 崎山　勇人		 新規作成			 	 */
/* ------------------------------------------------------------------------- */
THETA ArmControl::calc(POSITION pos)
{
	double x = pos.x;
	double y = pos.y;
	double l1 = length.l1;
	double l2 = length.l2;

	double norm = sqrt((pos.x * pos.x) + (pos.y * pos.y));

	THETA T;
	T.th1 = atan2(y, x) - acos(((x * x) + (y * y) + (l1 * l1) - (l1 * l2)) / (2 * l1 * norm));
	T.th2 = -T.th1 + atan2((y - l1 * sin(T.th1)), (x - l1 * cos(T.th1)));

	return T;
}
