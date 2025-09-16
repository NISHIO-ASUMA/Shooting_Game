//===========================================
//
// �}�b�v�}�l�[�W���[���� [ mapmanager.cpp ]
// Author : Asuma Nishio
//
//===========================================

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include "mapmanager.h"
#include "mapobject.h"
#include "modellist.h"
#include "manager.h"

//=========================
// �R���X�g���N�^
//=========================
CMapManager::CMapManager(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_MapObj.clear();
}
//=========================
// �f�X�g���N�^
//=========================
CMapManager::~CMapManager()
{
	// ����
}
//=========================
// ������
//=========================
HRESULT CMapManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//=========================
// �I��
//=========================
void CMapManager::Uninit(void)
{
	// �l�̃N���A
	m_MapObj.clear();

	// ���g�̔j��
	CObject::Release();
}
//=========================
// �X�V
//=========================
void CMapManager::Update(void)
{

}
//=========================
// �`��
//=========================
void CMapManager::Draw(void)
{
}
//=========================
// ��������
//=========================
CMapManager* CMapManager::Craete(void)
{
	// �C���X�^���X����
	CMapManager* pMapManager = new CMapManager;

	// null�Ȃ�
	if (pMapManager == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pMapManager->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pMapManager;
}













#if 0
// ���X�g�擾
CModelList* pModelList = CEditManager::GetList();

// �z�u�������f���̃C���f�b�N�X���擾
int nIdx = m_nSelectIndex;

// �͈̓`�F�b�N
auto modelInfoVec = pModelList->GetInfo();

// ���f�������擾
CModelList::MODELINFO& info = modelInfoVec[nIdx];

// �ړ�����
if (CManager::GetInputKeyboard()->GetPress(DIK_A))
{// A�L�[��������

	m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
}
else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
{// D�L�[��������
	// D�L�[�̂݉�����
	m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
{// W�L�[��������

	m_pos.x += sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z += cosf(pCamera->GetRot().y) * 7.0f;

	// �p�x�𐳋K��
	if (m_rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_rot.y += D3DX_PI * 2.0f;
	}

}
else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
{// S�L�[��������

	m_pos.x -= sinf(pCamera->GetRot().y) * 7.0f;
	m_pos.z -= cosf(pCamera->GetRot().y) * 7.0f;

	// �p�x�̐��K��
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
	}
#endif
