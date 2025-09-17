//====================================
//
// �^�C�g������ [ title.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "title.h"
#include "manager.h"
#include "game.h"
#include "ui.h"
#include "titlemanager.h"

//=====================================
// �R���X�g���N�^
//=====================================
CTitle::CTitle(bool isFirst) : CScene(CScene::MODE_TITLE), m_isCreate(isFirst)
{
	//����
}
//=====================================
// �f�X�g���N�^
//=====================================
CTitle::~CTitle()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CTitle::Init(void)
{
	// �J�����擾�E������
	CCamera* pCamera = CManager::GetCamera();
	pCamera->Init();

	// �C���X�^���X����
	m_pTitleManager = new CTitleManager(m_isCreate);

	// �������s��
	if (m_pTitleManager == nullptr) return E_FAIL;

	// �}�l�[�W���[�̏���������
	m_pTitleManager->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CTitle::Uninit(void)
{
	// null�`�F�b�N
	if (m_pTitleManager != nullptr)
	{
		// �I������
		m_pTitleManager->Uninit();

		// �j��
		delete m_pTitleManager;

		// nullptr����
		m_pTitleManager = nullptr;
	}
}
//=====================================
// �X�V����
//=====================================
void CTitle::Update(void)
{
	// null����Ȃ�������
	if (m_pTitleManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pTitleManager->Update();
	}

	// �R���g���[���[�擾
	if (CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_BACK))
	{
		PostQuitMessage(0);
		return;
	}
}
//=====================================
// �`�揈��
//=====================================
void CTitle::Draw(void)
{
	// ����
}
//=====================================
// ��������
//=====================================
CTitle* CTitle::Create(bool isFirst)
{
	// �C���X�^���X����
	CTitle* pTitle = new CTitle(isFirst);

	// null��������
	if (pTitle == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitle->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTitle;
}