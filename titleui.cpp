//====================================
//
// �^�C�g��ui���� [ titleui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "titleui.h"
#include "texture.h"
#include "manager.h"

//=========================
// �R���X�g���N�^
//=========================
CTitleUi::CTitleUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTexIdx = NULL;
}
//=========================
// �f�X�g���N�^
//=========================
CTitleUi::~CTitleUi()
{
	// ����
}
//=========================
// ����������
//=========================
HRESULT CTitleUi::Init(void)
{
	// 2D�I�u�W�F�N�g�̏���������
	CObject2D::Init();

	// ���_�^�C�v��ݒ�
	SetAnchor(ANCHORTYPE_CENTER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=========================
// �I������
//=========================
void CTitleUi::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}
//=========================
// �X�V����
//=========================
void CTitleUi::Update(void)
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}
//=========================
// �`�揈��
//=========================
void CTitleUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}
//=========================
// ��������
//=========================
CTitleUi* CTitleUi::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	CTitleUi* pTitleui = new CTitleUi;

	// null��������
	if (pTitleui == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitleui->Init())) 
	{
		// null��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pTitleui->SetPos(pos);
	pTitleui->SetCol(col);
	pTitleui->SetSize(fWidth, fHeight);
	pTitleui->SetTexture(nType);

	// �������ꂽ�|�C���^��Ԃ�
	return pTitleui;
}
//=========================
// �e�N�X�`�����蓖�ď���
//=========================
void CTitleUi::SetTexture(int nType)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case MENU_GAME:			// �Q�[�����j���[
		m_nTexIdx = pTexture->Register("data\\TEXTURE\\titlemenu001.png");
		break;

	case MENU_TUTORIAL:		// �`���[�g���A�����j���[
		m_nTexIdx = pTexture->Register("data\\TEXTURE\\titilemenu_002.png");
		break;

	case MENU_EXIT:			// �I���I��
		m_nTexIdx = pTexture->Register("data\\TEXTURE\\titlemenu_003.png");
		break;

	default:
		m_nTexIdx = -1;
		break;
	}

}
