//=====================================
//
// ���C���֐� [ main.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include <crtdbg.h>
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"

//******************************
// �E�B���h�E�v���V�[�W�����`
//******************************
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//==================================
// ���C���֐�
//==================================
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE /*hInstancePrev*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);			// ���������[�N���m�p�̃t���O

	// _CrtSetBreakAlloc(221); // {7585} �̊��蓖�ĂŃu���[�N����
#endif // _DEBUG

	// �}�l�[�W���[�̃C���X�^���X�𐶐�
	CManager* pManager = NULL;

	// FPS�J�E���g
	int nCountFPS = 0;

	DWORD dwCurrentTime;			// ���ݎ���
	DWORD dwExecLastTime;			// �I������

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				 // WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						 // �E�C���h�E�̃X�^�C��
		WindowProc,						 // �E�C���h�E�v���V�[�W��
		0,								 // 0�ɂ���
		0,								 // 0�ɂ���
		hInstance,						 // �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),  // �^�X�N�o�[�A�C�R��
		LoadCursor(NULL,IDC_ARROW),      // �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),      // �N���C�A���g�̈�̔w�i�F
		NULL,                            // ���j���[�o�[
		CLASS_NAME,                      // �E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION),  // �t�@�C���A�C�R��
	};

	HWND hWnd;  // �E�C���h�E�n���h��(���ʎq)
	MSG msg;    // ���b�Z�[�W���i�[����ϐ�

	// ��ʃT�C�Y�̍\��
	RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �N���C�A���g�̈�
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�C���h�E�𐶐�
	hWnd = CreateWindowEx(0,			// �g���E�C���h�E�X�^�C��
		CLASS_NAME,						// �E�C���h�E�N���X�̖��O
		WINDOW_NAME,					// �E�C���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,					// �E�C���h�E�̍����X���W
		CW_USEDEFAULT,					// �E�C���h�E�̍����Y���W
		(rect.right - rect.left),       // �E�C���h�E��
		(rect.bottom - rect.top),       // �E�C���h�E�̍���
		NULL,
		NULL,
		hInstance,						// �C���X�^���X�n���h��
		NULL);							// �E�C���h�E�쐬�f�[�^

	// �������m��
	pManager = new CManager;

	// �}�l�[�W���[�̏���������
	pManager->Init(hInstance, hWnd, TRUE);

	// ����\��ݒ�
	timeBeginPeriod(1);
	dwCurrentTime = 0;					// ������
	dwExecLastTime = timeGetTime();		// ���ݎ�����ۑ�

	//�E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);	// �E�C���h�E�̕\����Ԃ̐ݒ�
	UpdateWindow(hWnd);			// �N���C�A���g�̈�̍X�V

	// ������
	DWORD dwFrameCount = 0;					// �t���[���J�E���g
	DWORD dwFPSLastTime = timeGetTime();	// �Ō��FPS���v����������

	// ���b�Z�[�W���[�v
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{
			// Windows�̏���
			if (msg.message == WM_QUIT)
			{
				// WM_QUIT���b�Z�[�W���󂯎�����烋�[�v������
				break;
			}
			else
			{
				// ���b�Z�[�W�ݒ�
				TranslateMessage(&msg);	// ���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
				DispatchMessage(&msg);	// �E�C���h�E�v���V�[�W���փ��b�Z�[�W�𑗏o
			}
		}
		else
		{// DirectX�̏���

			dwCurrentTime = timeGetTime();		// ���ݎ����̎擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��

				nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime); 	// FPS���v��

				dwFPSLastTime = dwCurrentTime;	// �ۑ�

				dwFrameCount = 0;				// 0�ɖ߂�

				CRenderer::GetFps(nCountFPS);	// FPS�擾
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60/1�o��

				// �����J�n�̎���
				dwExecLastTime = dwCurrentTime;	

				// �t���[���J�E���g�����Z
				dwFrameCount++;

				// �}�l�[�W���[�X�V����
				pManager->Update();

				// �}�l�[�W���[�`�揈��
				pManager->Draw();
			}
		}
	}

	// nullptr����Ȃ�������
	if (pManager != nullptr)
	{
		// �}�l�[�W���[�I������
		pManager->Uninit();

		// �|�C���^�̔j��
		delete pManager;

		// nullptr�ɂ���
		pManager = nullptr;
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ���b�Z�[�W��Ԃ�
	return(int)msg.wParam;
}

//==========================================
// �E�C���h�E�v���V�[�W��
//==========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	// �E�C���h�E�̗̈�
	const RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; 

	// ���b�Z�[�W�n���h����Ԃ��ϐ�
	int nID;

	// �����_���[�̎擾
	CRenderer* pRenderer = CManager::GetRenderer();

	// ���C���v���Z�X�ϐ�
	CMainProc pProc = {};

	switch (uMsg)
	{
	case WM_DESTROY:// �E�C���h�E�j�����b�Z�[�W

		// WM_QUIT���b�Z�[�W�𑗂�
		PostQuitMessage(0);
		break;

	case WM_SIZE:

		if (wParam == SIZE_MINIMIZED)
			return 0;

		pRenderer->SetSize(LOWORD(lParam), HIWORD(lParam));

		return 0;

	case WM_KEYDOWN:				// �L�[�����̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:				// [ESC]�L�[�������ꂽ
			nID = MessageBox(hWnd, "�I�����܂���?", "�I�����b�Z�[�W", MB_YESNO);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);// �E�C���h�E�j�����b�Z�[�W
			}
			else
			{
				return 0;			// �Ԃ�
			}
			break;

		case VK_F11:
			pProc.ToggleFullScreen(hWnd);	// F11�Ńt���X�N���[��
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);// ����̏������J��Ԃ�
}

//==========================================
// �R���X�g���N�^
//==========================================
CMainProc::CMainProc()
{
	// �l�̃N���A
	m_Windowrect = {};
}
//==========================================
// �f�X�g���N�^
//==========================================
CMainProc::~CMainProc()
{
	// ����
}
//==========================================
// �E�B���h�E�t���X�N���[��
//==========================================
void CMainProc::ToggleFullScreen(HWND hWnd)
{
	// �؂�ւ��t���O��錾
	static bool isFullscreen = false;

	// ���݂̃E�B���h�E�X�^�C�����擾
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (isFullscreen)
	{
		// �E�B���h�E���[�h�ɐ؂�ւ�
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, m_Windowrect.left, m_Windowrect.top,
			m_Windowrect.right - m_Windowrect.left, m_Windowrect.bottom - m_Windowrect.top,
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_NORMAL);
	}
	else
	{
		// �t���X�N���[�����[�h�ɐ؂�ւ�
		GetWindowRect(hWnd, &m_Windowrect);
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
		SetWindowPos(hWnd, HWND_TOP, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN),
			SWP_FRAMECHANGED | SWP_NOACTIVATE);
		ShowWindow(hWnd, SW_MAXIMIZE);
	}

	// �t���O��ύX
	isFullscreen = !isFullscreen;
}