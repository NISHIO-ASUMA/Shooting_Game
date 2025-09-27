//====================================
//
// 背景処理 [ bg.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BG_H_ // このマクロ定義がされてなかったら
#define _BG_H_ // 2重インクルード防止のマクロ定義

//**********************
// インクルードファイル
//**********************
#include "object2D.h"

//**********************
// 前方宣言
//**********************
class CObject;

//**********************
// 背景クラスを宣言
//**********************
class CBg : public CObject2D
{
public:
	// コンストラクタ・デストラクタ
	CBg(int nPriority = static_cast<int>(CObject::PRIORITY::BASENUMBER));
	~CBg();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// 静的メンバ関数
	static CBg* Create(void);

private:
};

#endif