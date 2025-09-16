//=========================================
//
// �J�����쐬�V�[������ [ cameramode.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _CAMERAMODE_H_ // ���̃}�N����`������ĂȂ�������
#define _CAMERAMODE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "scene.h"

//******************************
// �V�[���N���X���`
//******************************
class CCameraMode : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCameraMode();
	~CCameraMode();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// ��������
	static CCameraMode* Create(void);
};

#endif