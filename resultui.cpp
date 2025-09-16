//=====================================
//
// ���U���gui�������� [ resultui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "resultui.h"
#include "texture.h"
#include "manager.h"

//============================
// �R���X�g���N�^
//============================
CResultUi::CResultUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
}
//============================
// �f�X�g���N�^
//============================
CResultUi::~CResultUi()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CResultUi::Init(void)
{
	// 2D�I�u�W�F�N�g�̏���������
	CObject2D::Init();

	// ���_�^�C�v��ݒ�
	SetAnchor(ANCHORTYPE_CENTER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CResultUi::Uninit(void)
{
	// 2D�I�u�W�F�N�g�̏I������
	CObject2D::Uninit();
}
//============================
// �X�V����
//============================
void CResultUi::Update(void)
{
	// 2D�I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}
//============================
// �`�揈��
//============================
void CResultUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// 2D�I�u�W�F�N�g�̕`�揈��
	CObject2D::Draw();
}
//============================
// ��������
//============================
CResultUi* CResultUi::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	 CResultUi* pResultUi = new CResultUi;

	 // null�`�F�b�N
	 if (pResultUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pResultUi->Init()))
	{
		// null��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pResultUi->SetPos(pos);
	pResultUi->SetCol(col);
	pResultUi->SetSize(fWidth, fHeight);
	pResultUi->SetTexture(nType);

	// �������ꂽ�|�C���^��Ԃ�
	return pResultUi;
}
//============================
// �e�N�X�`�����蓖��
//============================
void CResultUi::SetTexture(int nType)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case CResultUi::TYPE_NONE:
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\resultlogo.png");
		break;

	default:
		m_nIdxTex = -1;
		break;
	}
}
