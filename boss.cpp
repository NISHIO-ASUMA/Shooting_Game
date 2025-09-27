//=====================================
//
// ボス処理 [ boss.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// インクルードファイル宣言
//****************************
#include "boss.h"
#include "debugproc.h"
#include "manager.h"
#include "parameter.h"
#include "result.h"
#include "meshimpact.h"
#include "particle.h"
#include "bossstate.h"
#include "state.h"
#include "player.h"
#include "effect.h"
#include "sound.h"
#include "gamemanager.h"
#include "score.h"
#include "signal.h"
#include "handeffect.h"
#include <ctime>

//****************************
// 名前空間
//****************************
namespace BOSSINFO
{
	constexpr float HITRANGE = 11.0f; // コリジョンサイズ
	constexpr float CIRCLEHITRANGE = 200.0f; // 当たり判定の範囲
	constexpr float SETPOS_Y = -600.0f;	// 高さの最大値
	constexpr float MOVESPEED = 1.0f;
	constexpr int COOLTIME = 180;	  // 初期クールタイム
}

//****************************
// 静的メンバ変数宣言
//****************************
bool CBoss::m_isdaeth = false;		// 死亡フラグ

//====================================
// オーバーロードコンストラクタ
//====================================
CBoss::CBoss(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_WeekPointPos = VECTOR3_NULL;

	m_pMotion = nullptr;
	m_pParam = nullptr;
	m_pState = nullptr;

	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_type = NULL;
	m_nCoolTime = NULL;
	m_fSize = NULL;

	m_mtxworld = {};

	m_isEvent = false;
	m_isSet = false;
	m_nCurrentMotion = TYPE_NEUTRAL;
}
//====================================
// デストラクタ
//====================================
CBoss::~CBoss()
{
	// 無し
}
//====================================
// 生成処理
//====================================
CBoss* CBoss::Create(D3DXVECTOR3 pos,float fSize,int nLife)
{
	// インスタンス生成
	CBoss* pBoss = new CBoss;

	// 生成失敗時
	if (pBoss == nullptr) return nullptr;

	// オブジェクトセット
	pBoss->m_pos = pos;
	pBoss->m_fSize = fSize;

	// 初期化失敗時
	if (FAILED(pBoss->Init()))
	{
		// nullポインタを返す
		return nullptr;
	}

	// パラメーターポインタ生成
	pBoss->m_pParam = new CParameter;

	// 体力パラメータ
	if (pBoss->m_pParam != nullptr)
	{
		pBoss->m_pParam->SetMaxHp(nLife);
		pBoss->m_pParam->SetHp(nLife);
	}

	// ポインタを返す
	return pBoss;
}
//=========================================
// モデルの特定部分パーツの取得関数
//=========================================
CModel* CBoss::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// ボスが持っているモデルの数の中から探す
	for (int nModel = 0; nModel < NUMMODELS; nModel++)
	{
		// モデルがある かつ 取得したい物と一致していたら
		if (m_pModel[nModel] && m_pModel[nModel]->GetPartType() == modelpart)
		{
			// 該当モデルのidx番号のモデルを返す
			return m_pModel[nModel];
		}
	}

	// 該当なしの場合
	return nullptr;
}
//====================================
// 初期化処理
//====================================
HRESULT CBoss::Init(void)
{
	// フラグを初期化
	m_isdaeth = false;

	// オブジェクトの種類をセット
	SetObjType(TYPE_BOSS);

	// タイプ代入
	m_type = CBoss::TYPE_MAX;

	// 初期クールタイムを設定
	m_nCoolTime = BOSSINFO::COOLTIME;

	// モーションの読み込み
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\Bossmotion.txt", NUMMODELS, m_pModel, CBoss::TYPE_MAX);

	// モーション数を設定
	m_pMotion->SetMotionNum(m_type);

	// ステート生成
	m_pState = new CStateMachine;

	// 初期状態をセット
	ChangeState(new CBossStateNeutral(m_nCoolTime), CBossStateBace::ID_NEUTRAL);

	// 初期化結果を返す
	return S_OK;
}
//====================================
// 終了処理
//====================================
void CBoss::Uninit(void)
{
	// モデル数分の破棄
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// nullptrチェック
		if (m_pModel[nCnt] != nullptr)
		{
			// 終了処理
			m_pModel[nCnt]->Uninit();

			// ポインタの破棄
			delete m_pModel[nCnt];

			// nullptrにする
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptrチェック
	if (m_pMotion != nullptr)
	{
		// ポインタの破棄
		delete m_pMotion;

		// nullptrにする
		m_pMotion = nullptr;
	}

	// nullptrチェック
	if (m_pParam != nullptr)
	{
		// ポインタの破棄
		delete m_pParam;

		// nullptrにする
		m_pParam = nullptr;
	}

	// nullptrチェック
	if (m_pState != nullptr)
	{
		// 終了処理
		m_pState->OnExit();

		// ポインタの破棄
		delete m_pState;

		// null初期化
		m_pState = nullptr;
	}

	// 自身の破棄
	CObject::Release();
}
//====================================
// 更新処理
//====================================
void CBoss::Update(void)
{
	// 死んでるなら
	if (m_isdaeth)
	{
		// モーションセット
		m_pMotion->SetMotion(CBoss::TYPE_DEATH);

		// モーション全体更新
		m_pMotion->Update(m_pModel, NUMMODELS);

		return;
	}

	// 高さが SETPOS_Y以下
	if (m_pos.y < BOSSINFO::SETPOS_Y && !m_isSet)
	{
		// 上に移動
		m_pos.y += BOSSINFO::MOVESPEED;

		if (m_pos.y >= BOSSINFO::SETPOS_Y)
		{
			// 座標セット
			m_pos.y = BOSSINFO::SETPOS_Y;

			// フラグを有効化
			m_isSet = true;
		}

		// モーション全体更新
		m_pMotion->Update(m_pModel, NUMMODELS);

		return;
	}

	// 減算
	DecCoolTime();

	// nullチェック
	if (m_pState != nullptr)
	{
		// ステート更新
		m_pState->Update();
	}

	// モーション全体更新
	m_pMotion->Update(m_pModel, NUMMODELS);
}
//====================================
// 描画処理
//====================================
void CBoss::Draw(void)
{
	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 全モデルパーツの描画
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// 全モデル描画
		m_pModel[nCnt]->Draw();
	}

#ifdef _DEBUG

	// デバッグ表示
	CDebugproc::Print("ボス座標 [ %.2f ,%.2f , %.2f]", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 40);

	CDebugproc::Print("ボスモーション数 { %d }", m_type);
	CDebugproc::Draw(0, 180);

	CDebugproc::Print("ボス右手座標 { %.2f,%.2f,%.2f }", GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._41, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._42, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._43);
	CDebugproc::Draw(0, 300);

	CDebugproc::Print("ボス体力 { %d }", m_pParam->GetHp());
	CDebugproc::Draw(0, 400);

	CDebugproc::Print("ボスクールタイム { %d }",m_nCoolTime);
	CDebugproc::Draw(1080, 400);

	// デバッグフォント
	m_pMotion->Debug();
#endif // _DEBUG

}
//====================================
// 右手とプレイヤーの当たり判定
//====================================
bool CBoss::CollisionRightHand(D3DXVECTOR3* pPos)
{
	// 生成フラグを作成
	static bool isCreate = false;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// 一定フレーム内
	if (m_pMotion->CheckFrame(25, 25, TYPE_ACTION) && !isCreate)
	{
		// 再生
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// 攻撃サインを生成
		CSignal::Create();

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	// モデルのパーツ取得
	CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // 右手

	// nullだったら
	if (!pRightHand) return false;

	// 右手のワールドマトリックスを取得
	D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();
	D3DXVECTOR3 Pos = D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

	// 一定フレーム内
	if (m_pMotion->CheckFrame(100, 130, TYPE_ACTION) && m_isdaeth == false)
	{
		// 差分計算
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// 計算した差分の長さ取得
		float fDist = D3DXVec3Length(&diff);

		// 距離を返す
		return fDist <= (BOSSINFO::HITRANGE * BOSSINFO::HITRANGE);
	}
	else
	{
		// 当たらないとき
		return false;
	}
}
//====================================
// インパクトモーション時の当たり判定
//====================================
bool CBoss::CollisionImpactScal(D3DXVECTOR3* pPos)
{
	// モデルのパーツ取得
	CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // 右手

	// nullだったら
	if (!pRightHand) return false;

	// モデルのパーツ取得
	CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND); // 左手

	// nullだったら
	if (!pLeftHand) return false;

	// 手のワールドマトリックスを取得
	D3DXMATRIX mtxRight = pRightHand->GetMtxWorld();
	D3DXMATRIX mtxLeft = pLeftHand->GetMtxWorld();

	// 生成フラグを作成
	static bool isCreate = false;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// 一定フレーム内
	if (m_pMotion->CheckFrame(40, 40, TYPE_IMPACT) && !isCreate)
	{
		// 再生
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// 攻撃サインを生成
		CSignal::Create();

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	// 座標を格納
	D3DXVECTOR3 posRight(mtxRight._41, mtxRight._42, mtxRight._43);
	D3DXVECTOR3 posLeft(mtxLeft._41, mtxLeft._42, mtxLeft._43);

	// 両手の座標の中心点を計算
	D3DXVECTOR3 HandCenterPos = (posRight + posLeft) * 0.5f;

	// 一定フレーム内
	if (m_pMotion->CheckFrame(90, 110, TYPE_IMPACT) && !m_isdaeth)
	{
		// エフェクト生成
		CEffect::Create(D3DXVECTOR3(posRight.x, posRight.y + 20.0f, posRight.z - 30.0f), D3DCOLOR_RGBA(250, 250, 210, 255), VECTOR3_NULL, 70, 90.0f);
		CEffect::Create(D3DXVECTOR3(posLeft.x, posLeft.y + 20.0f, posLeft.z - 30.0f), D3DCOLOR_RGBA(250, 250, 210, 255), VECTOR3_NULL, 70, 90.0f);

		// プレイヤーとの距離を測定
		const float fHitRadius = 20.0f * BOSSINFO::HITRANGE; // 判定半径

		// 差分計算用
		D3DXVECTOR3 diff = VECTOR3_NULL;

		// 右手との差分
		diff = posRight - *pPos;

		// 半径に入っているとき
		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			// メッシュ衝撃波を生成	
			CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 100, 120.0f, 15.0f, 10.0f);

			// パーティクル生成
			CParticle::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), D3DCOLOR_RGBA(255, 215, 0, 255), 100, 400, 400, 200);

			// 再生
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);

			return true;

		}

		// 左手との差分
		diff = posLeft - *pPos;

		// 半径に入っているとき
		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			// メッシュ衝撃波を生成	
			CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 100, 120.0f, 15.0f, 10.0f);

			// パーティクル生成
			CParticle::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), D3DCOLOR_RGBA(255, 215, 0, 255), 100, 400, 400, 200);

			// 再生
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);

			return true;
		}
	}

	// 一定フレーム内
	if (m_pMotion->CheckFrame(95, 95, TYPE_IMPACT) && !m_isdaeth)
	{
		// メッシュ衝撃波を生成	
		CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 80, 120.0f, 15.0f, 10.0f);

		// パーティクル生成
		CParticle::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), D3DCOLOR_RGBA(255, 215, 0, 255), 100, 400, 400, 200);
		// 再生
		pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);
	}

	// 当たらないとき
	return false;
}
//=========================================
// 薙ぎ払い時の当たり判定
//=========================================
bool CBoss::CollisionCircle(D3DXVECTOR3* pPos,float fHitRadius)
{
	// 生成フラグを作成
	static bool isCreate = false;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// 一定フレーム内
	if (m_pMotion->CheckFrame(85, 85, TYPE_CIRCLE) && !isCreate)
	{
		// 再生
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// 攻撃サインを生成
		CSignal::Create();

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	// 一定フレーム外
	if (m_pMotion->CheckFrame(305, 320, TYPE_CIRCLE) && m_isdaeth == false)
	{
		return false;
	}

	//  一定フレーム内
	if ((m_pMotion->CheckFrame(110, 240, TYPE_CIRCLE)) && m_isdaeth == false)
	{
		// 右手のパーツ取得
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		if (!pRightHand) return false;

		// 右手のワールドマトリックスを取得
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// 座標に設定
		D3DXVECTOR3 handPos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// エフェクト生成
		CHandEffect::Create(handPos, D3DXCOLOR(1.0f,1.0f,1.0f,0.5f), VECTOR3_NULL, 60, 90.0f);

		// プレイヤーとの距離差分
		float fDisX = pPos->x - handPos.x;
		float fDisY = pPos->y - handPos.y;
		float fDisZ = pPos->z - handPos.z;

		// 半径を設定
		float fBossradius = 25.0f;

		// 半径のサイズを計算
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;

		float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// 半径内に入っていたら
		if (fDissAll <= fRadAll)
		{
			// コリジョン判定を返す
			return true;
		}
	}

	// 当たってないとき
	return false;
}
//=========================================
// 振り下ろし攻撃の当たり判定
//=========================================
bool CBoss::CollisionSwing(D3DXVECTOR3* pPos, float fHitRadius)
{
	// 生成フラグを作成
	static bool isCreate = false;

	// サウンド取得
	CSound* pSound = CManager::GetSound();

	// 一定フレーム内
	if ((m_pMotion->CheckFrame(40, 40, TYPE_ARMRIGHTLEFT) || m_pMotion->CheckFrame(150, 150, TYPE_ARMRIGHTLEFT))&& !isCreate)
	{
		// 再生
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// 攻撃サインを生成
		CSignal::Create();

		// 生成フラグを有効化
		isCreate = true;
	}
	else
	{
		// フレーム外ならリセット
		isCreate = false;
	}

	//  一定フレーム内
	if ((m_pMotion->CheckFrame(100, 160, TYPE_ARMRIGHTLEFT)) && m_isdaeth == false)
	{
		// 右手のパーツ取得
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		if (!pRightHand) return false;

		// 右手のワールドマトリックスを取得
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// 座標に設定
		D3DXVECTOR3 handPos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// パーティクル生成
		CEffect::Create(D3DXVECTOR3(handPos.x, handPos.y, handPos.z - 30.0f), D3DCOLOR_RGBA(0, 255, 127, 255), VECTOR3_NULL,50,100.0f);

		// プレイヤーとの距離差分
		float fDisX = pPos->x - ( handPos.x * 0.9f);
		float fDisY = pPos->y - ( handPos.y);
		float fDisZ = pPos->z - ( handPos.z * 0.9f);

		// 半径を設定
		float fBossradius = 30.0f;

		// 半径のサイズを計算
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;

		float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// 衝撃波
		if ((m_pMotion->CheckFrame(130, 130, TYPE_ARMRIGHTLEFT)))
		{
			// メッシュ衝撃波を生成	
			CMeshImpact::Create(D3DXVECTOR3(handPos.x, 5.0f, handPos.z), 100, 120.0f, 15.0f, 10.0f);

			// パーティクル生成
			CParticle::Create(D3DXVECTOR3(handPos.x, 5.0f, handPos.z), D3DCOLOR_RGBA(255, 215, 0, 255), 100, 400, 400, 200);
			// 再生
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);
		}

		// 半径内に入っていたら
		if (fDissAll <= fRadAll)
		{			
			// コリジョン判定を返す
			return true;
		}
	}

	if ((m_pMotion->CheckFrame(200, 200, TYPE_ARMRIGHTLEFT)))
	{
		// 向く
		RollToPlayer();
	}

	//  一定フレーム内
	if ((m_pMotion->CheckFrame(225, 280, TYPE_ARMRIGHTLEFT)) && m_isdaeth == false)
	{
		// 半径を設定
		float fBossradius = 60.0f;

		// 半径のサイズを計算
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// 右手のパーツ取得
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		D3DXMATRIX mtxWorldR = pRightHand->GetMtxWorld();
		D3DXVECTOR3 handPosR(mtxWorldR._41, mtxWorldR._42, mtxWorldR._43);

		// 左手のパーツ取得
		CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND);
		D3DXMATRIX mtxWorldL = pLeftHand->GetMtxWorld();
		D3DXVECTOR3 handPosL(mtxWorldL._41, mtxWorldL._42, mtxWorldL._43);

		// 中央座標
		D3DXVECTOR3 CenterPos = (handPosL + handPosR) * 0.5f;
		D3DXVECTOR3 CenterPosHit = (handPosL + handPosR) * 0.8f;

		// エフェクト生成
		CEffect::Create(D3DXVECTOR3(handPosR.x, handPosR.y, handPosR.z - 30.0f), D3DCOLOR_RGBA(0, 255, 127, 255), VECTOR3_NULL, 50, 100.0f);
		CEffect::Create(D3DXVECTOR3(handPosL.x, handPosL.y, handPosL.z), D3DCOLOR_RGBA(0, 255, 127, 255), VECTOR3_NULL, 50, 100.0f);

		// 衝撃波
		if ((m_pMotion->CheckFrame(270, 270, TYPE_ARMRIGHTLEFT)))
		{
			// パーティクル生成
			CParticle::Create(D3DXVECTOR3(CenterPos.x, 5.0f, CenterPos.z), D3DCOLOR_RGBA(255,215,0,255), 100, 400, 400, 200);

			// メッシュ衝撃波を生成	
			CMeshImpact::Create(D3DXVECTOR3(CenterPos.x, 5.0f, CenterPos.z), 200, 120.0f, 15.0f, 10.0f);

			// サウンド再生
			pSound->PlaySound(CSound::SOUND_LABEL_EXPLOSION);
		}

		// 右手
		if (pRightHand)
		{
			float fDisX = pPos->x - ( handPosR.x * 0.5f);
			float fDisY = pPos->y - ( handPosR.y);	 
			float fDisZ = pPos->z - ( handPosR.z * 0.5f);

			float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);

			if (fDissAll <= fRadAll)
			{
				// メッシュ衝撃波を生成	
				CMeshImpact::Create(D3DXVECTOR3(CenterPos.x, 5.0f, CenterPos.z), 200, 120.0f, 15.0f, 10.0f);

				// コリジョン判定
				return true; 
			}
		}

		// 左手
		if (pLeftHand)
		{
			float fDisX = pPos->x -( handPosL.x * 0.5f);
			float fDisY = pPos->y -( handPosL.y);	
			float fDisZ = pPos->z -( handPosL.z * 0.5f);

			float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);

			if (fDissAll <= fRadAll)
			{
				// メッシュ衝撃波を生成	
				CMeshImpact::Create(D3DXVECTOR3(CenterPos.x, 5.0f, CenterPos.z), 200, 120.0f, 15.0f, 10.0f);

				// コリジョン判定
				return true; 
			}
		}
	}

	// 当たってないとき
	return false;
}
//====================================
// ヒット処理
//====================================
void CBoss::Hit(int nDamage,D3DXVECTOR3 HitPos)
{
	// フラグが立っていたら
	if (m_isdaeth) return;

	// カメラ取得
	CCamera* pCamera = CManager::GetCamera();

	// イベントモードなら
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// 引数のダメージを格納
	int realDamage = nDamage;

	//==========================
	// 一個目の弱点パーツを取得
	//==========================
	CModel* pWeakHead = GetModelPartType(CModel::PARTTYPE_HEAD);

	// nullじゃなかったら
	if (pWeakHead)
	{
		// 弱点パーツのワールド座標を取得
		D3DXMATRIX mtx = pWeakHead->GetMtxWorld();

		// 弱点座標を設定
		D3DXVECTOR3 weakPos(mtx._41, mtx._42, mtx._43 - 20.0f);

		// ヒット座標との距離を測定
		D3DXVECTOR3 diff = HitPos - weakPos;
		float fDist = D3DXVec3Length(&diff);

		// 判定範囲内なら
		if (fDist <= WEEKPOINTSIZE)
		{
			// ダメージ2倍にする
			realDamage = nDamage * 2;

			// パーティクル生成
			CParticle::Create(HitPos, COLOR_GREEN, 50, 300, 400, 150);
		}
	}

	// HPを減算
	int nHp = m_pParam->GetHp();
	nHp -= realDamage;

	// 0以下なら
	if (nHp <= 0)
	{
		// セット
		nHp = 0;
		m_pParam->SetHp(nHp);

		// 死亡判定
		m_isdaeth = true;

		// スコアを加算
		CScore::AddScore(50000);

		// スコアを書き出す
		CScore::SaveScore();

		// 倒すのにかかった時間を書き出す
		CGameManager::GetTime()->Save();

		return;
	}
	else
	{
		// 現在体力を設定
		m_pParam->SetHp(nHp);

		// 最大HPの半分を下回ったらステート変更
		int nMaxHp = m_pParam->GetMaxHp();

		if (nHp <= nMaxHp * 0.5f)
		{
			// フラグが未使用なら
			if (!m_isEvent)
			{
				// フラグを有効化
				m_isEvent = true;

				// イベント状態へ移行
				ChangeState(new CBossStateEvent(), CBossStateBace::ID_EVENT);

				return;
			}
		}
	}
}
//====================================
// 状態変更処理
//====================================
void CBoss::ChangeState(CBossStateBace* pNewState, int Id)
{
	// 自分自身をセットする
	pNewState->SetOwner(this);

	// 状態を変更する
	m_pState->ChangeState(pNewState);
}
//====================================
// 向きを回転させる処理
//====================================
void CBoss::RollToPlayer(void)
{
	// プレイヤーの取得
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);

	// nullなら
	if (pPlayer == nullptr) return;

	// プレイヤーの座標を取得
	D3DXVECTOR3 pPos = pPlayer->GetPos();
	D3DXVECTOR3 VecPlayer = VECTOR3_NULL;
	VecPlayer = m_pos - pPos;

	// 水平方向の角度を求める
	float angle = atan2f(VecPlayer.x, VecPlayer.z);

	// 計算した角度をセット
	m_rot.y = angle;
}