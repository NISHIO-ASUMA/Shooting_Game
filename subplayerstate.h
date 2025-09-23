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
class CSubPlayerState : public CStateBase
{
public:
	//***************************
	// 状態管理ID列挙型
	//***************************
	enum ID
	{
		ID_NEUTRAL, // 待機
		ID_MOVE, // 移動
		ID_ACTION, // 攻撃
		ID_JUMP, // ジャンプ
		ID_GUARD, // 防御
		ID_DAMAGE,// ダメージ
		ID_INVITE, // ひきつけ
		ID_MAX
	};

	// コンストラクタ・デストラクタ
	CSubPlayerState();
	~CSubPlayerState();

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

#endif