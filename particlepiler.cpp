//=============================================
//
// パーティクルピラー処理 [ particlepiler.h ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// インクルードファイル
//**********************
#include "particlepiler.h"
#include "manager.h"
#include "effect.h"

//=====================================
// オーバーロードコンストラクタ
//=====================================
CParticlePiler::CParticlePiler(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
}
//=====================================
// デストラクタ
//=====================================
CParticlePiler::~CParticlePiler()
{
	// 無し
}
//=====================================
// 生成処理
//=====================================
CParticlePiler* CParticlePiler::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife)
{
	// パーティクルのポインタを宣言
	CParticlePiler* pParticle = new CParticlePiler;

	// nullだったら
	if (pParticle == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pParticle->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// オブジェクト設定
	pParticle->m_pos = pos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;

	// ポインタを返す
	return pParticle;
}
//=====================================
// 初期化処理
//=====================================
HRESULT CParticlePiler::Init(void)
{
	// 配列クリア
	m_pEffect.clear();

	return S_OK;
}
//=====================================
// 終了処理
//=====================================
void CParticlePiler::Uninit(void)
{
	// 配列クリア
	m_pEffect.clear();

	// 親クラスの破棄
	CObject::Release();
}
//=====================================
// 更新処理
//=====================================
void CParticlePiler::Update(void)
{
	//カラーの設定
	D3DXCOLOR col = m_col;

	// 座標を取得
	D3DXVECTOR3 pos = m_pos;

	// パーティクルの生成
	for (int nCntApper = 0; nCntApper < m_nMaxParticle; nCntApper++)
	{
		// 角度をランダムに設定
		float fAngle = (float)(rand() % 628 - 314) / 100.0f;

		// 半径をランダムに設定
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.5f);

		// 上昇速度
		float fRise = (float)(rand() % m_nLength) / 50.0f + 0.1f;

		// 移動量
		D3DXVECTOR3 Move = VECTOR3_NULL;

		Move.x = cosf(fAngle) * fRadius;	// 中心を回る
		Move.z = sinf(fAngle) * fRadius;	// 中心を回る
		Move.y += fRise;					// 上昇

		// 寿命の設定
		int nLife = ((rand() % m_nLife) + 10);

		// エフェクト生成
		CEffect* pEffect = CEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
		{
			// 配列に追加
			m_pEffect.push_back(pEffect);
		}
		else
		{
			break;
		}
	}

	// 破棄
	Uninit();
}
//=====================================
// 描画処理
//=====================================
void CParticlePiler::Draw(void)
{
	// 無し
}
