//=====================================
//
// �J�������� [ camera.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _CAMERA_H_ // ���̃}�N����`������ĂȂ�������
#define _CAMERA_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �O���錾
//**********************
class CInputMouse;

//**********************
// �J�����N���X���`
//**********************
class CCamera
{
public:
	//**********************
	// �J�������[�h�񋓌^
	//**********************
	enum MODE
	{
		MODE_NONE,
		MODE_PLAYER,
		MODE_LOCKON,
		MODE_MOUSE,
		MODE_SHAKE,
		MODE_EVENT,
		MODE_ANIM,
		MODE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CCamera();
	~CCamera();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);

	void MouseView(CInputMouse* pMouse);
	void LockOn(void);
	void PlayerFollow(void);
	void Rotation(void);
	void TitleCamera(void);
	void TutorialCamera(void);
	void AnimCamera(void);
	void UpdateAnimCamera(void);
	void UpdateShake(void);

	void Load(int nIdx);
	void Save(void);

	// �Z�b�^�[
	void StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame);
	void ShakeCamera(int WaveTime);
	void SetIsRotation(bool isFlags) { m_isRotation = isFlags; }
	void SetFinishRotation(bool isFlags) { m_isStopRotation = isFlags; }
	void SetCameraMode(int nMode) { m_pCamera.nMode = nMode; }
	void SetKey(bool isFlags) { m_isKey = isFlags; }
	void SetLoadPass(int nIdxPass) { m_nFileIdx = nIdxPass; }
	void SetAnim(bool isFlags) { m_isAnimTime = isFlags; }

	// �Q�b�^�[
	D3DXVECTOR3 GetRot(void) { return m_pCamera.rot; }
	D3DXVECTOR3 GetPos(void) { return m_pCamera.posV; }
	D3DXVECTOR3 GetPosR(void) { return m_pCamera.posR; }
	D3DXMATRIX GetMtxProjection(void) { return m_pCamera.mtxprojection; }
	int GetMode(void) { return m_pCamera.nMode; }
	bool GetShake(void) { return m_isShake; }
	bool GetAnim(void) { return m_isAnimTime; }

	// �t���O�����g
	bool GetIsRotation(void) { return m_isRotation; }
	bool GetFinishRotation(void) { return m_isStopRotation; }
	bool GetKeyFlag(void) { return m_isKey; }

private:
	// �萔�錾
	static constexpr int NUMKEY = 10;
	static constexpr int ANIMFILENUM = 2;

	//*************************
	// �C�x���g�t���[���\����
	//*************************
	struct EventData
	{
		bool isActive;		// �C�x���g���s����
		int	 frame;			// �o�߃t���[��
		int	 endFrame;		// �I���t���[��
		D3DXVECTOR3 startPosV;		// �J�n���_
		D3DXVECTOR3 startPosR;		// �J�n�����_
		D3DXVECTOR3 targetPosV;		// �ڕW���_
		D3DXVECTOR3 targetPosR;		// �ڕW�����_
	};


	//********************************
	// �J�����A�j���[�V�����L�[�\����
	//********************************
	struct AnimDataKey
	{
		float fPosVX;	// ���_X
		float fPosVY;	// ���_Y
		float fPosVZ;	// ���_Z

		float fPosRX;	// �����_X
		float fPosRY;	// �����_Y
		float fPosRZ;	// �����_Z

		float fRotX;	// ����X
		float fRotY;	// ����Y
		float fRotZ;	// ����Z
		int nAnimFrame; // �A�j���[�V�����̃t���[��
		float fDistance;// �J�����̋���
	};

	//**********************************
	// �J�����A�j���[�V�����f�[�^�\����
	//**********************************
	struct AnimData
	{
		AnimDataKey KeyInfo[NUMKEY];	// �\����
		int nNumKey; // �L�[�̍ő吔
		bool isLoop;	// ���[�v���邩�ǂ���
	};

	//*************************
	// �J�����\���̂��`
	//*************************
	struct Camera
	{
		D3DXMATRIX mtxprojection;	// �v���W�F�N�V�����}�g���b�N�X
		D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
		D3DXVECTOR3 posV, posR;		// ���_,�����_���W
		D3DXVECTOR3 rot;			// �p�x
		D3DXVECTOR3 vecU;			// �@���x�N�g��
		D3DXVECTOR3 posRDest;		// �ړI���W
		float fDistance;			// �J�����̋���
		int nMode;					// �J�����̃��[�h
		int nUseKey;				// �A�j���[�V�����g�p���ɓǂݎ��L�[��
		int nCntAnim;				// �J�E���g
		AnimData m_AnimData;	// �A�j���[�V�����f�[�^
	};

	EventData m_event;		// �C�x���g�p�f�[�^
	Camera m_pCamera;		// �J�����\���̕ϐ�

	int m_nShakeTime;				// �U������
	int m_nAnimNowKey;				// ���݃L�[No
	int m_nFileIdx;					// �t�@�C���C���f�b�N�X
	int m_nAnimShakeFlame;			// �A�j���[�V�����U���t���[��

	bool m_isRotation;		// ��]�������ǂ���
	bool m_isStopRotation;	// ��]�I��
	bool m_isSetPos;		// �{�X�����񂾂��ǂ����̃t���O
	bool m_isShake;			// �U�����邩�ǂ���
	bool m_isKey;			// �L�[���͔���
	bool m_isAnimTime;		// �A�j���[�V���������ǂ���
	bool m_isLoad;			// �ǂݍ��񂾂��ǂ���
	bool m_isStopCurrentAnim;

	D3DXVECTOR3 m_lastBossPos;		// �{�X�̍Ō�̍��W

	const char* ANIMFILE[ANIMFILENUM] =
	{
		"data\\Loader\\CameraInfo.txt",
		"data\\Loader\\CameraGameEnd.txt",
	};
};

#endif