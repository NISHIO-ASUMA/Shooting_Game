//==========================================================
//
// �L�����N�^�[�p�����[�^�[�ݒ�֐� [ charactor.h ]
// Author : Asuma Nishio
//
//==========================================================

#ifndef _CHARACTER_H_ // ���̃}�N����`������ĂȂ�������
#define _CHARACTER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"
#include "object.h"
#include "motion.h"
#include "model.h"

//*****************************
// �L�����N�^�[2D�N���X���`
//*****************************
class CCharacter: public CObject2D
{
public:

	// �L�����N�^�[��Ԃ�ݒ�
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_INVINCIBLE,
		STATE_DAETH,
		STATE_MAX
	};

	CCharacter();
	~CCharacter();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void CharactorMove(float fMove);
	void SetLife(int nLife) { m_nLife = nLife; }
	int GetLife(void) { return m_nLife; }
	void SetAnim2D(int nMaxPattern, int nAnimCount, float TexU, float TexV);

private:
	int m_nLife;	     // ���ݑ̗�
	int m_nAnimCount2D;	 // 2D�A�j���[�V�����J�E���g
	int m_nAnimPattern2D; // 2D�A�j���[�V�����p�^�[��
	int m_nMaxLife;		 // �ő�̗�
	float m_fMove;		// �ړ���
};

//*********************************************
// �L�����N�^�[3D�N���X���` ( �p�� : CObject )
//*********************************************
class CCharactor3D : public CObject
{
public:
	// �L�����N�^�[��Ԃ�ݒ�
	enum STATE
	{
		STATE_NONE = 0,
		STATE_NORMAL,
		STATE_DAMAGE,
		STATE_INVINCIBLE,
		STATE_DAETH,
		STATE_MAX
	};

	CCharactor3D(int nPriority = 4);
	~CCharactor3D();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	int GetLife(void)const { return m_nLife; }
	void SetLife(int nLife) { m_nLife = nLife; }

private:
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;	// �ړI�̊p�x
	int m_nLife;			// ���ݑ̗�	
	STATE m_state;
};
#endif
