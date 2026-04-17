//=========================================================
//
// リザルトシーン管理処理 [ resultmanager.h ]
// Author: Asuma Nishio
// 
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// 前方宣言
//*********************************************************
class CResultScore;

//*********************************************************
// リザルト管理クラスを定義
//*********************************************************
class CResultManager
{
public:
	// コンストラクタ・デストラクタ
	CResultManager();
	~CResultManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Load(void);

private:
	static constexpr int SCORELISTNUM = 3; // 最大数

	bool m_isKeyDown; // キー入力フラグ
	int m_nGameScore; // スコアを格納
	int m_nLastTime; // 時間を格納

	CResultScore* m_pResultScore[SCORELISTNUM];	// スコアポインタ
};