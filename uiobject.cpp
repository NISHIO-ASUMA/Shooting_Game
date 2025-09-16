//=====================================================================================
//
// UI�G�f�B�^�[�I�u�W�F�N�g [ uiobject.cpp ]
// Author : Asuma Nishio
// 
// TODO : �Ƃō�Ƃ���		�����Ƀe�N�X�`���t�@�C����,�A���J�[�^�C�v��ǉ�����
// �����o�����I�u�W�F�N�g��UI�N���X�g����Load����
//======================================================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "uiobject.h"
#include "manager.h"

//==============================
// �R���X�g���N�^
//==============================
CUiObject::CUiObject(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_fHeight = 0.0f;
	m_fWidth = 0.0f;
	m_nIdx = -1;
}
//==============================
// �f�X�g���N�^
//==============================
CUiObject::~CUiObject()
{
	// ����
}
//==============================
// ����������
//==============================
HRESULT CUiObject::Init(void)
{
	CObject2D::Init();

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_fHeight = 40.0f;
	m_fWidth = 40.0f;
	m_nIdx = -1;

	return S_OK;
}
//==============================
// �I������
//==============================
void CUiObject::Uninit(void)
{
	// ���g�̔j��
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CUiObject::Update(void)
{

}
//==============================
// �`�揈��
//==============================
void CUiObject::Draw(void)
{
	if (m_nIdx == -1) return;

	CObject2D::Draw();
}
//==============================
// ��������
//==============================
CUiObject* CUiObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth, float fHeight, int nIdx)
{
	// �C���X�^���X����
	CUiObject* pObj = new CUiObject;

	// null�`�F�b�N
	if (pObj == nullptr) return nullptr;

	if (FAILED(pObj->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pObj->m_pos = pos;
	pObj->m_rot = rot;
	pObj->m_fWidth = fWidth;
	pObj->m_fHeight = fHeight;
	pObj->m_nIdx = nIdx;

	// �������ꂽ�|�C���^
	return pObj;
}
