//=====================================
//
// �|�[�Y�Ǘ����� [ pausemanager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PAUSEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _PAUSEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "pause.h"

//*********************************
// �|�[�Y���j���[�Ǘ��N���X���`
//*********************************
class CPauseManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPauseManager();
	~CPauseManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �Z�b�^�[
	static void SetEnablePause(bool isFlags) { m_isPause = isFlags; }
	void SetEnablePause(void);

	// �ÓI�����o�֐�
	static bool GetPause(void) { return m_isPause; }

private:

	static constexpr int SELECT_MAX = 4; // �ő僁�j���[�I��

	int m_nSelectIdx;	// �Z���N�g�ԍ�

	CPause* m_pPause[SELECT_MAX]; // �|�[�Y�N���X�̃|�C���^�z��

	static bool m_isPause;		// �|�[�Y���ǂ���
};

#endif
