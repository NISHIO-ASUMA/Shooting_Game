//=======================================
//
// �����L���O�V�[������ [ ranking.cpp ]
// Author: Asuma Nishio
//
//=======================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "ranking.h"
#include "manager.h"
#include "rankingmanager.h"
#include "input.h"
#include "fade.h"
#include "title.h"

//===================================
// �I�[�o�[���[�h�R���X�g���N�^
//===================================
CRanking::CRanking() : CScene(CScene::MODE_RANKING)
{
	// �l�̃N���A
	m_pRankManager = nullptr;
}
//===================================
// �f�X�g���N�^
//===================================
CRanking::~CRanking()
{
	// ����
}
//===================================
// ��������
//===================================
CRanking* CRanking::Create(void)
{
	// �C���X�^���X����
	CRanking* pRanking = new CRanking;
	if (pRanking == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pRanking->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRanking;
}
//===================================
// ����������
//===================================
HRESULT CRanking::Init(void)
{
	// �C���X�^���X����
	m_pRankManager = new CRankingManager;

	// null����Ȃ�������
	if (m_pRankManager != nullptr)
	{
		// ����������
		m_pRankManager->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===================================
// �I������
//===================================
void CRanking::Uninit(void)
{
	// null�`�F�b�N
	if (m_pRankManager != nullptr)
	{
		// �I������
		m_pRankManager->Uninit();

		// �|�C���^�̔j��
		delete m_pRankManager;

		// null������
		m_pRankManager = nullptr;
	}
}
//===================================
// �X�V����
//===================================
void CRanking::Update(void)
{
	// null�`�F�b�N
	if (m_pRankManager != nullptr) m_pRankManager->Update();

	// ����L�[����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_A) || CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		// �t�F�[�h�擾
		CFade* pFade = CManager::GetFade();
		if (pFade == nullptr) return;

		// ��ʑJ��
		pFade->SetFade(new CTitle(true));

		// �J�����̐ݒ������������
		CManager::GetCamera()->SetFinishRotation(false);
		CManager::GetCamera()->SetIsRotation(false);
		CManager::GetCamera()->SetKey(false);

		return;
	}
}
//===================================
// �`�揈��
//===================================
void CRanking::Draw(void)
{
	// ����
}