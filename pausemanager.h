//=========================================================
//
// ポーズ管理処理 [ pausemanager.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "pause.h"

//*********************************************************
// ポーズメニュー管理クラスを定義
//*********************************************************
class CPauseManager
{
public:
	// コンストラクタ・デストラクタ
	CPauseManager();
	~CPauseManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// セッター
	static void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	// 静的メンバ関数
	static bool GetPause(void) { return m_isPause; }

private:
	// 定数宣言
	static constexpr int SELECT_MAX = 4; // 最大メニュー選択数
	static constexpr int SELECT_BEGIN = 1; // 最大メニュー選択数
	static constexpr int SELECT_END = 3; // 最大メニュー選択数

	int m_nSelectIdx;	// セレクト番号
	static bool m_isPause;		// ポーズかどうか
	CPause* m_pPause[SELECT_MAX]; // ポーズクラスのポインタ配列
};