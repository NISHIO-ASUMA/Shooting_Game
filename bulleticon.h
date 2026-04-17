//=========================================================
//
// 弾アイコン処理 [ bulleticon.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
//	インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "object2D.h"

//*********************************************************
// 弾アイコン表示クラス定義
//*********************************************************
class CBulletIcon : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CBulletIcon(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBulletIcon();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBulletIcon* Create(D3DXVECTOR3 pos, const char* pTexName, int nIdx);

private:
	int m_nIdx; // 識別番号
};