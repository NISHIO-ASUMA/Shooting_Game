//====================================
//
// �e���� [ shadow.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SHADOW_H_ // ���̃}�N����`������ĂȂ�������
#define _SHADOW_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object3D.h"

//*****************************
// �e�N���X���`
//*****************************
class CShadow : public CObject3D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CShadow(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CShadow();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void UpdatePos(D3DXVECTOR3 pos);

	// �ÓI�����o�֐�
	static CShadow* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);

	// �Z�b�^�[
	void SetTexture(void);

private:
	int m_nTexIdx;  // �e�N�X�`���C���f�b�N�X�ԍ�
};

#endif
