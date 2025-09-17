//=====================================
//
// �{�X��ԊǗ����� [ bossstate.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bossstate.h"
#include "bossattackstate.h"
#include "manager.h"
#include "player.h"
#include "gamemanager.h"
#include "rubblemanager.h"

//===========================
// �R���X�g���N�^
//===========================
CBossStateBace::CBossStateBace()
{
	// �l�̃N���A
	m_ID = ID_NEUTRAL;
	m_pBoss = nullptr;
}
//===========================
// �f�X�g���N�^
//===========================
CBossStateBace::~CBossStateBace()
{
	// ����
}


//===========================
// �ҋ@��ԃR���X�g���N�^
//===========================
CBossStateNeutral::CBossStateNeutral(int nTime) : m_CoolTime(nTime), m_nCurrentState(0)
{
	// ID�Z�b�g
	SetID(ID_NEUTRAL);
}
//===========================
// �ҋ@��ԃf�X�g���N�^
//===========================
CBossStateNeutral::~CBossStateNeutral()
{
	// ����
}
//===========================
// �ҋ@��ԊJ�n����
//===========================
void CBossStateNeutral::OnStart(void)
{
	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL,true,5,true);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(m_CoolTime);
}
//===========================
// �ҋ@��ԍX�V����
//===========================
void CBossStateNeutral::OnUpdate(void)
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	// �t���O���L�����Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_ANIM && m_pBoss->GetIsSet() == true)
	{
		// �A�j���[�V�����ŃC�x���g���[�V����
		m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_RUBBLE);

		return;
	}

	// �N�[���^�C�����Z
	m_pBoss->DecCoolTime();

	// �N�[���^�C���I����
	if (m_pBoss->GetCoolTime() <= 0)
	{
		// �����_���Ńp�^�[��������
		int attackType = rand() % 7;

		switch (attackType)
		{
		case CBoss::TYPE_ACTION:  // �E�艣��
			m_pBoss->ChangeState(new CBosshandAttack(), ID_ACTION);
			return;

		case CBoss::TYPE_IMPACT: // �@����
			m_pBoss->ChangeState(new CBossimpactAttack(), ID_ACTION);
			return;

		case CBoss::TYPE_CIRCLE: // �ガ����
			m_pBoss->ChangeState(new CBosscircleAttack(), ID_ACTION);
			return;

		case CBoss::TYPE_ARMRIGHTLEFT: // �U�艺�낵
			m_pBoss->ChangeState(new CBossArmAttack(), ID_ACTION);
			return;
		}
	}
	else
	{
		// �N�[���^�C�����̓j���[�g�������[�V�����Đ�
		m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_NEUTRAL, false, 0,false);
	}
}
//===========================
// �ҋ@��ԏI������
//===========================
void CBossStateNeutral::OnExit(void)
{
	// ����
}


//===========================
// �R���X�g���N�^
//===========================
CBossStateEvent::CBossStateEvent()
{
	// ID�Z�b�g
	SetID(ID_EVENT);
}
//===========================
// �f�X�g���N�^
//===========================
CBossStateEvent::~CBossStateEvent()
{
	//����
}
//===========================
// �C�x���g��ԊJ�n�֐�
//==========================
void CBossStateEvent::OnStart(void)
{
	// ���[�V�����Z�b�g
	m_pBoss->GetMotion()->SetMotion(CBoss::TYPE_RUBBLE);

	// �N�[���^�C���Z�b�g
	m_pBoss->SetCoolTime(250);

	// �}�l�[�W���[�擾
	CRubbleManager* pRubble = CGameManager::GetRubble();
	if (pRubble == nullptr) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	if (pCamera == nullptr) return;

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;

	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	playerPos.y = 0.0f;

	// ��������ƍ���
	float backDistance = 590.0f;
	float heightOffset = 120.0f;

	// �v���C���[�̌����̋t�������擾
	float rotY = pPlayer->GetRotDest().y;
	D3DXVECTOR3 backwardVec = D3DXVECTOR3(-sinf(rotY), 0.0f, -cosf(rotY));

	// �J�����ʒu
	D3DXVECTOR3 camPos = playerPos + backwardVec * backDistance;
	camPos.y += heightOffset; // �v���C���[��菭����

	// ����
	D3DXVECTOR3 targetPos = playerPos + D3DXVECTOR3(0.0f, 150.0f, 0.0f); // Y��傫�����Č��グ��

	// �J�����`�F���W
	pCamera->SetCameraMode(pCamera->MODE_EVENT);

	// �J�����̐U��
	pCamera->ShakeCamera(240);

	// �����_���ŏo�����銢�I�̃t�@�C����ݒ�
	int nType = rand() % 3;

	// ���I�ǂݍ���
	pRubble->LoadSplitFile(nType);

	// �C�x���g�J�����J�n
	pCamera->StartEventCamera(camPos, targetPos, 250);
}
//===========================
// �C�x���g��ԍX�V�֐�
//==========================
void CBossStateEvent::OnUpdate(void)
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
//===========================
// �C�x���g��ԏI���֐�
//==========================
void CBossStateEvent::OnExit(void)
{
	// ����
}
