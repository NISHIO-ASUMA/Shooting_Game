//============================================
//
// アイテム管理処理 [ itemmanager.cpp ]
// Author : Asuma Nishio
//
//============================================

//*********************************
// インクルードファイル
//*********************************
#include "itemmanager.h"
#include "gamemanager.h"
#include "time.h"
#include "item.h"

//=================================
// コンストラクタ
//=================================
CItemManager::CItemManager()
{
	// 値のクリア
}
//=================================
// デストラクタ
//=================================
CItemManager::~CItemManager()
{
	// 無し
}
//=================================
// 初期化処理
//=================================
HRESULT CItemManager::Init(void)
{
	// 初期化結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CItemManager::Uninit(void)
{
	// 各種終了処理
}
//=================================
// 更新処理
//=================================
void CItemManager::Update(void)
{
	// タイマークラス取得
	CTime* pTime = CGameManager::GetTime();

	// nullなら
	if (pTime == nullptr) return;

	// タイマーを取得
	int NowTime = pTime->GetAllTime();

	// 最終出現時間を保持
	static int lastSpawnTime = -1;

	// 20秒ごとに生成
	if (NowTime % 20 == 0 && NowTime != lastSpawnTime)
	{
		// 出現座標ランダム生成
		int nActivePos = rand() % NUMPOINT;

		// アイテムの出現割合を8:2にする
		int nRand = rand() % 10;
		int nTypeItem = 0;

		if (nRand < 8)
		{// 80%で回復アイテム
			nTypeItem = CItem::TYPE_LIFE;
		}
		else
		{// シールドアイテム
			nTypeItem = CItem::TYPE_GUARD;
		}

		// アイテム生成
		CItem::Create(m_ActivePointPos[nActivePos], VECTOR3_NULL, nTypeItem);

		// 時間を代入
		lastSpawnTime = NowTime;
	}
}