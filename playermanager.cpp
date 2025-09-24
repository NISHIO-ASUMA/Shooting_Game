//=========================================
//
// プレイヤー管理処理 [ playermanager.cpp ]
// Author: Asuma Nishio
//
//=========================================

//***************************
// インクルードファイル
//***************************
#include "playermanager.h"
#include "parameter.h"
#include "input.h"
#include "manager.h"

//***************************
// 静的メンバ変数宣言
//***************************
CPlayer* CPlayerManager::m_pPlayer = nullptr;	// プレイヤーのポインタ
CSubPlayer* CPlayerManager::m_pSubPlayer = nullptr; // サブプレイヤーのポインタ
bool CPlayerManager::m_isChageActive = false;

//===============================
// コンストラクタ
//===============================
CPlayerManager::CPlayerManager()
{
	// 値のクリア
	m_pParameter = nullptr;
	m_isHit = false;
}
//===============================
// デストラクタ
//===============================
CPlayerManager::~CPlayerManager()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CPlayerManager* CPlayerManager::Create(void)
{
	// インスタンス生成
	CPlayerManager* pPlayerManager = new CPlayerManager;
	if (pPlayerManager == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pPlayerManager->Init()))
	{
		return nullptr;
	}

	// 生成されたインスタンスを返す
	return pPlayerManager;
}
//===============================
// 初期化処理
//===============================
HRESULT CPlayerManager::Init(void)
{
	// フラグを無効化
	m_isChageActive = false;

	// プレイヤー生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, -550.0f), VECTOR3_NULL, 10, 0, "data\\MOTION\\Player\\Player100motion.txt");
	m_pSubPlayer = CSubPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 550.0f), D3DXVECTOR3(0.0f, D3DX_PI, 0.0f), 10);

	// 初期化結果
	return S_OK;
}
//===============================
// 終了処理
//===============================
void CPlayerManager::Uninit(void)
{
	// null初期化
	m_pPlayer = nullptr;
	m_pSubPlayer = nullptr;

	// nullじゃなかったら
	if (m_pParameter != nullptr)
	{
		delete m_pParameter;
		m_pParameter = nullptr;
	}
}
//===============================
//更新処理
//===============================
void CPlayerManager::Update(void)
{
	// コリジョンしたか判別する
}
//===============================
// 描画処理
//===============================
void CPlayerManager::Draw(void)
{
	// 無し
}
//===============================
// 操作切り替えフラグ設定
//===============================
void CPlayerManager::SetEnableChangePlayer(void)
{
	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// アニメ―ション中なら処理を通さない
	if (pCamera->GetMode() == CCamera::MODE_ANIM) return;

	// Qキー or RB が押された
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_Q) ||
		CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_RIGHT_B))
	{
		if (CManager::GetCamera()->GetShake() == false)
		{
			// フラグ変更
			m_isChageActive = m_isChageActive ? false : true;
		}
	}

}