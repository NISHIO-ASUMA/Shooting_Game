//==========================================
//
// �����L���O�Ǘ����� [ rankingmanager.cpp ]
// Author: Asuma Nishio
//
//==========================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "rankingmanager.h"
#include "rankingscore.h"
#include "ui.h"

//================================
// �R���X�g���N�^
//================================
CRankingManager::CRankingManager()
{
	// �l�̃N���A

}
//================================
// �f�X�g���N�^
//================================
CRankingManager::~CRankingManager()
{
	// ����
}
//================================
// ����������
//================================
HRESULT CRankingManager::Init(void)
{
	// Ui�w�i����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "RankBack.jpg", false);

	// �����L���O�X�R�A����
	CRankingScore::Create(D3DXVECTOR3(1050.0f, 200.0f, 0.0f), 250.0f, 40.0f);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CRankingManager::Uninit(void)
{
	// ����
}
//================================
// �X�V����
//================================
void CRankingManager::Update(void)
{
	// �e��X�V
}