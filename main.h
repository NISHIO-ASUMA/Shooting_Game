//=====================================
//
// ���C���֐� [ main.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MAIN_H_ // ���̃}�N����`������ĂȂ�������
#define _MAIN_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************
// ���C���v���Z�X�N���X���`
//*****************************
class CMainProc
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMainProc();
	~CMainProc();

	// �����o�֐�
	void ToggleFullScreen(HWND hWnd);

private:
	RECT m_Windowrect;	// �E�B���h�E�̕�
};

#endif
