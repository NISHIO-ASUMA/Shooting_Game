//========================================
//
// �e�A�C�R������ [ bulleticon.cpp ]
// Author: Asuma Nishio
//
//========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "bulleticon.h"
#include "manager.h"
#include "texture.h"
#include "bullet.h"

//***************************
// ���O���
//***************************
namespace BULLETICONINFO
{
	constexpr float ICONSIZE = 30.0f;	// �A�C�R���̃T�C�Y
};

//==================================
// �I�[�o�[���[�h�R���X�g���N�^
//==================================
CBulletIcon::CBulletIcon(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_nIdx = NULL;
}
//==================================
// �f�X�g���N�^
//==================================
CBulletIcon::~CBulletIcon()
{
	// ����
}
//==================================
// ��������
//==================================
CBulletIcon* CBulletIcon::Create(D3DXVECTOR3 pos, const char* pTexName,int nIdx)
{
	// �C���X�^���X����
	CBulletIcon* pIcon = new CBulletIcon;
	if (pIcon == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pIcon->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pIcon->SetPos(pos);
	pIcon->SetSize(BULLETICONINFO::ICONSIZE, BULLETICONINFO::ICONSIZE);
	pIcon->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pIcon->SetTexture(pTexName);
	pIcon->m_nIdx = nIdx;

	// �������ꂽ�|�C���^��Ԃ�
	return pIcon;
}
//==================================
// ����������
//==================================
HRESULT CBulletIcon::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	return S_OK;
}
//==================================
// �I������
//==================================
void CBulletIcon::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//==================================
// �X�V����
//==================================
void CBulletIcon::Update(void)
{
	// �e�̎�ނ��擾
	int nType = static_cast<int>(CBullet::GetType());

	// ��v���Ă�����
	if (m_nIdx == nType)
	{
		// �J���[�ύX
		SetCol(COLOR_WHITE);
	}
	else
	{
		// �J���[�ύX
		SetCol(COLOR_GLAY);
	}

	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//==================================
// �`�揈��
//==================================
void CBulletIcon::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �I�u�W�F�N�g�`��
	CObject2D::Draw();
}
//==================================
// �e�N�X�`������
//==================================
void CBulletIcon::SetTexture(const char* pTexName)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �p�X��ݒ�
	m_nIdxTex = pTexture->Register(pTexName);
}
