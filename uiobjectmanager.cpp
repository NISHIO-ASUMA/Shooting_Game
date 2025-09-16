//=========================================================
//
// UI�G�f�B�^�[�I�u�W�F�N�g�Ǘ����� [ uiobjectmanager.cpp ]
// Author : Asuma Nishio
// 
// TODO : �Ƃō�Ƃ���
//
//=========================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "uiobjectmanager.h"
#include "uiobject.h"

//=====================================
// �R���X�g���N�^
//=====================================
CUiObjectManager::CUiObjectManager(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_UiObj.clear();
}
//=====================================
// �f�X�g���N�^
//=====================================
CUiObjectManager::~CUiObjectManager()
{
	// ����
}
//=====================================
// ����������
//=====================================
HRESULT CUiObjectManager::Init(void)
{
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CUiObjectManager::Uninit(void)
{
	// �l�̃N���A
	m_UiObj.clear();

	// ���g�̔j��
	CObject::Release();
}
//=====================================
// �X�V����
//=====================================
void CUiObjectManager::Update(void)
{

}
//=====================================
// �`�揈��
//=====================================
void CUiObjectManager::Draw(void)
{

}
//=====================================
// ��������
//=====================================
CUiObjectManager* CUiObjectManager::Craete(void)
{
	// �C���X�^���X����
	CUiObjectManager* pUiObj = new CUiObjectManager;

	// nnull�`�F�b�N
	if (pUiObj == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pUiObj->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pUiObj;
}
