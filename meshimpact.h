//=============================================
//
// ���b�V���C���p�N�g���� [ meshimpact.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _MESHIMPACT_H_ // ���̃}�N����`������ĂȂ�������
#define _MESHIMPACT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************
// �Ռ��g�̃N���X��`
//**********************
class CMeshImpact : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMeshImpact(int nPriority = static_cast<int>(CObject::PRIORITY::IMPACT));
	~CMeshImpact();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	// �Z�b�^�[
	void SetCol(D3DXCOLOR col) { m_col = col; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// �ÓI�����o�֐�
	static CMeshImpact* Create(D3DXVECTOR3 pos, int nLife, float fRadius, float fInRadius,float fSpeed);

private:
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;
	LPDIRECT3DINDEXBUFFER9 m_pIdx;
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;

	float m_fInRadius;
	float m_fOutRadius;
	int m_nLife;
	float m_DecAlpha;
	float m_fSpeed;
};

#endif