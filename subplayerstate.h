//==================================================
//
// サブプレイヤー状態管理処理 [ subplayerstate.h ]
// Author: Asuma Nishio
//
//==================================================

#ifndef _SUBPLAYERSTATE_H_ // このマクロ定義がされてなかったら
#define _SUBPLAYERSTATE_H_ // 2重インクルード防止のマクロ定義

//*********************************
// インクルードファイル
//*********************************
#include "state.h"
#include "subplayer.h"

//*********************************
// サブプレイヤーのベース状態管理
//*********************************
class CSubPlayerStateBase : public CStateBase
{
public:
	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NEUTRAL, // 待機
		ID_MOVE,	// 移動
		ID_ACTION,	// 攻撃
		ID_JUMP,	// ジャンプ
		ID_GUARD,	// 防御
		ID_DAMAGE,	// ダメージ
		ID_INVITE,	// ひきつけ
		ID_MAX
	};

	// コンストラクタ・デストラクタ
	CSubPlayerStateBase();
	~CSubPlayerStateBase();

	// ステートが始まるときに一度だけ呼ばれる関数
	virtual void OnStart() {}

	// ステートが更新されるときに呼ばれる関数
	virtual void OnUpdate() {}

	// ステートが終了する時に一度だけ呼ばれる関数
	virtual void OnExit() {}

	// ゲッター
	int GetID() const override { return m_ID; }
	void SetID(ID id) { m_ID = id; }

	// セッター
	void SetOwner(CSubPlayer* pSubPlayer) { m_pSubPlayer = pSubPlayer; }

protected:
	CSubPlayer* m_pSubPlayer;		// サブプレイヤーのポインタ

private:
	ID m_ID;		// 列挙型のポインタ
};

//***************************************
// 待機状態処理
//***************************************
class CSubPlayerStateNeutral : public CSubPlayerStateBase
{
public:
	// コンストラクタ・デストラクタ
	CSubPlayerStateNeutral();
	~CSubPlayerStateNeutral();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:

};

//***************************************
// 移動状態処理
//***************************************
class CSubPlayerStateMove : public CSubPlayerStateBase
{
public:
	// コンストラクタ・デストラクタ
	CSubPlayerStateMove();
	~CSubPlayerStateMove();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:

};

//***************************************
// 攻撃状態処理
//***************************************
class CSubPlayerStateAction : public CSubPlayerStateBase
{
public:
	// コンストラクタ・デストラクタ
	CSubPlayerStateAction();
	~CSubPlayerStateAction();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:

};

//***************************************
// ジャンプ状態処理
//***************************************
class CSubPlayerStateJump : public CSubPlayerStateBase
{
public:
	// コンストラクタ・デストラクタ
	CSubPlayerStateJump();
	~CSubPlayerStateJump();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

private:
};

//***************************************
// ダメージ状態処理
//***************************************
class CSubPlayerStateDamage : public CSubPlayerStateBase
{
public:
	//**************************
	// ダメージ状態列挙型
	//**************************
	enum DAMAGESTATE
	{
		DAMAGESTATE_NONE,
		DAMAGESTATE_NORMAL,
		DAMAGESTATE_DAMAGE,
		DAMAGESTATE_INVINCIBLE,
		DAMAGESTATE_MAX
	};

	// コンストラクタ・デストラクタ
	CSubPlayerStateDamage(int nDamage);
	~CSubPlayerStateDamage();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

	// ゲッター
	int GetState()const { return m_nStateCount; }

private:
	static constexpr int DAMAGECOUNT = 45;

	int m_nStateCount;		// 管理カウント
	int m_nDamage;			// ダメージ数
	int m_nCurrentstate;	// 現在状態

};


//***************************************
// 挑発状態処理
//***************************************
class CSubPlayerStateInvite : public CSubPlayerStateBase
{
public:
	// コンストラクタ・デストラクタ
	CSubPlayerStateInvite();
	~CSubPlayerStateInvite();

	// ステートが始まるときに一度だけ呼ばれる関数
	void OnStart();

	// ステートが更新されるときに呼ばれる関数
	void OnUpdate();

	// ステートが終了する時に一度だけ呼ばれる関数
	void OnExit();

	// ゲッター
	int GetState()const { return m_nStateCount; }

private:
	static constexpr int INVITECOUNT = 300; // ひきつけフレーム

	int m_nStateCount;		// 管理カウント
	int m_nCurrentstate;	// 現在状態

};







#endif