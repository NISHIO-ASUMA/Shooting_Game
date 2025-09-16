//====================================
//
// ���͊֐� [ input.cpp ]
// Author: Asuma Nishio
//
//=====================================

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "input.h"
#include "main.h"

//********************************
// �}�N����`
//********************************
constexpr int PREVSTICK = 1000;// L�X�e�B�b�N�̂������l

//********************************
// �ÓI�����o�ϐ��錾
//********************************
LPDIRECTINPUT8 CInput::m_pInput = nullptr; // ���͏��

//=======================
// �R���X�g���N�^
//=======================
CInput::CInput()
{
	// �l�̃N���A
	m_pDevice = NULL;
	m_pInput = NULL;
}
//=======================
// �f�X�g���N�^
//=======================
CInput::~CInput()
{
	// ����
}
//=======================
// ����������
//=======================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	// NULL�`�F�b�N
	if (m_pInput == NULL)
	{
		// DirectInput�I�u�W�F�N�g�̐���
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
		{
			return E_FAIL;
		}
	}

	return S_OK;
}
//=======================
// �I������
//=======================
void CInput::Uninit(void)
{
	// ���̓f�o�C�X�̔j��
	if (m_pDevice != nullptr)
	{
		m_pDevice->Unacquire();	// �A�N�Z�X���̔j��
		m_pDevice->Release();	// ���

		m_pDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}
//=======================
// ���̓f�o�C�X�̎擾
//=======================
LPDIRECTINPUTDEVICE8 CInput::GetInputDevice(void)
{
	return m_pDevice;
}

//====================================
// �L�[�{�[�h�N���X�̃R���X�g���N�^
//====================================
CInputKeyboard::CInputKeyboard()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < KEY_MAX; nCnt++)
	{
		m_aKeystate[nCnt] = {};
		m_aOldState[nCnt] = {};
	}

	m_pDevice = NULL;
	m_pInput = NULL;
	m_nKeyPressCount = NULL;
}
//====================================
// �L�[�{�[�h�N���X�̃f�X�g���N�^
//====================================
CInputKeyboard::~CInputKeyboard()
{
	// ����
}
//====================================
// �L�[�{�[�h�N���X�̏���������
//====================================
HRESULT CInputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �e�N���X�̏�����
	CInput::Init(hInstance, hWnd);

	// ���̓f�o�C�X����
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevice, NULL)))	
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//====================================
// �L�[�{�[�h�N���X�̏I������
//====================================
void CInputKeyboard::Uninit(void)
{
	// �e�N���X�̏I������
	CInput::Uninit();
}
//====================================
// �L�[�{�[�h�N���X�̍X�V����
//====================================
void CInputKeyboard::Update(void)
{
	// �L�[�{�[�h�̓��͏��i�[�p�ϐ�
	BYTE aKeyState[KEY_MAX];

	for (int nCntkey = 0; nCntkey < KEY_MAX; nCntkey++)
	{
		m_aOldState[nCntkey] = m_aKeystate[nCntkey];	// �L�[�{�[�h�̃v���X����ۑ�
	}

	//���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCnt = 0; nCnt < KEY_MAX; nCnt++)
		{
			m_aKeystate[nCnt] = aKeyState[nCnt];	// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevice->Acquire();			// �L�[�{�[�h�̃A�N�Z�X�����l��
	}
}
//====================================
// �L�[�{�[�h�̃v���X���̎擾
//====================================
bool CInputKeyboard::GetPress(int nKey)
{
	return (m_aKeystate[nKey] & 0x80) ? true : false;		// �O�����Z�q���g�p
}
//====================================
// �L�[�{�[�h�̃g���K�[���̎擾
//====================================
bool CInputKeyboard::GetTrigger(int nKey)
{
	// �t���O�ϐ�
	bool isTrigger = false;

	if (m_aKeystate[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		isTrigger = true;
	}

	// ���ʂ�Ԃ�
	return isTrigger;
}
//====================================
// �L�[�{�[�h�̃����[�X���̎擾
//====================================
bool CInputKeyboard::GetRelease(int nKey)
{
	// �t���O�ϐ�
	bool isRelease = false;

	if (m_aKeystate[nKey] & 0x80 && !(m_aOldState[nKey] & 0x80))
	{
		isRelease = true;
	}

	// ���ʂ�Ԃ�
	return isRelease;
}
//====================================
// �L�[�{�[�h�̃��s�[�g���̎擾
//====================================
bool CInputKeyboard::GetRepeat(int nKey,int nMaxTime)
{
	bool isRepeat = false;

	// �L�[�J�E���g�����Z
	m_nKeyPressCount++;

	if (m_aOldState[nKey] & 0x80 && (m_aKeystate[nKey] & 0x80) && nMaxTime <= m_nKeyPressCount)
	{
		isRepeat = true;
		m_nKeyPressCount = 0;
	}

	return isRepeat;
}

//====================================
// �Q�[���p�b�h�̃R���X�g���N�^
//====================================
CJoyPad::CJoyPad()
{
	// �l�̃N���A
	m_joyKeyState = {};
	m_joyKeyStateTrigger = {};
	m_OldKeyState = {};
	m_pDevice = NULL;
	m_pInput = NULL;
	m_nPressCount = NULL;

	// �U���p�ϐ�
	m_isVibration = false;
	m_leftMotor = NULL;
	m_rightMotor = NULL;
	m_VibrationEndTime = NULL;
}
//====================================
// �Q�[���p�b�h�̃f�X�g���N�^
//====================================
CJoyPad::~CJoyPad()
{
	// ����
}
//====================================
// �Q�[���p�b�h�̏���������
//====================================
HRESULT CJoyPad::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �������̃N���A
	memset(&m_joyKeyState, 0, sizeof(XINPUT_STATE));

	// �������̃N���A
	memset(&m_joyKeyStateTrigger, 0, sizeof(XINPUT_STATE));

	// Xinput�̃X�e�[�g��ݒ�(�L����)
	XInputEnable(true);

	return S_OK;
}
//====================================
// �Q�[���p�b�h�̏I������
//====================================
void CJoyPad::Uninit(void)
{
	// �e�N���X�̏I������
	CInput::Uninit();

	// Xinput�̃X�e�[�g�𖳌���
	XInputEnable(false);
}
//====================================
// �Q�[���p�b�h�̍X�V����
//====================================
void CJoyPad::Update(void)
{
	// �O����͒l
	m_OldKeyState = m_joyKeyState;

	XINPUT_STATE joykeyState;			// ���͏����擾

	// �W���C�p�b�h�̏�Ԃ��擾
	if (XInputGetState(0, &joykeyState) == ERROR_SUCCESS)
	{
		WORD Button = joykeyState.Gamepad.wButtons;				// �������Ƃ��̓��͏��
		WORD OldButton = m_joyKeyState.Gamepad.wButtons;		// 1F�O�̓��͏��

		m_joyKeyStateTrigger.Gamepad.wButtons = Button & ~OldButton;

		m_joyKeyState = joykeyState;							// �W���C�p�b�h�̃v���X����ۑ�(�i�[)
	}
	else
	{
		// ��ԃ��Z�b�g
		ZeroMemory(&m_joyKeyState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_joyKeyStateTrigger, sizeof(XINPUT_STATE));
	}
}
//====================================
// �Q�[���p�b�h�U���֐�
//====================================
void CJoyPad::SetVibration(int leftMotor, int rightMotor, int durationMs)
{
	m_leftMotor = leftMotor;	// ���̃��[�^�[�̋���
	m_rightMotor = rightMotor;  // �E���[�^�[�̋���
	m_VibrationEndTime = GetTickCount64() + durationMs; // �p������
	m_isVibration = true;		// �t���O��L����

	// XInput��ݒ�
	XINPUT_VIBRATION vibration = {};
	vibration.wLeftMotorSpeed = leftMotor;
	vibration.wRightMotorSpeed = rightMotor;
	XInputSetState(0, &vibration); // �R���g���[���[�ɓK��
}
//==========================================================================================================
// �Q�[���p�b�h�U���X�V����
//==========================================================================================================
void CJoyPad::UpdateVibration(void)
{
	if (m_isVibration == true && GetTickCount64() >= m_VibrationEndTime)
	{// �U�����Ԃ��o�߂������~
		XINPUT_VIBRATION vibration = {};
		XInputSetState(0, &vibration);
		m_isVibration = false;
	}
}
//====================================
// �Q�[���p�b�h�̃v���X���̎擾
//====================================
bool CJoyPad::GetPress(JOYKEY Key)
{
	return (m_joyKeyState.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//====================================
// �Q�[���p�b�h�̃g���K�[���̎擾
//====================================
bool CJoyPad::GetTrigger(JOYKEY Key)
{
	return (m_joyKeyStateTrigger.Gamepad.wButtons & (0x01 << Key)) ? true : false;
}
//====================================
// �Q�[���p�b�h�̃����[�X���̎擾
//====================================
bool CJoyPad::GetRelease(JOYKEY Key)
{
	// �t���O�ϐ��錾
	bool isRelease = false;

	if (m_OldKeyState.Gamepad.wButtons & (0x01 << Key) && !((m_OldKeyState.Gamepad.wButtons & (0x01 << Key))))
	{
		isRelease = true;
	}

	// ���ʂ�Ԃ�
	return false;
}
//====================================
// �Q�[���p�b�h�̃��s�[�g���̎擾
//====================================
bool CJoyPad::GetRepeat(JOYKEY Key,int nMaXTime)
{
	// �t���O�ϐ��錾
	bool isRepeat = false;

	// ���t���[�����L�[��������Ă���
	if (m_joyKeyState.Gamepad.wButtons & (0x01 << Key))
	{
		m_nPressCount++;

		if (nMaXTime <= m_nPressCount)
		{
			isRepeat = true;
			m_nPressCount = 0;
		}
	}
	else
	{
		m_nPressCount = 0;
	}

	// ���ʂ�Ԃ�
	return isRepeat;
}
//====================================
// �p�b�h��L�X�e�B�b�N����			
//====================================
bool CJoyPad::GetLeftStick(void)
{
	// ���[�J���ϐ��錾
	bool isLstick = false;

	// �X�e�B�b�N�̓��͒l���������l�𒴂��Ă��Ȃ����
	if (m_joyKeyState.Gamepad.sThumbLX >=  PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLX <= -PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLY >=  PREVSTICK  ||
		m_joyKeyState.Gamepad.sThumbLY <= -PREVSTICK)
	{
		isLstick = true;
	}

	// ���ʂ�Ԃ�
	return isLstick;
}
//====================================
// �}�E�X�̃R���X�g���N�^
//====================================
CInputMouse::CInputMouse()
{
	// �l�̃N���A
	m_CurrentMouseState = {};
	m_PrevState = {};
	m_pDevice = NULL;
	m_pInput = NULL;
}
//====================================
// �}�E�X�̃f�X�g���N�^
//====================================
CInputMouse::~CInputMouse()
{
	// ����
}
//====================================
// �}�E�X�̏���������
//====================================
HRESULT CInputMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �e�N���X�̏���������
	CInput::Init(hInstance,hWnd);

	if (FAILED(m_pInput->CreateDevice(
		GUID_SysMouse,
		&m_pDevice,
		NULL)))
	{
		return E_FAIL;
	}

	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse)))
	{
		return E_FAIL;
	}

	// �������[�h�̐ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(
		hWnd,
		DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	//�L�[�{�[�h�̃A�N�Z�X�����l��
	m_pDevice->Acquire();

	return S_OK;
}
//====================================
// �}�E�X�̏I������
//====================================
void CInputMouse::Uninit(void)
{
	// �e�N���X�̏I������
	CInput::Uninit();
}
//====================================
// �}�E�X�̍X�V����
//====================================
void CInputMouse::Update(void)
{
	// �ߋ��̏��Z�b�g
	m_PrevState.lX = m_CurrentMouseState.lX;
	m_PrevState.lY = m_CurrentMouseState.lY;

	// �ŐV�̏���ۑ�����
	m_PrevState = m_CurrentMouseState;

	// �ŐV�̃}�E�X�̏�Ԃ��X�V
	HRESULT	hr = m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_CurrentMouseState);

	// �擾�ł��Ȃ������ꍇ
	if (FAILED(hr))
	{
		// �}�E�X�f�o�C�X�̉��
		m_pDevice->Acquire();
	}

	// �}�E�X���W���擾����
	POINT p;
	GetCursorPos(&p);

	// �X�N���[�����W���N���C�A���g���W�ɕϊ�����
	ScreenToClient(FindWindowA(CLASS_NAME, WINDOW_NAME), &p);

	m_CurrentMouseState.lX = p.x;
	m_CurrentMouseState.lY = p.y;
}
//====================================
// �}�E�X�̃J�[�\���ݒ�
//====================================
void CInputMouse::SetCursorVisibility(bool visible)
{
	// �J�[�\���J�E���g
	static int cursurCount = 0;

	if (visible)
	{
		//�J�[�\����\��
		while (cursurCount < 0)
		{
			ShowCursor(TRUE);
			cursurCount++;
		}
	}
	else
	{
		//�J�[�\�����\��
		while (cursurCount >= 0)
		{
			ShowCursor(FALSE);
			cursurCount--;
		}
	}
}
//====================================
// �}�E�X�̃g���K�[�����擾
//====================================
bool CInputMouse::GetTriggerDown(int button_type)
{
	if (!(m_PrevState.rgbButtons[button_type] & (0x80)) &&
		m_CurrentMouseState.rgbButtons[button_type] & (0x80))
	{
		return true;
	}

	return false;
}
//====================================
// �}�E�X�̃����[�X���̎擾
//====================================
bool CInputMouse::GetTriggerUp(int button_type)
{
	if (m_PrevState.rgbButtons[button_type] & (0x80) &&
		!(m_CurrentMouseState.rgbButtons[button_type] & (0x80)))
	{
		return true;
	}

	return false;
}
//====================================
// �}�E�X�̃v���X���̎擾
//====================================
bool CInputMouse::GetPress(int button_type)
{
	return (m_CurrentMouseState.rgbButtons[button_type] & 0x80) ? true : false;
}
//====================================
// �}�E�X�̏�Ԃ��擾
//====================================
bool CInputMouse::GetState(DIMOUSESTATE* mouseState)
{
	// ���̓f�o�C�X���擾
	LPDIRECTINPUTDEVICE8 pMouse = GetInputDevice();

	if (pMouse == NULL)
	{
		return false;
	}

	// �}�E�X�̏�Ԃ��擾
	HRESULT hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

	if (FAILED(hr))
	{
		// ���̓f�o�C�X�����Z�b�g����Ă���ꍇ�A�Ď擾�����݂�
		if (hr == DIERR_INPUTLOST || hr == DIERR_NOTACQUIRED)
		{
			pMouse->Acquire();

			// �Ď擾�����݂�
			hr = pMouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)mouseState);

			if (FAILED(hr))
			{
				return false;
			}
		}
		else
		{
			//�G���[�̏ꍇ
			return false;
		}
	}

	return true; // ����Ɏ擾�ł����ꍇ

}
//====================================
// �}�E�X�z�C�[���̒l���擾
//====================================
BOOL CInputMouse::IsMouseWheelPresent(void)
{
	return (GetSystemMetrics(SM_MOUSEWHEELPRESENT) != 0);
}