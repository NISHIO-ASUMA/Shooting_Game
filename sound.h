//=====================================
//
// �T�E���h���� [ sound.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SOUND_H_ // ���̃}�N����`������ĂȂ�������
#define _SOUND_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �T�E���h�N���X���`
//******************************
class CSound
{
public:
	//***************************
	// �T�E���h�̎�ޗ񋓌^
	//***************************
	enum SOUND_LABEL
	{
		SOUND_LABEL_TITLE_BGM,		// �^�C�g��BGM
		SOUND_LABEL_GAMEBGM,		// �Q�[��BGM
		SOUND_LABEL_RESULTBGM,		// ���U���gBGM
		SOUND_LABEL_TUTORIALBGM,	// �`���[�g���A��BGM
		SOUND_LABEL_LOSERESULTBGM,	// �s�k���U���g

		SOUND_LABEL_SELECT, // �L�[�I��SE
		SOUND_LABEL_RETURN, // ����L�[SE
		SOUND_LABEL_ITEM,	// �A�C�e��SE
		SOUND_LABEL_ALART,	// �x����SE
		SOUND_LABEL_BULLET,	// �ʏ�eSE
		SOUND_LABEL_LASER,	// ���[�U�[SE
		SOUND_LABEL_LIFE,	// ��SE
		SOUND_LABEL_DAMAGE, // �_���[�WSE
		SOUND_LABEL_CIRCLE,	// ���b�V���U��SE
		SOUND_LABEL_CLEAR,	// �^�X�N����SE
		SOUND_LABEL_GUARD,	// �K�[�h��SE
		SOUND_LABEL_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CSound();
	~CSound();

	// �����o�֐�
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

private:
	//*****************************
	// �T�E���h���̍\���̒�`
	//*****************************
	struct SOUNDINFO
	{
		const char* pFilename;	// �t�@�C����
		int nCntLoop;			// ���[�v�J�E���g
	};

	//******************************
	// �T�E���h�̏��񋓌^�錾
	//******************************
	SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX] =
	{
		{"data/BGM/titlebgm.wav", -1},		 // �^�C�g��BGM
		{"data/BGM/gamebgm.wav",-1},		 // �Q�[��BGM
		{"data/BGM/resultbgm.wav",-1},		 // ���U���gBGM
		{"data/BGM/tutorialbgm.wav",-1},	 // �`���[�g���A��BGM
		{"data/BGM/LoseResult.wav",-1},		 // �s�k���U���gBGM

		{"data/SE/keyselect.wav",0},		 // �I���L�[SE
		{"data/SE/keyenter.wav",0},			 // ����L�[SE
		{"data/SE/Itemse.wav",0},			 // �A�C�e��SE
		{"data/SE/Alart.wav",0},			 // �x����SE
		{"data/SE/BulletSe.wav",0},			 // �ʏ�e
		{"data/SE/LaserBullet.wav",0},		 // ���[�U�[�e
		{"data/SE/LifeSe.wav",0},			 // ��SE
		{"data/SE/Damage.wav",0},			 // �_���[�WSE
		{"data/SE/MeshCircle.wav",0},		 // ���b�V���U��SE
		{"data/SE/TutoClear.wav",0},		 // �^�X�N����SE
		{"data/SE/Guard.wav",0},			 // �K�[�h��SE
	};

	IXAudio2* m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
	int m_SoundCount;										// �T�E���h�̃J�E���g
	int m_SoundInterval;									// �C���^�[�o���J�E���g

};

#endif