//=========================================
//
// ボス体力処理 [ bosslifegage.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "bosslifegage.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"
#include "object2D.h"

//**********************
// 定数宣言
//**********************
namespace BOSSLIFE
{
	constexpr float VALUELENGTH = 0.32f;	// 割合値
	constexpr float HEIGHT = 60.0f;			// 高さ
};

//===============================
// オーバーロードコンストラクタ
//===============================
CBossLifeGage::CBossLifeGage(int nPriority) : CGage(nPriority)
{
	// 値のクリア
	m_pBoss = nullptr;

	m_nCurrentLifeLength = NULL;
	m_nMaxLifeLength = NULL;
	m_Type = TYPE_FRAME;
}
//===============================
// デストラクタ
//===============================
CBossLifeGage::~CBossLifeGage()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CBossLifeGage* CBossLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType,const char* pTexName)
{
	// インスタンス生成
	CBossLifeGage* pBossLife = new CBossLifeGage;

	// nullだったら
	if (pBossLife == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pBossLife->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pBossLife->SetPos(pos);
	pBossLife->SetSize(fWidth, fHeight);
	pBossLife->SetType(nType);
	pBossLife->SetTexture(pTexName);
	pBossLife->SetAnchor(CObject2D::ANCHORTYPE_LEFTSIDE);

	// 生成されたポインタを返す
	return pBossLife;
}
//===============================
// 初期化処理
//===============================
HRESULT CBossLifeGage::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// ボスの取得
	if (m_pBoss == nullptr)
	{
		m_pBoss = CGameManager::GetBoss();
	}

	// 取得できたら
	if (m_pBoss != nullptr)
	{
		// パラメーター取得
		CParameter* pParam = m_pBoss->GetParam();

		// 最大値体力を設定する
		m_nMaxLifeLength = pParam->GetMaxHp();
	}

	// 初期化結果を返す
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CBossLifeGage::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//===============================
// 更新処理
//===============================
void CBossLifeGage::Update(void)
{
	// 死亡していたら
	if (m_pBoss->IsDaeth()) return;

	// nullじゃない かつ 種類がバーの時
	if (m_pBoss != nullptr && m_Type == TYPE_GAGE)
	{
		// パラメーター取得
		CParameter* pParam = m_pBoss->GetParam();

		// 現在の体力を取得
		m_nCurrentLifeLength = pParam->GetHp();

		// ゲージの長さ設定
		SetGageLength(m_nMaxLifeLength, m_nCurrentLifeLength, BOSSLIFE::VALUELENGTH, BOSSLIFE::HEIGHT);
	}

	// 親クラスの更新処理
	CObject2D::Update();
}
//===============================
// 描画処理
//===============================
void CBossLifeGage::Draw(void)
{
	// 親クラスの描画
	CObject2D::Draw();
}