//==========================================
//
// �Q�[���Ǘ����� [ gamemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "gamemanager.h"
#include "manager.h"
#include "debugproc.h"
#include "score.h"
#include "time.h"
#include "meshdome.h"
#include "meshfield.h"
#include "player.h"
#include "meshimpact.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "parameter.h"
#include "result.h"
#include "sound.h"
#include "item.h"
#include "barrierdurability.h"
#include "bullethorming.h"
#include "itemmanager.h"
#include "charge.h"
#include "sceneloader.h"
#include "ui.h"
#include "texture.h"
#include "pilermanager.h"
#include "spread.h"
#include "bulleticon.h"
#include "result.h"
#include "moveui.h"

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CMeshCylinder* CGameManager::m_pMeshCylinder = nullptr;	// �~��
CBoss* CGameManager::m_pBoss = nullptr;					// �{�X
CTime* CGameManager::m_pTime = nullptr;					// �^�C�}�[
CUimanager* CGameManager::m_puimanager = nullptr;		// UI�}�l�[�W���[
CBarrierManager* CGameManager::m_pBarrier = nullptr;	// �o���A�}�l�[�W���[
CRubbleManager* CGameManager::m_pRubble = nullptr;		// ���I�I�u�W�F�N�g�}�l�[�W���[

//========================
// �R���X�g���N�^
//========================
CGameManager::CGameManager()
{
	// �l�̃N���A
}
//========================
// �f�X�g���N�^
//========================
CGameManager::~CGameManager()
{
	// ����
}
//========================
// ����������
//========================
HRESULT CGameManager::Init(void)
{
	// �V�����_�[����
	m_pMeshCylinder = CMeshCylinder::Create(D3DXVECTOR3(0.0f, -20.0f, 0.0f), 550.0f);

	// �{�X����
	m_pBoss = CBoss::Create(D3DXVECTOR3(0.0f, -800.0f, 0.0f), 60.0f, 500);

	// �V�[���I�u�W�F�N�g�ǂݍ���
	CSceneLoader::SplitLoad(2);

	// �^�C�}�[����
	m_pTime = CTime::Create(D3DXVECTOR3(1220.0f, 670.0f, 0.0f), 80.0f, 50.0f);

	// �t���[���쐬
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 65.0f, 0.0f), 0, 65.0f, 65.0f, "data\\TEXTURE\\alert_frame.png", false);
	CUi::Create(D3DXVECTOR3(180.0f, 670.0f, 0.0f), 0, 170.0f, 40.0f, "data\\TEXTURE\\Pause_ui.png", false);

	// ���݂̒e�\���A�C�R��
	CBulletIcon::Create(D3DXVECTOR3(90.0f, 180.0f, 0.0f), "data\\TEXTURE\\Normal_bullet.png", 0);
	CBulletIcon::Create(D3DXVECTOR3(180.0f, 180.0f, 0.0f), "data\\TEXTURE\\Laser_Icon.png", 1);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	// pSound->PlaySound(CSound::SOUND_LABEL_GAMEBGM);

	// �o���A�}�l�[�W���[����
	 m_pBarrier = new CBarrierManager;

	// null����Ȃ������珉����
	if (m_pBarrier != nullptr)
	{
		// ����������
		m_pBarrier->Init();
	}

	// ���I�I�u�W�F�N�g�}�l�[�W���[����
	m_pRubble = new CRubbleManager;

	// null����Ȃ������珉����
	if (m_pRubble != nullptr)
	{
		// ����������
		m_pRubble->Init();
	}

	// �A�C�e���}�l�[�W���[����
	m_pItemManager = new CItemManager;

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// ����������
		m_pItemManager->Init();
	}

	// �~���U���Ǘ��N���X����
	m_pPilerManager = new CPilerManager;

	// null����Ȃ�������
	if (m_pPilerManager != nullptr)
	{
		// ����������
		m_pPilerManager->Init();
	}

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return E_FAIL;

	// �A�j���[�V�����Z�b�g
	pCamera->SetLoadPass(0);
	pCamera->SetCameraMode(CCamera::MODE_ANIM);

	// �A�j���[�V��������UI�Z�b�g
	CMoveUi::Create(D3DXVECTOR3(SCREEN_WIDTH, 30.0f, 0.0f), "data\\TEXTURE\\CameraAnimBox.png", CMoveUi::MOVETYPE_RIGHT);
	CMoveUi::Create(D3DXVECTOR3(0.0f, 690.0f, 0.0f), "data\\TEXTURE\\CameraAnimBox.png", CMoveUi::MOVETYPE_LEFT);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//========================
// �I������
//========================
void CGameManager::Uninit(void)
{
	// �g�p�����|�C���^��null������
	m_pBoss = nullptr;
	m_pMeshCylinder = nullptr;
	m_pTime = nullptr;

	// null����Ȃ�������
	if (m_pBarrier != nullptr)
	{
		// �I������
		m_pBarrier->Uninit();

		// �|�C���^�̔j��
		delete m_pBarrier;

		// null������
		m_pBarrier = nullptr;
	}

	// null����Ȃ�������
	if (m_pRubble != nullptr)
	{
		// �I������
		m_pRubble->Uninit();

		// �|�C���^�̔j��
		delete m_pRubble;

		// null������
		m_pRubble = nullptr;
	}

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// �I������
		m_pItemManager->Uninit();

		// �|�C���^�̔j��
		delete m_pItemManager;

		// null������
		m_pItemManager = nullptr;
	}

	// null����Ȃ�������
	if (m_pPilerManager != nullptr)
	{
		// �I������
		m_pPilerManager->Uninit();

		// �|�C���^�̔j��
		delete m_pPilerManager;

		// null������
		m_pPilerManager = nullptr;
	}
}
//========================
// �X�V����
//========================
void CGameManager::Update(void)
{
	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;

	// �ߋ��̍��W�擾
	D3DXVECTOR3 pos = pPlayer->GetOldPos();

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g�� �܂��� �A�j���[�V�������Ȃ�~�߂�
	if (pCamera->GetMode() == CCamera::MODE_ANIM) return;
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// null����Ȃ�������
	if (m_pBarrier != nullptr)
	{
		// �X�V����
		m_pBarrier->Update();
	}

	// null����Ȃ�������
	if (m_pItemManager != nullptr)
	{
		// �X�V����
		m_pItemManager->Update();
	}

	// null����Ȃ�������
	if (m_pPilerManager != nullptr)
	{
		// �X�V����
		// m_pPilerManager->Update(&pos);
	}

#ifdef _DEBUG

	// ���ؗp�I�u�W�F�N�g�o��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_O))
	{
		// ���Z�񐔂����Z
		CScore::DecScore();
	}

	// ���ؗp�I�u�W�F�N�g�o��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_2))
	{
		// �X�V
		CManager::GetFade()->SetFade(new CResult());
		return;
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_L))
	{
		// CManager::GetFade()->SetFade(new CResult());

		// return;

		// �t�@�C������
		m_pRubble->LoadSplitFile(m_pRubble->FILETYPE_SMALL);
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_N))
	{
		// �X�R�A��ۑ�
		CScore::SaveScore();
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_G))
	{
		CCamera* pCamera = CManager::GetCamera();

		pCamera->SetCameraMode(CCamera::MODE_ANIM);
	}
#endif
}