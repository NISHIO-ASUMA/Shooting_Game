//============================================
//
// �������U���g�V�[������ [ loseresult.h ]
// Author: Asuma Nishio
// 
//============================================

#ifndef _LOSERESULT_H_ // ���̃}�N����`������ĂȂ�������
#define _LOSERESULT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "scene.h"

//********************************
// �������U���g�V�[���N���X���`
//********************************
class CLoseResult : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CLoseResult();
	~CLoseResult();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CLoseResult* Create(void);

private:

};

#endif