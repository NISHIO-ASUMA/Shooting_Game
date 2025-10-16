//=============================================
//
// チュートリアル管理処理 [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALMANAGER_H_ // このマクロ定義がされてなかったら
#define _TUTORIALMANAGER_H_ // 2重インクルード防止のマクロ定義

//******************************
// インクルードファイル
//******************************
#include "barriermanager.h"
#include "player.h"

//******************************
// 前方宣言
//******************************
class CTutorialUi;
class CTutoTask;
class CMoveUi;
class CItem;

//********************************
// チュートリアル管理クラスを定義
//********************************
class CTutorialManager
{
public:
	//***********************
	// 動かすタスクの種類
	//***********************
	enum TASKTYPE
	{
		TASKTYPE_MOVE,
		TASKTYPE_ATTACK,
		TASKTYPE_JUMP,
		TASKTYPE_JUMPATTACK,
		TASKTYPE_AVOID,
		TASKTYPE_LASER,
		TASKTYPE_LASERACTION,
		TASKTYPE_FREE,
		TASKTYPE_MAX
	};

	// コンストラクタ・デストラクタ
	CTutorialManager();
	~CTutorialManager();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	static CBarrierManager* GetBarrier(void) { return m_pBarrierManger; }
	static CPlayer* GetPlayer(void) { return m_pPlayer; }

private:
	CTutorialUi* m_pTutoui; // チュートリアルuiクラスのポインタ
	CTutoTask* m_pTask;		// タスククラスポインタ	
	TASKTYPE m_Tasktype;	// 種類

	CMoveUi* m_pMoveui;
	CMoveUi* m_pMoveItemUi;
	CItem* m_pItem[2];
	static CPlayer* m_pPlayer;

	static CBarrierManager* m_pBarrierManger;

	bool m_isFreeDone;
	bool m_isCreate;
};

#endif
