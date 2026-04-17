//=========================================================
//
// ブロック処理 [ block.h ]
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
#include "objectX.h"

//*********************************************************
// ブロッククラスを定義
//*********************************************************
class CBlock : public CObjectX
{
public:
	// コンストラクタ・デストラクタ
	CBlock(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CBlock();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBlock* Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot);

private:
};