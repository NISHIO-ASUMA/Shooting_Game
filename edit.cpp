//========================================
//
// �G�f�B�^�[�V�[������ [ edit.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "edit.h"
#include "editmanager.h"
#include "meshdome.h"
#include "meshfield.h"
#include "block.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CEdit::CEdit() : CScene(CScene::MODE_EDIT)
{
	// �l�̃N���A
	m_pEditManager = nullptr;
}
//================================
// �f�X�g���N�^
//================================
CEdit::~CEdit()
{
	// ����
}
//================================
// ��������
//================================
CEdit* CEdit::Create(void)
{
	// �C���X�^���X����
	CEdit* pEdit = new CEdit;

	// null�Ȃ�
	if (pEdit == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pEdit->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pEdit;
}
//================================
// ����������
//================================
HRESULT CEdit::Init(void)
{
	// �h�[������
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 800.0f);

	// �t�B�[���h����
	CMeshField::Create(D3DXVECTOR3(0.0f, -150.0f, 0.0f), 2000.0f);

	// �u���b�N�z�u
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f,0);

	// �}�l�[�W���[�̃C���X�^���X����
	m_pEditManager = new CEditManager;

	 // null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// ����������
		m_pEditManager->Init();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CEdit::Uninit(void)
{
	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// �}�l�[�W���[�̏I������
		m_pEditManager->Uninit();

		// �|�C���^�̔j��
		delete m_pEditManager;

		// null������
		m_pEditManager = nullptr;
	}
}
//================================
// �X�V����
//================================
void CEdit::Update(void)
{
	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// �}�l�[�W���[�̍X�V����
		m_pEditManager->Update();
	}
}
//================================
// �`�揈��
//================================
void CEdit::Draw(void)
{
	// null����Ȃ�������
	if (m_pEditManager != nullptr)
	{
		// �}�l�[�W���[�̕`��
		m_pEditManager->Draw();
	}
}