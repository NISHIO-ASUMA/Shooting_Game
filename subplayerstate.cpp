//===================================================
//
// サブプレイヤー状態管理処理 [ subplayerstate.cpp ]
// Author: Asuma Nishio
//
//===================================================

//*********************************
// インクルードファイル
//*********************************
#include "subplayerstate.h"
#include "manager.h"
#include "input.h"
#include "gamemanager.h"
#include "particle.h"

//==============================
// コンストラクタ
//==============================
CSubPlayerStateBase::CSubPlayerStateBase()
{
	// 値のクリア
	m_pSubPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateBase::~CSubPlayerStateBase()
{
	// 無し
}

//==============================
// 待機状態コンストラクタ
//==============================
CSubPlayerStateNeutral::CSubPlayerStateNeutral()
{
	// IDセット
	SetID(ID_NEUTRAL);
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateNeutral::~CSubPlayerStateNeutral()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateNeutral::OnStart()
{
	// 直前が着地なら
	if (m_pSubPlayer->GetMotion()->GetMotionType() == CSubPlayer::SUBPLAYERMOTION_LANDING)
	{
		// ニュートラルモーションに設定
		m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_NEUTRAL, true, 5, false);
	}
	else
	{
		// ニュートラルモーションに設定
		m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_NEUTRAL, true, 5, false);
	}
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateNeutral::OnUpdate()
{
	// キー入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモード または アニメーション中 なら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;
	if (pCamera->GetMode() == CCamera::MODE_ANIM) return;

	// Damage中は一切入力を受け付けない
	if (m_pSubPlayer->GetStateMachine()->GetNowStateID() == ID_DAMAGE) return;

	// 移動入力があれば移動状態へ
	if ((m_pSubPlayer->isMoveInputKey(pInput) || m_pSubPlayer->isMovePadButton(pPad) || pPad->GetLeftStick()) &&
		m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE)
	{
		// 状態変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateMove, ID_MOVE);

		// ここで処理を返す
		return;
	}

	// 攻撃キー入力時
	if ((pInput->GetPress(DIK_RETURN) || pPad->GetPress(CJoyPad::JOYKEY_X)) &&
		m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE)
	{
		// ステート変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateAction, ID_ACTION);

		// ここで処理を返す
		return;
	}

	// Spaceキー もしくは PadのAキー
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE)
	{
		// ステート変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}


	// TABキー もしくは PadのR1キー
	if ((pInput->GetPress(DIK_TAB) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT_B)) &&
		m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE)
	{
		// ステート変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateInvite, ID_INVITE);

		// ここで処理を返す
		return;
	}

}
//==============================
// 終了関数
//==============================
void CSubPlayerStateNeutral::OnExit()
{
	// 無し
}


//==============================
// 移動状態コンストラクタ
//==============================
CSubPlayerStateMove::CSubPlayerStateMove()
{
	// IDセット
	SetID(ID_MOVE);
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateMove::~CSubPlayerStateMove()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateMove::OnStart()
{
	// 無し
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateMove::OnUpdate()
{
	// キー入力を取得	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();
	D3DXVECTOR3 MeshPos = VECTOR3_NULL;

	// ゲーム中
	if (nMode == CScene::MODE_GAME)
	{
		// シリンダー座標の取得
		MeshPos = CGameManager::GetCylinder()->GetPos();
	}
	else
	{
		// シリンダー座標の取得
		MeshPos = VECTOR3_NULL;
	}

	// 移動処理実行
	m_pSubPlayer->UpdateMove(MeshPos, pInput, pPad);

	// キー入力が無い
	if (!m_pSubPlayer->isMoveInputKey(pInput) && !m_pSubPlayer->isMovePadButton(pPad)
		&& m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE)
	{
		// ニュートラルに遷移
		m_pSubPlayer->ChangeState(new CSubPlayerStateNeutral, ID_NEUTRAL);

		// ここで処理を返す
		return;
	}

	// ジャンプキー入力時にステート変更
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pSubPlayer->GetNowMotion() != CSubPlayer::SUBPLAYERMOTION_DAMAGE &&
		!m_pSubPlayer->IsJumping())
	{
		// ジャンプに遷移
		m_pSubPlayer->ChangeState(new CSubPlayerStateJump, ID_JUMP);

		// ここで処理を返す
		return;
	}

}
//==============================
// 終了関数
//==============================
void CSubPlayerStateMove::OnExit()
{
	// 無し
}


//==============================
// 攻撃状態コンストラクタ
//==============================
CSubPlayerStateAction::CSubPlayerStateAction()
{
	// IDセット
	SetID(ID_ACTION);
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateAction::~CSubPlayerStateAction()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateAction::OnStart()
{
	// 攻撃モーションに変更
	m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_ACTION);
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateAction::OnUpdate()
{
	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// 入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// 重力
	m_pSubPlayer->GravityScal();

	// 武器の位置取得
	CModel* pModelWeapon = m_pSubPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// nullだったら
	if (!pModelWeapon) return;

	// 腕のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// ゲームシーンなら
	if (nMode == CScene::MODE_GAME)
	{
		// プレイヤーとボス間でベクトル生成
		D3DXVECTOR3 VecBoss = m_pSubPlayer->VecToBoss(m_pSubPlayer->GetPos());

		// 攻撃更新
		m_pSubPlayer->UpdateAction(pInput, mtxWorld, VecBoss, pPad);
	}
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// プレイヤーと中心でベクトル生成
		D3DXVECTOR3 VecCenter = m_pSubPlayer->VecToCenter(m_pSubPlayer->GetPos());

		// 攻撃更新
		m_pSubPlayer->UpdateAction(pInput, mtxWorld, VecCenter, pPad);
	}
}
//==============================
// 終了関数
//==============================
void CSubPlayerStateAction::OnExit()
{
	// 無し
}

//==============================
// ジャンプ状態コンストラクタ
//==============================
CSubPlayerStateJump::CSubPlayerStateJump()
{
	// IDセット
	SetID(ID_JUMP);
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateJump::~CSubPlayerStateJump()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateJump::OnStart()
{
	// ジャンプ開始
	m_pSubPlayer->StartJump();

	// ジャンプモーションに変更
	m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_JUMP);
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateJump::OnUpdate()
{
	// 入力情報の取得
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// 武器の位置取得
	CModel* pModelWeapon = m_pSubPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// nullだったら
	if (!pModelWeapon) return;

	// 腕のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// ゲームシーン
	if (nMode == CScene::MODE_GAME)
	{
		// プレイヤーとボス間でベクトル生成
		D3DXVECTOR3 VecBoss = m_pSubPlayer->VecToBoss(m_pSubPlayer->GetPos());

		// ジャンプ更新関数
		m_pSubPlayer->UpdateJumpAction(pInput, mtxWorld, VecBoss, pPad);
	}
	// チュートリアルシーン
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// 中心ベクトル生成
		D3DXVECTOR3 VecCenter = m_pSubPlayer->VecToCenter(m_pSubPlayer->GetPos());

		// ジャンプ更新関数
		m_pSubPlayer->UpdateJumpAction(pInput, mtxWorld, VecCenter, pPad);
	}
}
//==============================
// 終了関数
//==============================
void CSubPlayerStateJump::OnExit()
{
	// 無し
}


//==============================
// ダメージ状態コンストラクタ
//==============================
CSubPlayerStateDamage::CSubPlayerStateDamage(int nDamage)
{
	// IDセット
	SetID(ID_DAMAGE);

	// 値のクリア
	m_nStateCount = NULL;
	m_nDamage = nDamage;
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateDamage::~CSubPlayerStateDamage()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateDamage::OnStart()
{
	// モーションセット
	m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_DAMAGE);

	// 状態変更
	m_nStateCount = DAMAGECOUNT;

	// パッド取得
	CJoyPad* pJoyPad = CManager::GetJoyPad();
	if (pJoyPad == nullptr) return;

	// 振動開始
	pJoyPad->SetVibration(53000, 53000, 600);

	// カメラ振動
	CManager::GetCamera()->ShakeCamera(40);

	// 判定を有効化
	// m_pPlayer->SetIsDamege(true);

	// パーティクル生成
	CParticle::Create(D3DXVECTOR3(m_pSubPlayer->GetPos().x, 5.0f, m_pSubPlayer->GetPos().z), D3DCOLOR_RGBA(0, 191, 255, 255), 80, 200, 200, 180);
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateDamage::OnUpdate()
{
	// 空中時,重力適用
	m_pSubPlayer->GravityScal();

	// 位置更新
	m_pSubPlayer->AddMove();

	// 状態管理カウンターをデクリメント
	m_nStateCount--;

	if (m_nStateCount <= NULL)
	{
		// カウントを変更
		m_nStateCount = DAMAGECOUNT;

		// 状態変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateNeutral(), ID_NEUTRAL);

		return;
	}
}
//==============================
// 終了関数
//==============================
void CSubPlayerStateDamage::OnExit()
{
	// フラグ初期化
	m_pSubPlayer->SetJump(false);
}


//==============================
// 挑発状態コンストラクタ
//==============================
CSubPlayerStateInvite::CSubPlayerStateInvite()
{
	// IDセット
	SetID(ID_INVITE);
}
//==============================
// デストラクタ
//==============================
CSubPlayerStateInvite::~CSubPlayerStateInvite()
{
	// 無し
}
//==============================
// 開始関数
//==============================
void CSubPlayerStateInvite::OnStart()
{
	// モーションセット
	m_pSubPlayer->GetMotion()->SetMotion(CSubPlayer::SUBPLAYERMOTION_INVITE);

	// 最大時間をセット
	m_nStateCount = INVITECOUNT;
}
//==============================
// 更新関数
//==============================
void CSubPlayerStateInvite::OnUpdate()
{
	// 時間を減らす
	m_nStateCount--;

	if (m_nStateCount <= NULL)
	{
		// 最大時間にセット
		m_nStateCount = INVITECOUNT;

		// ステート変更
		m_pSubPlayer->ChangeState(new CSubPlayerStateNeutral,ID_NEUTRAL);

		// TODO : 切り替えするフラグを有効化する

		return;
	}
}
//==============================
// 終了関数
//==============================
void CSubPlayerStateInvite::OnExit()
{
	// 無し
}
