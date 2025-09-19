//===============================================
//
// �{�X�̍U����ԊǗ����� [bossattackstate.cpp ]
// Author: Asuma Nishio
//
//===============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "state.h"
#include "bossattackstate.h"

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CBosshandAttack::CBosshandAttack()
{
	// ID�Z�b�g
	SetID(ID_ACTION);
}
//====================================
// �I�[�o�[���[�h�f�X�g���N�^
//====================================
CBosshandAttack::~CBosshandAttack()
{
	// ����
}
//====================================
// �J�n����
//====================================
void CBosshandAttack::OnStart(void)
{
	// �t���[��������
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// ��������
	m_pBoss->RollToPlayer();

	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_ACTION);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(180);
}
//====================================
// �X�V����
//====================================
void CBosshandAttack::OnUpdate(void)
{
	// ���݂̃N�[���^�C���擾
	int nCooltime = m_pBoss->GetCoolTime();

	if (nCooltime <= 0)
	{
		// ��ԕύX
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//====================================
// �I������
//====================================
void CBosshandAttack::OnExit(void)
{
	// ����
}



//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CBossimpactAttack::CBossimpactAttack()
{
	// ID���Z�b�g
	SetID(ID_ACTION);
}
//====================================
// �f�X�g���N�^
//====================================
CBossimpactAttack::~CBossimpactAttack()
{
	// ����
}
//====================================
// �X�e�[�g�J�n����
//====================================
void CBossimpactAttack::OnStart(void)
{
	// �t���[��������
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// ��������
	m_pBoss->RollToPlayer();

	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_IMPACT);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(160);
}
//====================================
// �X�e�[�g�X�V����
//====================================
void CBossimpactAttack::OnUpdate(void)
{
	// ���݂̃N�[���^�C���擾
	int nCooltime = m_pBoss->GetCoolTime();

	// �I�����肩�� �N�[���^�C�����Ȃ��Ȃ�����
	if (nCooltime <= 0)
	{
		// ��ԕύX
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//====================================
// �X�e�[�g�I������
//====================================
void CBossimpactAttack::OnExit(void)
{
	// ����
}

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CBosscircleAttack::CBosscircleAttack()
{
	// ID���Z�b�g
	SetID(ID_ACTION);
}
//====================================
// �f�X�g���N�^
//====================================
CBosscircleAttack::~CBosscircleAttack()
{
	// ����
}
//====================================
// �X�e�[�g�J�n�֐�
//====================================
void CBosscircleAttack::OnStart(void)
{
	// �t���[��������
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// ��������
	m_pBoss->RollToPlayer();

	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_CIRCLE);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(280);
}
//====================================
// �X�e�[�g�X�V�֐�
//====================================
void CBosscircleAttack::OnUpdate(void)
{
	// ���݂̃N�[���^�C���擾
	int nCooltime = m_pBoss->GetCoolTime();

	// �N�[���^�C�����Ȃ��Ȃ�����
	if (nCooltime <= 0)
	{
		// ��ԕύX
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//====================================
// �X�e�[�g�I���֐�
//====================================
void CBosscircleAttack::OnExit(void)
{
	// ����
}

//====================================
// �R���X�g���N�^
//====================================
CBossArmAttack::CBossArmAttack()
{
	// ID���Z�b�g
	SetID(ID_ACTION);
}
//====================================
// �f�X�g���N�^
//====================================
CBossArmAttack::~CBossArmAttack()
{
	// ����
}
//====================================
// �X�e�[�g�J�n�֐�
//====================================
void CBossArmAttack::OnStart(void)
{
	// �t���[��������
	m_pBoss->GetMotion()->SetResetFrame(NULL);

	// ��������
	m_pBoss->RollToPlayer();

	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_ARMRIGHTLEFT);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(320);
}
//====================================
// �X�e�[�g�X�V�֐�
//====================================
void CBossArmAttack::OnUpdate(void)
{
	// ���݂̃N�[���^�C���擾
	int nCooltime = m_pBoss->GetCoolTime();

	// �N�[���^�C�����Ȃ��Ȃ�����
	if (nCooltime <= 0)
	{
		// ��ԕύX
		m_pBoss->ChangeState(new CBossStateNeutral(180), ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}
}
//====================================
// �X�e�[�g�I���֐�
//====================================
void CBossArmAttack::OnExit(void)
{
	// ����
}