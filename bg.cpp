//=====================================
//
// 背景処理 [ bg.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "bg.h"

//===============================
// オーバーロードコンストラクタ
//===============================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	// 無し
}
//===============================
// デストラクタ
//===============================
CBg::~CBg()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CBg* CBg::Create(void)
{
	// 背景のポインタ宣言
	CBg* pBg = new CBg;
	if (pBg == nullptr) return nullptr;

	// 初期化処理
	if (FAILED(pBg->Init()))
	{
		return nullptr;
	}

	// 2D描画設定
	pBg->SetRot(D3DXVECTOR3(VECTOR3_NULL));
	pBg->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));
	pBg->SetTexture("BackGround.png");

	// 背景のポインタを返す
	return pBg;
}
//===============================
// 背景の初期化処理
//===============================
HRESULT CBg::Init(void)
{
	// 親クラスの初期化
	CObject2D::Init();

	// 結果を返す
	return S_OK;
}
//===============================
// 背景の終了処理
//===============================
void CBg::Uninit(void)
{
	// 2Dオブジェクトの破棄
	CObject2D::Uninit();
}
//===============================
// 背景の更新処理
//===============================
void CBg::Update(void)
{
	// 無し
}
//===============================
// 背景の描画処理
//===============================
void CBg::Draw(void)
{
	// 2Dオブジェクトの描画
	CObject2D::Draw();
}