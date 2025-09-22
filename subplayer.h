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
		SUNPLAYERMOTION_NEUTRAL,	// ニュートラル
		SUNPLAYERMOTION_MOVE,		// 移動
		SUNPLAYERMOTION_ACTION,		// アクション
		SUNPLAYERMOTION_JUMP,		// ジャンプ
		SUNPLAYERMOTION_LANDING,	// 着地
		SUNPLAYERMOTION_JUMPATTACK,	// ジャンプ攻撃
		SUNPLAYERMOTION_DAMAGE,		// ダメージ
		SUNPLAYERMOTION_INVITE,		// ひきつけ
		SUNPLAYERMOTION_MAX
	};

	// コンストラクタ・デストラクタ
	CSubPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CSubPlayer();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// void ChangeState(CSubPlayerState * pNewState, int Id); // ステート変更
	// void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestPos, CJoyPad* pPad); // 通常攻撃更新関数
	// void UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard, CJoyPad* pPad);					  // 移動更新関数
	// void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);
	void Collision(void);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// 現在の座標を取得
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }	// 過去の座標を取得
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// 現在の角度を取得
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }	// 目的角を取得
	SUBPLAYERMOTION GetNowMotion(void) const;

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	CMotion* GetMotion(void) { return m_pMotion; }
	CParameter* GetParameter(void) { return m_pParameter; }
	CStateMachine* GetStateMachine() { return m_pStateMachine; }	// プレイヤーのステートマシンを取得

	// フラグメント関数
	bool IsJumping() { return m_isJump; } 	// ジャンプ状態の確認
	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isAttackeyPress(CInputKeyboard* pKeyInput);
	bool isLanding(void) { return m_isJump; }
	bool GetLanding(void) { return m_isLanding; }
	bool GetIsDamege(void) { return m_isDecHp; }

	// ゲッター
	
	// 静的メンバ関数
	static CSubPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife);

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
	bool m_isShadow;
	bool m_isInvite;
	bool m_isDecHp;

	float m_fAngle;			// 現在の角度
};

#endif