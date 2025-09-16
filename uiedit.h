//=====================================
//
// UI�G�f�B�^�[�V�[������ [ uiedit.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _UIEDIT_H_ // ���̃}�N����`������ĂȂ�������
#define _UIEDIT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "scene.h"

//*******************************
// �O���錾
//*******************************
class CUimanager;
class CUiEditManager;

//*******************************
// UI�G�f�B�^�[�N���X���`
//*******************************
class CUiedit : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CUiedit();
	~CUiedit();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CUiedit* Create(void);

private:
	CUiEditManager* m_pUiEditManager;	// �N���X�|�C���^
};

#endif