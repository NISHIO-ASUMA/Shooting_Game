//====================================
//
// �e���� [ shadow.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "shadow.h"
#include "manager.h"

//**********************
// ���O���
//**********************
namespace SHADOWINFO
{
	constexpr float SHADOW_SIZE = 30.0f; // �e�̑傫��
}

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CShadow::CShadow(int nPriority) : CObject3D(nPriority)
{
	// �l�̃N���A
	m_nTexIdx = NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CShadow::~CShadow()
{
	// ����
}
//==================================
// ��������
//==================================
CShadow* CShadow::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	CShadow* pShadow = new CShadow;

	// nullptr��������
	if (pShadow == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pShadow->SetPos(pos);
	pShadow->SetRot(rot);
	pShadow->SetSize(SHADOWINFO::SHADOW_SIZE, SHADOWINFO::SHADOW_SIZE);
	pShadow->SetTexture();

	// ���������s��
	if (FAILED(pShadow->Init()))
	{
		// ������Ԃ�
		return nullptr;
	}

	// �e�̃|�C���^��Ԃ�
	return pShadow;
}
//=================================
// �e�̏���������
//=================================
HRESULT CShadow::Init(void)
{
	// �e�N���X�̏�����
	CObject3D::Init();

	return S_OK;
}
//=================================
// �e�̏I������
//=================================
void CShadow::Uninit(void)
{
	// �e�̏I������
	CObject3D::Uninit();
}
//=================================
// �e�̍X�V����
//=================================
void CShadow::Update(void)
{
	// ����
}
//=================================
// �e�̕`�揈��
//=================================
void CShadow::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���Z�����̐ݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// �e�N���X�̕`��
	CObject3D::Draw();

	// ���Z������߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
//=================================
// �e�N�X�`���ݒ菈��
//=================================
void CShadow::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���N���X�ɓo�^
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\shadow000.jpg");
}
//=================================
// �e���W�X�V����
//=================================
void CShadow::UpdatePos(D3DXVECTOR3 pos)
{
	// ���W�Z�b�g
	SetPos(pos);
}
