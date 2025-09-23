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

//**********************
// 名前空間
//**********************
namespace SUBINFO
{

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
	
	// 初期座標の向きを設定
	// InitPos(NULL);

	// ステートマシンを生成
	m_pStateMachine = new CStateMachine;

	// 初期状態をセット
	// ChangeState(new CPlayerStateNeutral, CPlayerStateBase::ID_NEUTRAL);

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

}
//=================================
// 描画処理
//=================================
void CSubPlayer::Draw(void)
{

}
