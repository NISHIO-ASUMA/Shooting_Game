//===============================================
//
// UI�G�f�B�^�[�V�[���Ǘ����� [ uieditmanager.h ]
// Author : Asuma Nishio
//
//===============================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "uieditmanager.h"

//===============================
// �R���X�g���N�^
//===============================
CUiEditManager::CUiEditManager()
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nTypeIdx = NULL;
	m_mtxworld = {};

	m_nSavePassIdx = NULL;
	m_nNumAll = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CUiEditManager::~CUiEditManager()
{

}
//===============================
// ������
//===============================
HRESULT CUiEditManager::Init(void)
{
	return S_OK;
}
//===============================
// �I��
//===============================
void CUiEditManager::Uninit(void)
{

}
//===============================
// �X�V
//===============================
void CUiEditManager::Update(void)
{

}
//===============================
// �`��
//===============================
void CUiEditManager::Draw(void)
{

}
//===============================
// �ۑ�
//===============================
void CUiEditManager::Save(void)
{

}
