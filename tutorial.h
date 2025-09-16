//=====================================
//
// �`���[�g���A������ [ tutorial.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TUTORIAL_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "scene.h"

//**********************
// �O���錾
//**********************
class CTutorialManager;

//************************************
// �`���[�g���A���V�[���N���X���`
//************************************
class CTutorial : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTutorial();
	~CTutorial();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTutorial* Create(void);

private:
	CTutorialManager* m_pTutoManager; // �}�l�[�W���[�N���X�̃|�C���^
};

#endif
