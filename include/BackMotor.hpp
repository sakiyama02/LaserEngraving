#pragma once
/* ------------------------------------------------------------------------- */
/* BackMotor.hpp															 */
/* ステッピングモータ制御の派生クラス										 */
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
#include "SteppingMotor.hpp"					/* 規定クラスのヘッダ		 */

/* ------------------------------------------------------------------------- */
/* class宣言																 */
/* ------------------------------------------------------------------------- */
/* ステッピングモータ制御の派生クラス -------------------------------------- */
class BackMotor : public SteppingMotor
{
public:
	/* シングルトン -------------------------------------------------------- */
	static BackMotor &getInstance()
	{
		static BackMotor instance;
		return instance;
	}

private:
	/* コンストラクタ ------------------------------------------------------ */
	BackMotor();
	/* デストラクタ -------------------------------------------------------- */
	~BackMotor();
};

/* ------------------------------------------------------------------------- */
/*				Copyright HAL College of Technology & Design				 */
/* ------------------------------------------------------------------------- */