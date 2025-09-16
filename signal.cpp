//=====================================
//
// �U���T�C������ [ signal.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "signal.h"
#include "manager.h"
#include "texture.h"

//**********************
// ���O���
//**********************
namespace SIGNINFO
{
	inline constexpr int LIFE = 60; // �ő����
	inline constexpr float UISIZE = 50.0f;	// UI�T�C�Y
	const D3DXVECTOR3 ACTIVEPOS = { 640.0f,60.0f,0.0f }; // UI���W
};

//==============================
// �R���X�g���N�^
//==============================
CSignal::CSignal(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nidxTex = NULL;
	m_nLife = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CSignal::~CSignal()
{
	// ����
}
//==============================
// ����������
//==============================
HRESULT CSignal::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ������ݒ�
	m_nLife = SIGNINFO::LIFE;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CSignal::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CSignal::Update(void)
{
	// �_�ŏ��������s
	SetFlash(2, 5, COLOR_WHITE);

	// �̗͂����炷
	m_nLife--;

	// 0�ȉ�
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		// �����ŏ����I��
		return;
	}

	// �I�u�W�F�N�g�X�V
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CSignal::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nidxTex));

	// �I�u�W�F�N�g�`��
	CObject2D::Draw();
}
//==============================
// �e�N�X�`�����蓖��
//==============================
void CSignal::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �p�X��ݒ�
	m_nidxTex = pTexture->Register("data\\TEXTURE\\alert.png");
}
//==============================
// ��������
//==============================
CSignal* CSignal::Create(void)
{
	// �C���X�^���X����
	CSignal* pSign = new CSignal;
	if (pSign == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pSign->SetPos(SIGNINFO::ACTIVEPOS);
	pSign->SetSize(SIGNINFO::UISIZE, SIGNINFO::UISIZE);
	pSign->SetAnchor(ANCHORTYPE_CENTER);
	pSign->SetTexture();

	// ���������s��
	if (FAILED(pSign->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pSign;
}
