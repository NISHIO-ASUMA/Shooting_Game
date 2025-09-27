//====================================
//
// 編集用モデル処理 [ edimodel.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// インクルードファイル
//**********************
#include "object.h"

//***************************
// 編集用モデルクラスを定義
//***************************
class CEditModel : public CObject
{
public:
	// コンストラクタ・デストラクタ
	CEditModel(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEditModel();

	// メンバ関数
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ゲッター
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxworld; }
	int GetIdx(void) { return m_nIdxObj; }

	// セッター
	void SetIdxObj(int nIdx) { m_nIdxObj = nIdx; }

	// 静的メンバ関数
	static CEditModel* Create(void);

private:
	D3DXVECTOR3 m_pos;	// 座標
	D3DXVECTOR3 m_rot;	// 角度
	D3DXMATRIX m_mtxworld;	// ワールドマトリックス
	int m_nIdxObj;	// オブジェクトインデックス番号
};

