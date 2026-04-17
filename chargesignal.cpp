//=========================================================
//
// チャージサイン処理 [ chargesignal.cpp ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードファイル
//*********************************************************
#include "chargesignal.h"

//=========================================================
// コンストラクタ
//=========================================================
CChargeSignal::CChargeSignal(int nPriority) : CObject2D(nPriority)
{
	// 値のクリア
	m_nLife = NULL;
}
//=========================================================
// デストラクタ
//=========================================================
CChargeSignal::~CChargeSignal()
{
	// 無し
}
//=========================================================
// 生成処理
//=========================================================
CChargeSignal* CChargeSignal::Create(D3DXVECTOR3 pos)
{
	// インスタンス生成
	CChargeSignal* pChargeSignal = new CChargeSignal;
	if (pChargeSignal == nullptr)	return nullptr;

	// 初期化失敗時
	if (FAILED(pChargeSignal->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pChargeSignal->SetPos(pos);
	pChargeSignal->SetSize(200.0f, 50.0f);
	pChargeSignal->SetAnchor(ANCHORTYPE_CENTER);
	pChargeSignal->SetTexture("laserchageUp.png");

	// ポインタを返す
	return pChargeSignal;
}
//=========================================================
// 初期化処理
//=========================================================
HRESULT CChargeSignal::Init(void)
{
	// 親クラス初期化
	CObject2D::Init();

	// 生存フレーム設定
	m_nLife = 90;

	return S_OK;
}
//=========================================================
// 終了処理
//=========================================================
void CChargeSignal::Uninit(void)
{
	// 親クラスの終了
	CObject2D::Uninit();
}
//=========================================================
// 更新処理
//=========================================================
void CChargeSignal::Update(void)
{
	// 点滅実行
	SetFlash(5, 10, COLOR_YERROW);

	// 体力を減らす
	m_nLife--;

	// 0以下
	if (m_nLife <= NULL)
	{
		// 終了処理
		Uninit();

		// ここで処理終了
		return;
	}

	// 親クラスの更新
	CObject2D::Update();
}
//=========================================================
// 描画処理
//=========================================================
void CChargeSignal::Draw(void)
{
	// 親クラスの描画
	CObject2D::Draw();
}