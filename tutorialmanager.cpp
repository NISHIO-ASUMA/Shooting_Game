//=================================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.cpp ]
// Author: Asuma Nishio
//
//=================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorialmanager.h"
#include "tutorialui.h"
#include "manager.h"
#include "fade.h"
#include "game.h"
#include "sceneloader.h"
#include "meshdome.h"
#include "meshcylinder.h"
#include "meshfield.h"
#include "player.h"
#include "tutotask.h"
#include "tutorialboss.h"
#include "effectpiler.h"
#include "exitpoint.h"
#include "block.h"
#include "charge.h"

//==========================
// �R���X�g���N�^
//==========================
CTutorialManager::CTutorialManager()
{
	// �l�̃N���A
	m_pTutoui = nullptr;
	m_pTask = nullptr;
	m_isFreeDone = false;
	m_Tasktype = TASKTYPE_MOVE;
}
//==========================
// �f�X�g���N�^
//==========================
CTutorialManager::~CTutorialManager()
{
	// ����
}
//==========================
// ����������
//==========================
HRESULT CTutorialManager::Init(void)
{
	// �V�[���e�L�X�g�ǂݍ���
	CSceneLoader::SplitLoad(1);

	// �{�X����
	CTutorialBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f));

	// �^�X�N����
	m_pTask = new CTutoTask;

	// null����Ȃ�������
	if (m_pTask != nullptr)
	{
		// ����������
		m_pTask->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==========================
// �I������
//==========================
void CTutorialManager::Uninit(void)
{
	// null����Ȃ�������
	if (m_pTask != nullptr)
	{
		// �I������
		m_pTask->Uninit();

		// �j��
		delete m_pTask;

		// null������
		m_pTask = nullptr;
	}
}
//==========================
// �X�V����
//==========================
void CTutorialManager::Update(void)
{
	// �^�X�N�N���X�̍X�V����
	if (m_pTask != nullptr)
	{
		m_pTask->Update();
	}

	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �ԍ��擾
	int nIdx = m_pTask->GetTaskIndex();

	// �Ǘ��t���O
	bool isCheck = false;
	static bool isFinish = false;
	static bool isJump = false;
	static bool isLaserActionDone = false;

	// ���ݔԍ��ɉ����ĕύX
	switch (nIdx)
	{
	case CTutorialManager::TASKTYPE_MOVE:	// �ړ�����
		if ((pKey->GetPress(DIK_A) || pKey->GetPress(DIK_D)) ||
			(pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT)))
		{
			isCheck = true;
		}

		break;

	case CTutorialManager::TASKTYPE_ATTACK:	// �U������

		if ((pKey->GetPress(DIK_RETURN) || pJoyPad->GetPress(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
		}
		break;
	case CTutorialManager::TASKTYPE_JUMP:	// �W�����v����

		if ((pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A)))
		{
			isCheck = true;
		}
		break;

	case CTutorialManager::TASKTYPE_JUMPATTACK: // �W�����v�U��

		// �W�����v������t���O�𗧂Ă�
		if (pKey->GetTrigger(DIK_SPACE) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_A))
		{
			isJump = true;
		}

		// �W�����v�ς݃t���O�������ԂōU��
		if (isJump && (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_X)))
		{
			isCheck = true;
			isJump = false; // ��x���������烊�Z�b�g
		}
		break;

	case CTutorialManager::TASKTYPE_LASER: // ����؂�ւ�

		// �`���[�W���Z
		CCharge::AddCharge(100.0f);

		// �t���O�L�����@���� �L�[����
		if ((pKey->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B)) && CCharge::GetChargeFlag())
		{
			isCheck = true;
		}
		break;

	case CTutorialManager::TASKTYPE_LASERACTION: // ���[�U�[�U��

		// �L�[���͂��Ă���
		if (pKey->GetPress(DIK_RETURN) || pJoyPad->GetPress(pJoyPad->JOYKEY_X))
		{
			// ���Z
			CCharge::DecCharge(0.5f);
		}

		if (!CCharge::GetChargeFlag() && !isLaserActionDone)
		{
			isCheck = true;
			isLaserActionDone = true;
		}

		break;

	case CTutorialManager::TASKTYPE_FREE: // �t���[
		if (!m_isFreeDone)  // �܂��������ĂȂ��Ƃ�����
		{
			isFinish = true;
			m_isFreeDone = true; // 1�񏈗������烍�b�N
		}
		break;

	default:
		break;
	}

	if (isFinish)
	{
		// �|�C���g����
		CExitPoint::Create(D3DXVECTOR3(0.0f, 0.0f, -550.0f), 0.5f);

		// �u���b�N����
		CBlock::Create("data\\MODEL\\STAGEOBJ\\yajirusi.x", D3DXVECTOR3(0.0f, 180.0f, -550.0f), D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f), 0.0f,1);
		CBlock::Create("data\\MODEL\\STAGEOBJ\\Billboard_kanban.x", D3DXVECTOR3(0.0f, 190.0f, -550.0f), VECTOR3_NULL, 0.0f, 0);

		// ����������
		isFinish = false;
	}

	// ���͂��L����
	if (isCheck)
	{
		// �T�E���h�Đ�
		CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_CLEAR);

		// ���ɐi��
		m_pTask->NextTask();
	}
}