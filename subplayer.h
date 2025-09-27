//=========================================
//
// サブプレイヤー処理 [ subplayer.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _SUBPLAYER_H_ // このマクロ定義がされてなかったら
#define _SUBPLAYER_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// 前方宣言
//**********************
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CSubPlayerStateBase;

//*****************************
// サブプレイヤークラスを定義
//*****************************
class CSubPlayer : public CObject
{
public:
	//****************************************
	// サブプレイヤーが行うモーション列挙型
	//****************************************
	enum SUBPLAYERMOTION
	{
		SUBPLAYERMOTION_NEUTRAL,	// ニュートラル
		SUBPLAYERMOTION_MOVE,		// 移動
		SUBPLAYERMOTION_ACTION,		// アクション
		SUBPLAYERMOTION_JUMP,		// ジャンプ
		SUBPLAYERMOTION_LANDING,	// 着地
		SUBPLAYERMOTION_JUMPATTACK,	// ジャンプ攻撃
		SUBPLAYERMOTION_DAMAGE,		// ダメージ
		SUBPLAYERMOTION_INVITE,		// ひきつけ
		SUBPLAYERMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CSubPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CSubPlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void ChangeState(CSubPlayerStateBase* pNewState, int Id);
	void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx,const D3DXVECTOR3 DestMove,CJoyPad* pPad);
	void UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard, CJoyPad* pPad);
	void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);
	void Collision(void);

	D3DXVECTOR3 VecToBoss(const D3DXVECTOR3& pPos);
	D3DXVECTOR3 VecToCenter(const D3DXVECTOR3& pPos);

	void StartJump(void);
	void GravityScal(void);
	void HitDamage(int nDamage);

	// セッター
	void SetRotDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	void SetJump(bool isJump) { m_isJump = isJump; }
	void SetLanding(bool isLanding) { m_isLanding = isLanding; }
	void AddMove(void) { m_pos += m_move; }

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }		
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }		
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }
	SUBPLAYERMOTION GetNowMotion(void) const;

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	CMotion* GetMotion(void) { return m_pMotion; }
	CParameter* GetParameter(void) { return m_pParameter; }
	CStateMachine* GetStateMachine() { return m_pStateMachine; }

	int GetType(void) { return m_type; }
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	// フラグメント関数
	bool IsJumping(void) { return m_isJump; }
	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isLanding(void) { return m_isJump; }
	bool GetLanding(void) { return m_isLanding; }

	// 静的メンバ関数
	static CSubPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	static inline constexpr int MAX_MODEL = 19; // サブプレイヤーで使うモデルの数

	D3DXVECTOR3 m_move;		// 移動量
	D3DXVECTOR3 m_rotDest;  // 目的角
	D3DXVECTOR3 m_pos;		// 階層構造設定座標
	D3DXVECTOR3 m_posOld;	// 過去の座標情報
	D3DXVECTOR3 m_rot;		// 角度
	D3DXVECTOR3 m_Scal;		// 拡大率
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス

	CModel* m_apModel[MAX_MODEL]; // 使うモデルのポインタ
	CMotion* m_pMotion;		// モーションのポインタ
	CParameter* m_pParameter; // パラメータークラスポインタ
	CShadowS* m_pShadowS;	// ステンシルシャドウクラスポインタ
	CStateMachine* m_pStateMachine;	// ステート基底クラスのポインタ

	int m_type;				// モーションの種類変数
	int m_nNumAll;			// モデル総数
	int m_State;			// 状態管理カウンター
	int m_nIdxTexture;		// テクスチャID
	int m_nIdxPlayer;		// プレイヤーの識別番号

	bool m_isLanding;		// 着地判定
	bool m_isJump;			// ジャンプ判定
	bool m_isMoving;		// 移動キー判定
	bool m_isAttack;		// 攻撃判定
	bool m_isInvite;

	float m_fAngle;			// 現在の角度
};

#endif