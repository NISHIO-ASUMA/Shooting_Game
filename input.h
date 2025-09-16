//====================================
//
// ���͊֐� [ input.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _INPUT_H_ // ���̃}�N����`������ĂȂ�������
#define _INPUT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*******************************
// ���͐e�N���X���`
//*******************************
class CInput
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CInput();
	~CInput();

	// ���z�E�������z�֐�
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(void) = 0;

	// �Q�b�^�[
	LPDIRECTINPUTDEVICE8 GetInputDevice(void);

protected:
	static LPDIRECTINPUT8 m_pInput; // ���͕ϐ�
	LPDIRECTINPUTDEVICE8 m_pDevice; // ���̓f�o�C�X
};

//*******************************
// �L�[�{�[�h�N���X���`
//*******************************
class CInputKeyboard : public CInput
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CInputKeyboard();
	~CInputKeyboard();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �Q�b�^�[
	bool GetPress(int nKey);
	bool GetTrigger(int nKey);
	bool GetRelease(int nKey);
	bool GetRepeat(int nKey,int nMaxTime);

private:
	static inline constexpr int KEY_MAX = 256;

	BYTE m_aKeystate[KEY_MAX]; // �L�[���͏��
	BYTE m_aOldState[KEY_MAX]; // �ߋ��̓��͓��e��ۑ�

	int m_nKeyPressCount;
};

//*******************************
// �Q�[���p�b�h�N���X���`
//*******************************
class CJoyPad : public CInput
{
public:
	//*********************************
	// �W���C�p�b�h�̃L�[�̗񋓌^
	//*********************************
	enum JOYKEY
	{
		JOYKEY_UP,			 // �\���L�[(��)
		JOYKEY_DOWN,		 // �\���L�[(��)
		JOYKEY_LEFT,		 // �\���L�[(��)
		JOYKEY_RIGHT,		 // �\���L�[(�E)
		JOYKEY_START,		 // �X�^�[�g�L�[
		JOYKEY_BACK,		 // �o�b�N�L�[
		JOYKEY_LS,			 // L3(L�X�e�B�b�N)
		JOYKEY_RS,			 // R3(R�X�e�B�b�N)
		JOYKEY_LEFT_B,		 // LB�L�[
		JOYKEY_RIGHT_B,		 // RB�L�[
		JOYKEY_LEFT_TRIGGER, // LT�L�[
		JOYKEY_RIGHT_TRIGGER,// RT�L�[
		JOYKEY_A,			 // A�{�^��
		JOYKEY_B,			 // B�{�^��
		JOYKEY_X,			 // X�{�^��
		JOYKEY_Y,			 // Y�{�^��
		JOYKEY_MAX			 // �p�b�h�̍ő吔
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CJoyPad();
	~CJoyPad();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	void UpdateVibration(void);

	// �Z�b�^�[
	void SetVibration(int leftMotor, int rightMotor, int durationMs);

	// �Q�b�^�[
	bool GetPress(JOYKEY Key);
	bool GetTrigger(JOYKEY Key);
	bool GetRelease(JOYKEY Key);
	bool GetRepeat(JOYKEY Key, int nMaXTime);
	bool GetLeftStick(void);

	XINPUT_STATE* GetStickAngle(void) { return &m_joyKeyState; }

private:
	XINPUT_STATE m_joyKeyState;		   // �W���C�p�b�h�̃v���X���
	XINPUT_STATE m_OldKeyState;		   // �ߋ��̃W���C�p�b�h���͏��
	XINPUT_STATE m_joyKeyStateTrigger; // �W���C�p�b�h�̃g���K�[���
	int m_nPressCount;

	//********************
	// �U���֐�
	//********************
	int m_leftMotor; // �����[�^�[�̋���
	int m_rightMotor; // �E���[�^�[�̋���
	DWORD m_VibrationEndTime; // �U���I������
	bool m_isVibration;   // �U�������ǂ���
};

//*******************************
// �}�E�X�N���X���`
//*******************************
class CInputMouse : public CInput
{
public:
	//********************
	// �}�E�X�̗񋓌^
	//********************
	enum MOUSE
	{
		MOUSE_LEFT = 0,
		MOUSE_RIGHT,
		MOUSE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CInputMouse();
	~CInputMouse();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	// �Z�b�^�[
	void SetCursorVisibility(bool visible);

	// �Q�b�^�[
	bool GetTriggerDown(int button_type);
	bool GetTriggerUp(int button_type);
	bool GetPress(int button_type);
	bool GetState(DIMOUSESTATE* mouseState);
	D3DXVECTOR2 GetMouseVelocity() { return D3DXVECTOR2((float)m_CurrentMouseState.lX, (float)m_CurrentMouseState.lY); }
	D3DXVECTOR2 GetMouseOldVelocity() { return D3DXVECTOR2((float)m_PrevState.lX, (float)m_PrevState.lY); }
	BOOL IsMouseWheelPresent(void);

private:
	DIMOUSESTATE m_PrevState;	 
	DIMOUSESTATE m_CurrentMouseState;
};
#endif