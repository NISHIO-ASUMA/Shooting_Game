//=====================================
//
// �g�U�I�u�W�F�N�g���� [ spread.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SPREAD_H_ // ���̃}�N����`������ĂȂ�������
#define _SPREAD_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "objectX.h"

//*****************************
// �g�U�I�u�W�F�N�g����
//*****************************
class CSpread : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSpread(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CSpread();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CSpread* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

private:
	float m_fUpSpeed;	// �㏸���x
	int m_nBounceCount;	// ��
};

#endif