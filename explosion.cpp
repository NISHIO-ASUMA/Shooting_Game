//====================================
//
// �������� [ explosion.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "explosion.h"
#include "manager.h"

//***********************************
// �}�N����`
//***********************************
#define NUM_PATTERN (8)
#define NUM_ANIM (2)
#define TEX_U (0.125f)
#define TEX_V (1.0f)
#define EXPLOSION_SIZE_X (100.0f)
#define EXPLOSION_SIZE_Y (100.0f)

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CExplosion::CExplosion(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTexture = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CExplosion::~CExplosion()
{
	// ����
}
//===============================
// ��������
//===============================
CExplosion* CExplosion::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col)
{
	// �����̃C���X�^���X����
	CExplosion* pExplsion = new CExplosion;

	// �e�N�X�`���Z�b�g
	pExplsion->SetTexture();

	// �������Ɏ��s������
	if (FAILED(pExplsion->Init())) 
	{
		// �j��
		delete pExplsion;

		// NULL��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pExplsion->SetRot(rot);
	pExplsion->SetSize(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y);
	pExplsion->SetPos(pos);
	pExplsion->SetCol(col);

	return pExplsion;
}
//===============================
// �����̏���������
//===============================
HRESULT CExplosion::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	return S_OK;
}
//===============================
// �����̏I������
//===============================
void CExplosion::Uninit(void)
{
	// �I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}
//===============================
// �����̍X�V����
//===============================
void CExplosion::Update(void)
{
	// ���݂̍��W���擾
	D3DXVECTOR3 pos = GetPos();

	// ���W�Z�b�g
	SetPos(pos);

	// �A�j���[�V�����Z�b�g
	// SetAnim(NUM_PATTERN,NUM_ANIM, TEX_U, TEX_V);
}
//===============================
// �����̕`�揈��
//===============================
void CExplosion::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �I�u�W�F�N�g�`��
	CObject2D::Draw();
}
//===============================
// �e�N�X�`���Z�b�g
//===============================
void CExplosion::SetTexture()
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\explosion000.png");

}