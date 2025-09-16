//=========================================
//
// �v���C���[�̗͏��� [ playerlifegage.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _PLAYERLIFEGAGE_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYERLIFEGAGE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gage.h"

//**********************
// �O���錾
//**********************
class CPlayer;
class CObject;

//*************************
// �̗̓Q�[�W�N���X���`
//*************************
class CPlayerLifeGage : public CGage
{
public:
	//**********************
	// �Q�[�W�̎�ޒ�`
	//**********************
	enum GAGE
	{
		GAGE_FRAME,
		GAGE_BAR,
		GAGE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CPlayerLifeGage();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[�E�Q�b�^�[
	void SetTexture(int Type);
	void SetGage(int type) { m_gage = type; }
	void SetShake(bool isFlags) { m_isShake = isFlags; }
	int GetGage(void) const { return m_gage; }
	
	// �ÓI�����o�֐�
	static CPlayerLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype);

private:
	static constexpr float GAGE_WIDTH = 40.0f;	// ��l�Ɋ|����{��
	static constexpr float GAGE_HEIGHT = 45.0f; // �Q�[�W�̍����̌Œ�l

	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	int m_nLifeLength;		// �o�[�̒�����l
	int m_nMaxLifeLength;	// �ŏ��̗̑͒l
	int m_gage;				// �񋓕ϐ�
	int m_nMaxLife;			// �ő厞�̗̑�
	int m_nShakeTimer;		// �U������
	float m_fShakeAmplitude;// �U����
	float m_fShakeOffset;	// �I�t�Z�b�g

	bool m_isShake;			// �U�����邩�ǂ���

	CPlayer* m_pPlayer;		// �v���C���[�N���X�|�C���^
	D3DXVECTOR3 m_basePos;	// ����W
};

#endif
