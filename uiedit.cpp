//=====================================
//
// �G�f�B�^�[���� [ uiedit.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "uiedit.h"
#include "ui.h"
#include "uieditmanager.h"

//===============================
// �R���X�g���N�^
//===============================
CUiedit::CUiedit() : CScene(CScene::MODE_EDIT)
{
	// �l�̃N���A
	m_pUiEditManager = nullptr;
}
//===============================
// �f�X�g���N�^
//===============================
CUiedit::~CUiedit()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUiedit::Init(void)
{
	// �������m��
	m_pUiEditManager = new CUiEditManager;

	// null�Ȃ�
	if (m_pUiEditManager == nullptr) return E_FAIL;

	// ����������
	m_pUiEditManager->Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CUiedit::Uninit(void)
{
	// null�`�F�b�N
	if (m_pUiEditManager != nullptr)
	{
		// �I������
		m_pUiEditManager->Uninit();

		// �|�C���^�̔j��
		delete m_pUiEditManager;

		// null������
		m_pUiEditManager = nullptr;
	}
}
//===============================
// �X�V����
//===============================
void CUiedit::Update(void)
{
	// null����Ȃ�������
	if (m_pUiEditManager != nullptr)
	{
		m_pUiEditManager->Update();
	}
}
//===============================
// �`�揈��
//===============================
void CUiedit::Draw(void)
{
	// null����Ȃ�������
	if (m_pUiEditManager != nullptr)
	{
		m_pUiEditManager->Draw();
	}
}
//===============================
// ��������
//===============================
CUiedit* CUiedit::Create(void)
{
	// �C���X�^���X����
	CUiedit* pUiEdit = new CUiedit;

	// null�`�F�b�N
	if (pUiEdit == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pUiEdit->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pUiEdit;
}
