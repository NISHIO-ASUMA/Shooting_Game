//=========================================================
//
// パラメータ処理 [ parameter.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// パラメータークラスを定義
//*********************************************************
class CParameter
{
public:
	// コンストラクタ・デストラクタ
	CParameter();
	~CParameter();

	// セッター
	void SetHp(int nHp) { m_nHp = nHp; }
	void SetMaxHp(int nMaxHp) { m_nMaxHp = nMaxHp; }
	void AddHp(int nValue) { m_nHp += nValue; }

	// ゲッター
	int GetHp()const { return m_nHp; }
	int GetMaxHp() const { return m_nMaxHp; }

private:
	int m_nHp; // 体力
	int m_nMaxHp; // 最大体力
};