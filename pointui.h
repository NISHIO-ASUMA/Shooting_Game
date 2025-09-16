//=====================================
//
// �I���|�C���gUI���� [ pointui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _POINTUI_H_ // ���̃}�N����`������ĂȂ�������
#define _POINTUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include "object2D.h"

//*********************************
// �I���|�C���g�\��UI�N���X���`
//*********************************
class CPointUi : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPointUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPointUi();
	
	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CPointUi* Create(D3DXVECTOR3 pos);

private:
	int m_nIdxTex;	// �e�N�X�`���C���f�b�N�X

};

#endif