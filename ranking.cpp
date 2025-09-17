//=======================================
//
// ランキングシーン処理 [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// インクルードファイル宣言
//******************************
#include "ranking.h"
#include "manager.h"
#include "rankingmanager.h"
#include "input.h"
#include "fade.h"
#include "title.h"

//===================================
// オーバーロードコンストラクタ
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	// 値のクリア
	m_pRankManager = nullptr;
}
//===================================
// デストラクタ
//===================================
CRanking::~CRanking()
{
	// 無し
}
//===================================
// 生成処理
//===================================
CRanking* CRanking::Create(void)
{
	// インスタンス生成
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pRanking->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pRanking;
}
//===================================
// 初期化処理
//===================================
HRESULT CRanking::Init(void)
{
	// インスタンス生成
	m_pRankManager = new CRankingManager;

	// nullじゃなかったら
	if (m_pRankManager != nullptr)
	{
		// 初期化処理
		m_pRankManager->Init();
	}

	// 初期化結果を返す
	return S_OK;
}
//===================================
// 終了処理
//===================================
void CRanking::Uninit(void)
{
	// nullチェック
	if (m_pRankManager != nullptr)
	{
		// 終了処理
		m_pRankManager->Uninit();

		// ポインタの破棄
		delete m_pRankManager;

		// null初期化
		m_pRankManager = nullptr;
	}
}
//===================================
// 更新処理
//===================================
void CRanking::Update(void)
{
	// nullチェック
	if (m_pRankManager != nullptr) m_pRankManager->Update();

	// 決定キー入力
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// フェード取得
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// 画面遷移
		pFade->SetFade(new CTitle(true));

		// カメラの設定を初期化する
		CManager::GetCamera()->SetFinishRotation(false);
		CManager::GetCamera()->SetIsRotation(false);
		CManager::GetCamera()->SetKey(false);

		return;
	}
}
//===================================
// 描画処理
//===================================
void CRanking::Draw(void)
{
	// 無し
}