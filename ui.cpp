//====================================
//
// UI���� [ ui.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "ui.h"
#include "texture.h"
#include "manager.h"
#include "easing.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CUi::CUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTexIdxType = NULL;
	m_isFlash = false;
	m_nFlashFrame = NULL;
	m_nState = STATE_NONE;
}
//===============================
// �f�X�g���N�^
//===============================
CUi::~CUi()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUi::Init(void)
{
	// �I�u�W�F�N�g�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CUi::Uninit(void)
{
	// �I�u�W�F�N�g�̏I��
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CUi::Update(void)
{
	// �_�ŗL����
	if (m_isFlash)
	{
		// �_�ŏ���
		SetFlash(NULL, m_nFlashFrame, COLOR_WHITE);
	}

	if (m_nState == STATE_FALL && !m_isFlash)
	{
		// ���ݍ��W���擾
		D3DXVECTOR3 NowPos = GetPos();
		
		// ���Ɉړ�
		NowPos.y += 10.0f;

		// ���W�Z�b�g
		SetPos(NowPos);

		if (NowPos.y >= SCREEN_HEIGHT + 50.0f)
		{
			// �I������
			Uninit();

			// ���̏����ɓ���Ȃ��悤�ɂ���
			return;
		}
	}

	// �e�N���X�X�V
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���Z�b�g
	CTexture* pTexture = CManager::GetTexture();

	// ���蓖��
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdxType));

	// �I�u�W�F�N�g�̕`��
	CObject2D::Draw();
}
//===============================
// ��������
//===============================
CUi* CUi::Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight, const char* Filename, bool isUse)
{
	// �C���X�^���X����
	CUi* pUi = new CUi;

	// null�Ȃ�
	if (pUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pUi->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pUi->SetPos(pos);
	pUi->SetSize(fWidth, fHeight);
	pUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pUi->SetTexture(Filename);
	pUi->m_nFlashFrame = nFlashFrame;
	pUi->m_isFlash = isUse;

	// �������ꂽ�|�C���^��Ԃ�
	return pUi;
}
//===============================
// �e�N�X�`���Z�b�g����
//===============================
void CUi::SetTexture(const char* pRegistername)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null����Ȃ�������
	if (pTexture != nullptr)
	{
		// �e�N�X�`���ݒ�
		m_nTexIdxType = pTexture->Register(pRegistername);
	}
}