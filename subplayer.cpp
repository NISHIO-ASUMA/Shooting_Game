//=========================================
//
// サブプレイヤー処理 [ subplayer.h ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "subplayer.h"
#include "manager.h"
#include "texture.h"
#include "boss.h"
#include "particle.h"
#include "meshimpact.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "state.h"
#include "item.h"
#include "barriermanager.h"
#include "rubble.h"
#include "charge.h"
#include "meshpiler.h"
#include "effect.h"
#include "exitpoint.h"
#include "game.h"
#include "effectsmoke.h"
#include "sound.h"
#include "particlepiler.h"
#include "subplayerstate.h"

//**********************
// 名前空間
//**********************
namespace SUBINFO
{
	constexpr int KEYCOUNT = 15; // リピートカウント
	constexpr float MOVE = 0.015f; // 移動量
	constexpr float JUMP = 18.3f; // ジャンプ量
	constexpr float GRAVITY = 1.5f; // 重力
};

//=================================
// コンストラクタ
//=================================
CSubPlayer::CSubPlayer(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_move = VECTOR3_NULL;
	m_Scal = VECTOR3_NULL;
	m_State = NULL;
	m_nIdxTexture = NULL;
	m_rotDest = VECTOR3_NULL;
	m_nNumAll = NULL;
	m_type = NULL;
	m_posOld = VECTOR3_NULL;
	m_nIdxPlayer = NULL;
	m_fAngle = NULL;

	// モデルのポインタのクリア
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// クラスポインタ
	m_pMotion = nullptr;
	m_pParameter = nullptr;
	m_pShadowS = nullptr;
	m_pStateMachine = nullptr;

	// フラグメント
	m_isLanding = false;
	m_isJump = false;
	m_isAttack = false;
	m_isMoving = false;
}
//=================================
// デストラクタ
//=================================
CSubPlayer::~CSubPlayer()
{
	// 無し
}
//=================================
// 生成処理
//=================================
CSubPlayer* CSubPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// インスタンス生成
	CSubPlayer* pSubPlayer = new CSubPlayer;
	if (pSubPlayer == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pSubPlayer->Init()))
	{
		return nullptr;
	}

	// オブジェクト設定
	pSubPlayer->m_pos = pos;
	pSubPlayer->m_rot = rot;
	
	// 生成されたポインタを返す
	return pSubPlayer;
}
//=================================
// 初期化処理
//=================================
HRESULT CSubPlayer::Init(void)
{
	// オブジェクトの種類をセット
	SetObjType(TYPE_PLAYER);

	// 弾の種類
	CBullet::SetType(CBullet::BTYPE_PLAYER);

	// モデル総数を代入
	m_nNumAll = MAX_MODEL;

	// モーション種類数を代入
	m_type = SUBPLAYERMOTION_MAX;

	// 角度初期化
	m_fAngle = NULL;

	// スケールサイズを設定
	m_Scal = D3DXVECTOR3(0.75f, 0.75f, 0.75f);

	// フラグを設定
	m_isJump = false;
	m_isLanding = false;
	m_isMoving = false;

	// モーションの読み込み
	m_pMotion = CMotion::Load("data\\MOTION\\Player\\Player200motion.txt", MAX_MODEL, m_apModel, SUBPLAYERMOTION_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(SUBPLAYERMOTION_MAX);

	// プレイヤー識別モデルフラグを設定
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// nullptrじゃなかったら
		if (m_apModel[nCnt] != nullptr)
		{
			// フラグを設定する
			m_apModel[nCnt]->SetIsPlayer(true);
		}
	}

	// ステンシルシャドウ生成
	m_pShadowS = CShadowS::Create("data\\MODEL\\STAGEOBJ\\Shadowmodel.x",m_pos,m_rot);
	
	// 体力は共通
	// m_pParameter = new CParameter;


	// ステートマシンを生成
	m_pStateMachine = new CStateMachine;

	// 初期状態をセット
	ChangeState(new CSubPlayerStateNeutral(), CSubPlayerStateBase::ID_NEUTRAL);

	// 結果を返す
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CSubPlayer::Uninit(void)
{
	// nullチェック
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{
			m_apModel[nCnt]->Uninit();
			delete m_apModel[nCnt];
			m_apModel[nCnt] = nullptr;
		}
	}

	// nullチェック
	if (m_pMotion != nullptr)
	{
		delete m_pMotion;

		m_pMotion = nullptr;
	}

	// nullptrチェック
	if (m_pParameter != nullptr)
	{
		// ポインタの破棄
		delete m_pParameter;

		// nullptrにする
		m_pParameter = nullptr;
	}

	// nullptrチェック
	if (m_pStateMachine != nullptr)
	{
		// 終了処理
		m_pStateMachine->OnExit();

		// ポインタの破棄
		delete m_pStateMachine;

		// nullptrにする
		m_pStateMachine = nullptr;
	}

	// オブジェクト自身の破棄
	CObject::Release();
}
//=================================
// 更新処理
//=================================
void CSubPlayer::Update(void)
{
	//// 死んでるなら処理しない
	//if (m_isDeath) return;

	// 現在シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// 攻撃中はボスの方向に体を向ける
	if (m_isAttack && nMode == CScene::MODE_GAME)
	{
		// ボスの方向へベクトルを向ける
		D3DXVECTOR3 BossDir = CGameManager::GetBoss()->GetPos() - m_pos;
		BossDir.y = 0.0f;

		if (D3DXVec3LengthSq(&BossDir) > 0.0001f)
		{
			// 正規化
			D3DXVec3Normalize(&BossDir, &BossDir);

			// 角度を適用
			m_rot.y = atan2f(-BossDir.x, -BossDir.z);
		}
	}
	else if (m_isAttack && nMode == CScene::MODE_TUTORIAL)
	{
		// 方向へベクトルを向ける
		D3DXVECTOR3 DestPos = VECTOR3_NULL - m_pos;
		DestPos.y = 0.0f;

		if (D3DXVec3LengthSq(&DestPos) > 0.0001f)
		{
			// 正規化
			D3DXVec3Normalize(&DestPos, &DestPos);

			// 角度を適用
			m_rot.y = atan2f(-DestPos.x, -DestPos.z);
		}
	}

	// nullptrじゃないとき
	if (m_pStateMachine != nullptr)
	{
		// ステート更新
		m_pStateMachine->Update();
	}

	// 入力デバイスのポインタ取得
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;

	pInput = CManager::GetInputKeyboard();
	pJoyPad = CManager::GetJoyPad();

	// 武器のワールドマトリックスとボス方向取得
	CModel* pModelWeapon = GetModelPartType(CModel::PARTTYPE_WEAPON);
	if (!pModelWeapon) return;

	// 腕のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	//==========================
	// アイテムとの当たり判定
	//==========================
	// オブジェクト取得
	CObject* pObjItem = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	// nullptrじゃないとき
	while (pObjItem != nullptr)
	{
		// アイテムのオブジェクトタイプを取得
		if (pObjItem->GetObjType() == CObject::TYPE_ITEM)
		{
			// アイテムにキャスト
			CItem* pItem = static_cast<CItem*>(pObjItem);

			// コリジョンしたとき
			if (pItem->Collision(&m_pos) == true)
			{
				// 一回当たったら抜ける
				break;
			}
		}

		// 次のオブジェクトを検出する
		pObjItem = pObjItem->GetNext();
	}

	// 当たり判定処理関数
	Collision();
	
	// 現在のy座標が0.0f以下の時
	if (m_pos.y <= 0.0f)
	{
		// y座標を地面の座標に設定
		m_pos.y = 0.0f;

		// 着地判定を有効化
		m_isLanding = true;

		// 高さへの移動量を0.0fに設定
		m_move.y = 0.0f;
	}

	// 影座標をMAINプレイヤー座標に設定
	D3DXVECTOR3 ShadowPos = m_pos;

	// オブジェクト設定
	m_pShadowS->SetPos(ShadowPos);
	m_pShadowS->SetRot(m_rot);

	// チャージ上限に達したとき かつ フラグが有効なら
	if ((pInput->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B)) && CCharge::GetChargeFlag())
	{
		// サウンド再生
		CSound* pSound = CManager::GetSound();
		if (pSound != nullptr)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_CHANGEWEPON);
		}

		// 弾の種類を切り替え可能にする
		CBullet::SetType(CBullet::BTYPE_LASER);
	}

	// レーザーの時
	if (CBullet::GetType() == CBullet::BTYPE_LASER)
	{
		// パーティクル生成
		CParticlePiler::Create(D3DXVECTOR3(mtxWorld._41, mtxWorld._42 - 5.0f, mtxWorld._43), D3DXCOLOR(0.2f, 0.6f, 1.0f, 1.0f), 20, 30, 20, 20);
	}

	// モーションの全体更新
	m_pMotion->Update(m_apModel, MAX_MODEL);
}
//=================================
// 描画処理
//=================================
void CSubPlayer::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans, mtxScal;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 大きさを反映
	D3DXMatrixScaling(&mtxScal, m_Scal.x, m_Scal.y, m_Scal.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);


	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
//=================================
// 状態変更処理
//=================================
void CSubPlayer::ChangeState(CSubPlayerStateBase* pNewState, int Id)
{
	// 自分自身を代入
	pNewState->SetOwner(this);

	// ステート変更
	m_pStateMachine->ChangeState(pNewState);
}

//=================================
// 攻撃更新関数
//=================================
void CSubPlayer::UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx,const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{
	// キーフラグをセット
	bool isKeyPress = false;

	//====================
	// 攻撃処理
	//====================
	if ((pInputKeyboard->GetPress(DIK_RETURN) || pPad->GetPress(pPad->JOYKEY_X) && m_pMotion->GetMotionType() != CSubPlayer::SUBPLAYERMOTION_JUMPATTACK))
	{
		// キーフラグをセット
		isKeyPress = true;

		// 15フレーム攻撃キーを入力していたら
		if ((pInputKeyboard->GetRepeat(DIK_RETURN, SUBINFO::KEYCOUNT)) || ((pPad->GetRepeat(pPad->JOYKEY_X, SUBINFO::KEYCOUNT))))
		{
			// 弾を生成
			CBullet::Create(D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43), DestMove, CBullet::GetType(), 5.0f, 5.0f, 40);
		}

		// 攻撃状態じゃないとき
		if (!m_isAttack)
		{
			// 攻撃フラグを有効化する
			m_isAttack = true;

			// 地上攻撃モーションに変更
			m_pMotion->SetMotion(CSubPlayer::SUBPLAYERMOTION_ACTION);
		}
		else if (m_isAttack && !m_pMotion->GetFinishMotion()) // 攻撃状態 かつ モーション終了判定がfalseの時
		{
			// 攻撃フラグを無効化する
			m_isAttack = false;

			// キー入力フラグを無効にする
			isKeyPress = false;

			// ニュートラルステートに変更
			ChangeState(new CSubPlayerStateNeutral(), CSubPlayerStateBase::ID_NEUTRAL);

			// ここで処理を返す
			return;
		}
	}
	else if (!isKeyPress && m_pMotion->GetMotionType() == CSubPlayer::SUBPLAYERMOTION_ACTION)
	{// キーフラグが無効 かつ 現在のモーションが攻撃モーションなら

		// 攻撃状態を解除
		m_isAttack = false;

		// ニュートラルモーションに変更
		ChangeState(new CSubPlayerStateNeutral(), CSubPlayerStateBase::ID_NEUTRAL);

		// ここで処理を返す
		return;

	}

	// 攻撃状態 かつ モーションの状態が攻撃じゃなかったら
	if (m_isAttack && m_pMotion->GetMotionType() != CSubPlayer::SUBPLAYERMOTION_ACTION)
	{
		// 攻撃状態を解除
		m_isAttack = false;
	}
}
//=================================
// 移動更新関数
//=================================
void CSubPlayer::UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard, CJoyPad* pPad)
{
	// ジャンプ攻撃中なら移動処理を禁止
	if (m_pMotion->GetMotionType() == SUBPLAYERMOTION_JUMPATTACK)
	{
		return; // この時は移動や方向変更なし
	}

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// キー入力時の角度計算
	static float fAngle = NULL;

	// 円柱の半径を取得
	float fRadius = NULL;

	// ゲームシーン
	if (nMode == CScene::MODE_GAME)
	{
		fRadius = CGameManager::GetCylinder()->GetRadius();
	}
	else
	{
		fRadius = 550.0f;
	}

	// キー入力時の角度計算
	if (pInputKeyboard->GetPress(DIK_A) || (pPad->GetPress(pPad->JOYKEY_LEFT)))
	{
		// 角度更新
		m_fAngle += SUBINFO::MOVE;

		// 目的角を計算
		m_rotDest.y = m_fAngle - D3DX_PI * 0.5f; // 左向きに設定

		if (!m_isJump) 	m_pMotion->SetMotion(SUBPLAYERMOTION_MOVE, false, 0, false); // 移動モーションに変更
	}
	else if (pInputKeyboard->GetPress(DIK_D) || (pPad->GetPress(pPad->JOYKEY_RIGHT)))
	{
		// 角度更新
		m_fAngle -= SUBINFO::MOVE;

		// 目的角を計算
		m_rotDest.y = m_fAngle + D3DX_PI * 0.5f; // 右向きに設定

		if (!m_isJump) 	m_pMotion->SetMotion(SUBPLAYERMOTION_MOVE, false, 0, false); // 移動モーションに変更
	}
	else
	{
		// 移動モーション時,ニュートラルモーションに変更
		if (m_pMotion->GetMotionType() == SUBPLAYERMOTION_MOVE) m_pMotion->SetMotion(SUBPLAYERMOTION_NEUTRAL, false, 0, false);
	}


	// キー入力時の角度計算
	if (pInputKeyboard->GetPress(DIK_A) || (pPad->GetPress(pPad->JOYKEY_LEFT))) // Aキー
	{
		// 角度更新
		m_fAngle += SUBINFO::MOVE;

		// 目的角を計算
		m_rotDest.y = m_fAngle - D3DX_PI * 0.5f; // 左向きに設定

		if (!m_isJump) 	m_pMotion->SetMotion(SUBPLAYERMOTION_MOVE, false, 0, false); // 移動モーションに変更
	}
	else if (pInputKeyboard->GetPress(DIK_D) || (pPad->GetPress(pPad->JOYKEY_RIGHT))) // Dキー
	{
		// 角度更新
		m_fAngle -= SUBINFO::MOVE;

		// 目的角を計算
		m_rotDest.y = m_fAngle + D3DX_PI * 0.5f; // 右向きに設定

		if (!m_isJump) 	m_pMotion->SetMotion(SUBPLAYERMOTION_MOVE, false, 0, false); // 移動モーションに変更
	}
	else
	{
		// 移動モーション時,ニュートラルモーションに変更
		if (m_pMotion->GetMotionType() == SUBPLAYERMOTION_MOVE) m_pMotion->SetMotion(SUBPLAYERMOTION_NEUTRAL, false, 0, false);
	}

	// 角度を正規化
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// 対角線座標を中心から計算
	m_pos.x = DestPos.x - sinf(m_fAngle) * fRadius;
	m_pos.z = DestPos.z - cosf(m_fAngle) * fRadius;

	// 角度設定
	m_rot.y += (m_rotDest.y - m_rot.y) + D3DX_PI;

	// 現在座標を更新
	m_posOld = m_pos;
}
//=================================
// 攻撃更新関数
//=================================
void CSubPlayer::UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{
	// モーションのフラグ
	bool isJumpAttacking = (m_pMotion->GetMotionType() == SUBPLAYERMOTION_JUMPATTACK);

	// シーン取得
	CScene::MODE nMode = CManager::GetScene();

	// ジャンプ中に移動する場合
	if (!isJumpAttacking && m_pMotion->GetMotionType() == SUBPLAYERMOTION_JUMP)
	{
		D3DXVECTOR3 DestPos = VECTOR3_NULL;

		if (nMode == CScene::MODE_GAME)
		{
			// メッシュシリンダーの取得
			DestPos = CGameManager::GetCylinder()->GetPos();
		}
		else
		{
			DestPos = VECTOR3_NULL;
		}

		// 移動処理呼び出し
		UpdateMove(DestPos, pInputKeyboard, pPad);
	}

	// ジャンプ攻撃中に空中で静止する
	if (isJumpAttacking && ((pInputKeyboard->GetPress(DIK_RETURN)) || (pPad->GetPress(pPad->JOYKEY_X))))
	{
		// 一定の高さで静止する
		m_move.y = 0.0f;
	}
	else
	{
		// 重力値を適用
		m_move.y -= 0.7f;
	}

	// ジャンプ中処理
	if (m_isJump)
	{
		// ジャンプ中に攻撃キー入力
		if ((pInputKeyboard->GetPress(DIK_RETURN)) || ((pPad->GetPress(pPad->JOYKEY_X))))
		{
			// 攻撃キーを15フレーム押し続けていたら
			if ((pInputKeyboard->GetRepeat(DIK_RETURN, SUBINFO::KEYCOUNT)) || ((pPad->GetRepeat(pPad->JOYKEY_X, SUBINFO::KEYCOUNT))))
			{
				// 弾を生成
				CBullet::Create(D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43), DestMove, CBullet::GetType(), 5.0f, 5.0f, 45);
			}

			// ジャンプ攻撃モーションに変更
			m_pMotion->SetMotion(SUBPLAYERMOTION_JUMPATTACK, false, 0, false);

			// ゲームシーン
			if (nMode == CScene::MODE_GAME)
			{
				// 方向をボスに向かせる
				D3DXVECTOR3 BossDir = CGameManager::GetBoss()->GetPos() - m_pos;
				BossDir.y = 0.0f;

				if (D3DXVec3LengthSq(&BossDir) > 0.0001f)
				{
					D3DXVec3Normalize(&BossDir, &BossDir);
					m_rot.y = atan2f(-BossDir.x, -BossDir.z);
				}
			}
			// チュートリアルシーン
			else if (nMode == CScene::MODE_TUTORIAL)
			{
				// 方向を設定
				D3DXVECTOR3 VecCenter = VECTOR3_NULL - m_pos;
				VecCenter.y = 0.0f;

				if (D3DXVec3LengthSq(&VecCenter) > 0.0001f)
				{
					D3DXVec3Normalize(&VecCenter, &VecCenter);
					m_rot.y = atan2f(-VecCenter.x, -VecCenter.z);
				}
			}
		}
	}

	// 高さ更新
	AddMove();

	// 着地時の処理
	if (m_isLanding)
	{
		// 着地モーションに変更
		m_pMotion->SetMotion(SUBPLAYERMOTION_LANDING,true,5,false);

		// ジャンプ可能状態に変更
		m_isJump = false;

		// フラグ有効化
		m_isLanding = true;
	}

	// モーション終了時　かつ 種類が着地モーション
	if (m_pMotion->GetMotionType() == SUBPLAYERMOTION_LANDING && m_pMotion->GetFinishMotion())
	{
		if (m_isLanding == true)
		{
			// ニュートラルに変更
			ChangeState(new CSubPlayerStateNeutral(), CSubPlayerStateBase::ID_NEUTRAL);

			// ここで処理を返す
			return;
		}
	}

	// 着地時に移動キー入力が存在しているなら
	if (m_pMotion->GetMotionType() == SUBPLAYERMOTION_LANDING && (isMoveInputKey(pInputKeyboard) || isMovePadButton(pPad)))
	{
		// ニュートラルに変更
		ChangeState(new CSubPlayerStateMove(), CSubPlayerStateBase::ID_NEUTRAL);

		// ここで処理を返す
		return;
	}
}
//=================================
// 当たり判定関数
//=================================
void CSubPlayer::Collision(void)
{

}

//=================================
// 方向指定関数
//=================================
D3DXVECTOR3 CSubPlayer::VecToBoss(const D3DXVECTOR3& pPos)
{
	// ボスの座標取得
	D3DXVECTOR3 BossPos = CGameManager::GetBoss()->GetPos();

	// プレイヤーとボス間でベクトル生成
	D3DXVECTOR3 VecBoss = BossPos - pPos;
	VecBoss.y = 0.0f;

	// できたベクトルを正規化する
	D3DXVec3Normalize(&VecBoss, &VecBoss);

	// ベクトルを返す
	return VecBoss;
}
//=================================
// 方向指定関数
//=================================
D3DXVECTOR3 CSubPlayer::VecToCenter(const D3DXVECTOR3& pPos)
{
	// ボスの座標取得
	D3DXVECTOR3 CenterPos = VECTOR3_NULL;

	// プレイヤーとボス間でベクトル生成
	D3DXVECTOR3 VecCenter = CenterPos - pPos;
	VecCenter.y = 0.0f;

	// できたベクトルを正規化する
	D3DXVec3Normalize(&VecCenter, &VecCenter);

	// ベクトルを返す
	return VecCenter;
}
//================================
//　ジャンプ開始
//================================
void CSubPlayer::StartJump(void)
{
	// ジャンプキー入力 かつ ジャンプフラグがfalseの時
	if (!m_isJump)
	{
		// フラグを有効化
		m_isJump = true;

		// 未着地判定に変更
		m_isLanding = false;

		// 上昇値を設定
		m_move.y = SUBINFO::JUMP;

		// 移動更新
		AddMove();
	}
}
//==================================
// 重力関数
//==================================
void CSubPlayer::GravityScal(void)
{
	// 重力値を適用
	m_move.y -= SUBINFO::GRAVITY;
}
//==================================
// ダメージ関数
//==================================
void CSubPlayer::HitDamage(int nDamage)
{
	// バリア取得
	CBarrierManager* pBarrier = CGameManager::GetBarrier();

	// バリアが0以上
	if (pBarrier != nullptr && pBarrier->GetNumBarrier() > 0)
	{
		// バリアを減らす
		pBarrier->DamageBarrier(nDamage);

		// 処理終了
		return;
	}

	// パラメーター取得
	int nHp = m_pParameter->GetHp();

	// 体力を減らす
	nHp -= nDamage;

	// サウンド取得
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return;

	// 再生
	pSound->PlaySound(CSound::SOUND_LABEL_DAMAGE);

	// 現在体力が0以下
	if (nHp <= NULL)
	{
		// 現在体力をセット
		m_pParameter->SetHp(nHp);

		// 死亡フラグをセット
		// m_isDeath = true;

		// モーションセット
		m_pMotion->SetMotion(SUBPLAYERMOTION_DAMAGE, false, 0, false);

		return;
	}
	else
	{
		// 現在体力をセット
		m_pParameter->SetHp(nHp);
	}

}
//=================================
// 現在モーション取得
//=================================
CSubPlayer::SUBPLAYERMOTION CSubPlayer::GetNowMotion(void) const
{
	// nullじゃなかったら
	if (m_pMotion)
	{
		// 現在番号を返す
		return static_cast<CSubPlayer::SUBPLAYERMOTION>(m_pMotion->GetMotionType());
	}

	return SUBPLAYERMOTION_NEUTRAL; // デフォルト
}
//=================================
// モデルのパーツ取得
//=================================
CModel* CSubPlayer::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// プレイヤーが持っているモデルの数の中から探す
	for (int nModel = 0; nModel < MAX_MODEL; nModel++)
	{
		// モデルがある かつ 取得したい物と一致していたら
		if (m_apModel[nModel] && m_apModel[nModel]->GetPartType() == modelpart)
		{
			// 該当モデルのidx番号のモデルを返す
			return m_apModel[nModel];
		}
	}

	// 該当なし
	return nullptr;
}
//================================
// キー入力判定
//================================
bool CSubPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// いずれかの移動キー入力
	return (pKeyInput->GetPress(DIK_A) || pKeyInput->GetPress(DIK_D));
}
//================================
// キー入力判定
//================================
bool CSubPlayer::isMovePadButton(CJoyPad* pPad)
{
	// いずれかの移動キー入力
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
