//=========================================================
//
// ブロック全体の管理を行う [ blockmanager.h ]
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
#include "block.h"
#include <vector>

//*********************************************************
// ブロックマネージャークラス定義
//*********************************************************
class CBlockManager
{
public:
	// コンストラクタ・デストラクタ
	CBlockManager();
	~CBlockManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// 静的メンバ関数
	static CBlock* Create(const char* pfileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static std::vector<CBlock*> m_blocks; // 配列
	static int m_nIdxCount;	// モデルインデックス番号
};