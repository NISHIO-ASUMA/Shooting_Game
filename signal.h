//=====================================
//
// �U���T�C������ [ signal.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SIGNAL_H_ // ���̃}�N����`������ĂȂ�������
#define _SIGNAL_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//*************************
// �U���T�C���N���X���`
//*************************
class CSignal : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSignal(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CSignal();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CSignal* Create(void);

private:
	int m_nidxTex;		// �e�N�X�`���C���f�b�N�X
	int m_nLife;		// ����
};

#endif