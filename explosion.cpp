//====================================
//
// 爆発処理 [ explosion.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "explosion.h"
#include "manager.h"

//***********************************
// 定数宣言
//***********************************
namespace EXPLOSION
{
	constexpr int NUM_PATTERN = 8; // パターン数
	constexpr int NUM_ANIM = 2;	   // アニメ―ション数
	constexpr float TEX_U = 0.125f; // 分割する値
	constexpr float TEX_V = 1.0f;   // 最大値
	constexpr float SIZE = 100.0f;  // 大きさ
}

//===============================
// オーバーロードコンストラクタ
//===============================
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
}
//===============================
// デストラクタ
//===============================
CExplosion::~CExplosion()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CExplosion* CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col)
{
	// 爆発のインスタンス生成
	CExplosion* pExplsion = new CExplosion;

	// 初期化に失敗したら
	if (FAILED(pExplsion->Init())) 
	{
		// 破棄
		delete pExplsion;

		// NULLを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pExplsion->SetRot(rot);
	pExplsion->SetSize(EXPLOSION::SIZE, EXPLOSION::SIZE);
	pExplsion->SetPos(pos);
	pExplsion->SetCol(col);
	pExplsion->SetTexture("explosion000.png");

	return pExplsion;
}
//===============================
// 爆発の初期化処理
//===============================
HRESULT CExplosion::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	return S_OK;
}
//===============================
// 爆発の終了処理
//===============================
void CExplosion::Uninit(void)
{
	// オブジェクトの終了
	CObject2D::Uninit();
}
//===============================
// 爆発の更新処理
//===============================
void CExplosion::Update(void)
{
	// 無し
}
//===============================
// 爆発の描画処理
//===============================
void CExplosion::Draw(void)
{
	// オブジェクト描画
	CObject2D::Draw();
}
