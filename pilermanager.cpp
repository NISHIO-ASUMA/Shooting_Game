//===============================================
//
// �~���U���Ǘ����� [ pilermanager.cpp ]
// Author : Asuma Nishio
//
//===============================================

//**********************************
// �C���N���[�h�t�@�C���錾
//**********************************
#include "pilermanager.h"
#include "meshpiler.h"
#include "meshcircle.h"
#include "effectsmoke.h"
#include "manager.h"

//**********************************
// ���O���
//**********************************
namespace PILERMANAGERINFO
{
	constexpr int MAX_ACTIVETIME = 600;	// �ő�J�E���g
	constexpr int SIRCLECOUNT = 20;		// �~�`�����J�E���g
	constexpr int PILERCOUNT = 45;		// �~�������J�E���g
	constexpr int RANDAM = 3;			// �����������_���̍ō��l
	constexpr int ACTIVEBACE = 3;		// �����K��l
};

//===============================
// �R���X�g���N�^
//===============================
CPilerManager::CPilerManager()
{
	// �l�̃N���A
	m_nTimer = NULL;
	m_nCount = NULL;
	m_nActiveTime = NULL;
	m_LastCirclePos = VECTOR3_NULL;
	m_State = STATE_IDLE;
}
//===============================
// �f�X�g���N�^
//===============================
CPilerManager::~CPilerManager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CPilerManager::Init(void)
{
	// �ϐ��̏�����
	m_nTimer = NULL;
	m_nCount = NULL;
	m_State = STATE_IDLE;
	m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CPilerManager::Uninit(void)
{
	// ����
}
//===============================
// �X�V����
//===============================
void CPilerManager::Update(D3DXVECTOR3* DestPos)
{
	// �C�x���g�J�������[�h�Ȃ�
	if (CManager::GetCamera()->GetMode() == CManager::GetCamera()->MODE_EVENT) return;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return;

	// �A�N�e�B�u�^�C�������Z
	m_nActiveTime--;

	// 0�ȉ��ɂȂ�����
	if (m_nActiveTime <= 0)
	{
		// �����_���l��ݒ�
		int nNumActive = (rand() % PILERMANAGERINFO::RANDAM) + PILERMANAGERINFO::ACTIVEBACE;

		switch (m_State)
		{
		case STATE_IDLE:	// �ҋ@��
		
			// �J�E���g�����Z
			m_nTimer++;

			// ��������
			if (m_nTimer > PILERMANAGERINFO::SIRCLECOUNT)
			{
				// �o�����Đ�
				pSound->PlaySound(CSound::SOUND_LABEL_CIRCLE);

				// �T�[�N���o�� ( �n�ʌŒ� )
				CMeshCircle::Create(D3DXVECTOR3(DestPos->x,0.0f,DestPos->z));
				
				// �o�������ʒu��ۑ�
				m_LastCirclePos = D3DXVECTOR3(DestPos->x, 0.0f, DestPos->z);

				// �^�C�������Z�b�g
				m_nTimer = NULL;

				// ��Ԃ�ύX
				m_State = STATE_WAIT_PILER;
			}
			break;
		

		case STATE_WAIT_PILER:	// �ҋ@��

			// �^�C�������Z
			m_nTimer++;

			// ��������
			if (m_nTimer > PILERMANAGERINFO::PILERCOUNT)
			{
				// �~���o��
				CMeshPiler::Create(m_LastCirclePos);

				m_LastCirclePos = VECTOR3_NULL;

				// �o���񐔂𑝂₷
				m_nCount++;	

				// �^�C���J�E���g��������
				m_nTimer = NULL;

				if (m_nCount >= nNumActive)
				{
					// ��ԕύX
					m_State = STATE_COOLTIME;
				}
				else
				{
					// ��ԕύX
					m_State = STATE_IDLE;
				}
			}
			break;

		case STATE_COOLTIME:	// �N�[���^�C��

			// �J�E���g�����Z
			m_nTimer++;

			// 10�b��������
			if (m_nTimer > PILERMANAGERINFO::MAX_ACTIVETIME)
			{
				// ���Z�b�g���čĂъJ�n
				m_nTimer = NULL;
				m_nCount = NULL;
				m_State = STATE_IDLE;
				m_nActiveTime = PILERMANAGERINFO::MAX_ACTIVETIME;
			}
			break;
		}
	}
}