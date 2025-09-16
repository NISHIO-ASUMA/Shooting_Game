//====================================
//
// �ҏW�p���f������ [ edimodel.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//***************************
// �ҏW�p���f���N���X���`
//***************************
class CEditModel : public CObject
{
public:
	CEditModel(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CEditModel();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxworld; }
	int GetIdx(void) { return m_nIdxObj; }

	void SetIdxObj(int nIdx) { m_nIdxObj = nIdx; }

	static CEditModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
	int m_nIdxObj;
};

