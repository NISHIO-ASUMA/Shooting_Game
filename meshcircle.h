//==================================
//
// �~�`���b�V������ [ meshcircle.h ]
// Author: Asuma Nishio
//
//==================================

#ifndef _MESHCIRCLE_H_ // ���̃}�N����`������ĂȂ�������
#define _MESHCIRCLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**************************
// �~�`���b�V���N���X��`
//**************************
class CMeshCircle : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMeshCircle(int nPriority = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshCircle();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CMeshCircle* Create(D3DXVECTOR3 pos);

private:
	int m_nTexIdx;		// �e�N�X�`���C���f�b�N�X

	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X

	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��
	int m_nNumDigitX, m_nNumDigitZ;		// ������
	int m_nLife;			// ����
	float m_fRadius;		// ���a
};

#endif