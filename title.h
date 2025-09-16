//====================================
//
// �^�C�g������ [ title.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TITLE_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "scene.h"

//**************************
// �O���錾
//**************************
class CTitleManager;

//****************************
// �^�C�g���N���X���`
//****************************
class CTitle :public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitle(bool isFirst = true);
	~CTitle();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTitle* Create(bool isFirst = true);

private:
	CTitleManager* m_pTitleManager; // �}�l�[�W���[�N���X�|�C���^
	bool m_isCreate;				// ���S�����t���O

};
#endif
