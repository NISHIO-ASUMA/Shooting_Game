//=========================================================
//
// レーザーエフェクト処理 [ effectlaser.h ]
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
// レーザーエフェクトクラスを定義
//*********************************************************
class CEffectLaser : public CBillboard
{
public:
	// コンストラクタ・デストラクタ
	CEffectLaser(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectLaser();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CEffectLaser* Create(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos,D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;		// 体力
	float m_fRadius;	// 半径
	float m_fLength;	// 長さ
	D3DXVECTOR3 m_move;	// 移動量
	D3DXVECTOR3 m_EndPos; // 終点座標
	D3DXVECTOR3 m_OldPos; // 過去の座標
};