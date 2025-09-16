//=====================================
//
// �`���[�g���A������ [ tutorial.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "tutorial.h"
#include "tutorialmanager.h"
#include "manager.h"
#include "sound.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CTutorial::CTutorial() : CScene(CScene::MODE_TUTORIAL)
{
	// �l�̃N���A
	m_pTutoManager = nullptr;
}
//===============================
// �f�X�g���N�^
//===============================
CTutorial::~CTutorial()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CTutorial::Init(void)
{
	// �}�l�[�W���[�̃C���X�^���X����
	m_pTutoManager = new CTutorialManager;

	// null�ł͂Ȃ�������
	if (m_pTutoManager != nullptr) m_pTutoManager->Init();

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_TUTORIALBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CTutorial::Uninit(void)
{
	// null�`�F�b�N
	if (m_pTutoManager != nullptr)
	{
		// �I������
		m_pTutoManager->Uninit();

		// �|�C���^�̔j��
		delete m_pTutoManager;

		// nullptr�ɂ���
		m_pTutoManager = nullptr;
	}
}
//===============================
// �X�V����
//===============================
void CTutorial::Update(void)
{
	// �|�C���^�����݂���Ȃ�
	if (m_pTutoManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pTutoManager->Update();
	}
}
//===============================
// �`�揈��
//===============================
void CTutorial::Draw(void)
{
	// ����
}
//===============================
// ��������
//===============================
CTutorial* CTutorial::Create(void)
{
	// �C���X�^���X����
	CTutorial* pTutorial = new CTutorial;

	// �������s��
	if (pTutorial == nullptr) return nullptr;

	// �����������Ɏ��s������
	if (FAILED(pTutorial->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTutorial;
}
