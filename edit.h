//========================================
//
// �G�f�B�^�[�V�[������ [ edit.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _EDIT_H_ // ���̃}�N����`������ĂȂ�������
#define _EDIT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "scene.h"

//**********************************
// �O���錾
//**********************************
class CEditManager;

//**********************************
// �G�f�B�^�[�V�[���N���X���`
//**********************************
class CEdit : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEdit();
	~CEdit();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CEdit* Create(void);

private:
	CEditManager* m_pEditManager; // �}�l�[�W���[�N���X�|�C���^

};

#endif
