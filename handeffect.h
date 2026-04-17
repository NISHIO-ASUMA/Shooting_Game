//=========================================================
//
// ハンドエフェクト処理 [ handeffect.h ]
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
#include "billboard.h"

//*********************************************************
// 前方宣言
//*********************************************************
class CObject;

//*********************************************************
// ハンドエフェクトクラスを定義
//*********************************************************
class CHandEffect : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CHandEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CHandEffect();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CHandEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;			// 寿命
	float m_fRadius;		// 半径
	D3DXVECTOR3 m_move;		// 移動量
};