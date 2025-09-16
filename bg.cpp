//====================================
//
// �w�i���� [ bg.h ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bg.h"
#include "manager.h"
#include "object.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CBg::CBg(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_ScrollSpeed = 0.0f;
	m_IndexBg = 0;
	m_nIdxTexture = 0;
}
//===============================
// �f�X�g���N�^
//===============================
CBg::~CBg()
{
	// ����
}
//===============================
// ��������
//===============================
CBg* CBg::Create(int nIdxBg)
{
	// �w�i�̃|�C���^�錾
	CBg* pBg;

	// �C���X�^���X����
	pBg = new CBg;

	// �ԍ�����
	pBg->m_IndexBg = nIdxBg;

	// �e�N�X�`���Z�b�g
	pBg->SetTexture(nIdxBg);

	// �X�N���[�����x�����C���[���Ƃɐݒ�
	switch (nIdxBg)
	{
	case BG_BACK: 
		pBg->SetScrollSpeed(0.003f); 
		break; // ��

	case BG_CENTER: 
		pBg->SetScrollSpeed(0.006f);
		break; // �^��

	case BG_FRONT:
		pBg->SetScrollSpeed(0.009f); 
		break; // ��O

	default:
		break;
	}

	// ����������
	if (FAILED(pBg->Init()))
	{
		// �j��
		delete pBg;

		// NULL�ɂ���
		return nullptr;
	}

	// 2D�`��ݒ�
	pBg->SetRot(D3DXVECTOR3(VECTOR3_NULL));
	pBg->SetSize((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT);
	pBg->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f));

	// �w�i�̃|�C���^��Ԃ�
	return pBg;
}
//===============================
// �w�i�̏���������
//===============================
HRESULT CBg::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �w�i�̏I������
//===============================
void CBg::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̔j��
	CObject2D::Uninit();
}
//===============================
// �w�i�̍X�V����
//===============================
void CBg::Update(void)
{
	// �e�N�X�`���̃X�N���[������
	m_TexScroll.x += m_ScrollSpeed;

	// �e�N�X�`�����W�̍X�V�֐�
	// SetUV(m_TexScroll.x, 1.0f + m_TexScroll.x, 1.0f);
}
//===============================
// �w�i�̕`�揈��
//===============================
void CBg::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// 2D�I�u�W�F�N�g�̕`��
	CObject2D::Draw();
}
//===============================
// �e�N�X�`���Z�b�g�֐�
//===============================
void CBg::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	switch (nType)
	{
	case BG_BACK:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;
	case BG_CENTER:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;

	case BG_FRONT:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field000.jpeg");
		break;

	default:
		break;
	}
}
