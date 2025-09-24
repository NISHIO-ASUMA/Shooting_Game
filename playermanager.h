//=========================================
//
// プレイヤー管理処理 [ playermanager.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _PLAYERMANAGER_H_ // このマクロ定義がされてなかったら
#define _PLAYERMANAGER_H_ // 2重インクルード防止のマクロ定義

//***************************
// インクルードファイル
//***************************
#include "player.h"
#include "subplayer.h"

//***************************
// 前方宣言
//***************************
class CParameter;

//***************************
// 管理クラスを定義
//***************************
class CPlayerManager
{
public:
	// コンストラクタ・デストラクタ
	CPlayerManager();
	~CPlayerManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetEnableChangePlayer(void);
	bool GetChangeActive(void) { return m_isChageActive; }

	// 静的メンバ関数
	static CPlayerManager* Create(void);
	static CPlayer* GatePlayer(void) { return m_pPlayer; }
	static CSubPlayer* GetSubPlayer(void) { return m_pSubPlayer; }
	static void SetChange(bool isFlags) { m_isChageActive = isFlags; }

private:
	// 静的メンバ変数
	static CPlayer* m_pPlayer;
	static CSubPlayer* m_pSubPlayer;
	static bool m_isChageActive; // 操作できるか

	CParameter* m_pParameter;	// 共通パラメータ

	bool m_isHit;		// ヒットかどうか
};

#endif