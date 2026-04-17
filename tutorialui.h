//=========================================================
//
// チュートリアルUI処理 [ tutorialui.h ]
// Author: Asuma Nishio
//
//=========================================================

//*********************************************************
// インクルードガード
//*********************************************************
#pragma once

//*********************************************************
// インクルードファイル
//*********************************************************
#include "object2D.h"

//*********************************************************
// チュートリアルuiクラスを定義
//*********************************************************
class CTutorialUi : public CObject2D
{
public:
	//***************************
	// オブジェクトの状態
	//***************************
	enum STATE
	{
		STATE_AWAIT,
		STATE_MOVE,
		STATE_STOP,
		STATE_EXIT,
		STATE_MAX
	};

	// コンストラクタ・デストラクタ
	CTutorialUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTutorialUi();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// セッター
	void SetState(int nState) { m_nState = nState; }

	// ゲッター
	bool IsFinished() const;

	// 静的メンバ関数
	static CTutorialUi* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,const char * pFileName,int nState);

private:
	int m_nState;		// UIの状態
	float m_fAlpha;		// 透明度
};
