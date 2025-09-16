//=========================================
//
// �^�C�g�����S���� [ titlelogo.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "titlelogo.h"
#include "manager.h"
#include "texture.h"
#include "easing.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CTitleLogo::CTitleLogo(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nTexIdx = NULL;
	m_move = VECTOR3_NULL;
	m_isAnimating = false;
	m_nFrame = NULL;
	m_nMaxFrame = NULL;
}
//================================
// �f�X�g���N�^
//================================
CTitleLogo::~CTitleLogo()
{
	// ����
}
//================================
// ��������
//================================
CTitleLogo* CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CTitleLogo* pTitlelogo = new CTitleLogo;

	// null�������ꍇ
	if (pTitlelogo == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pTitlelogo->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pTitlelogo->SetPos(pos);
	pTitlelogo->SetSize(fWidth, fHeight);
	pTitlelogo->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pTitlelogo->SetTexture();

	// �������ꂽ�|�C���^��Ԃ�
	return pTitlelogo;
}
//================================
// ����������
//================================
HRESULT CTitleLogo::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	// �����l��ݒ�
	m_nMaxFrame = 800;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CTitleLogo::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CTitleLogo::Update(void)
{
	// ���̓`�F�b�N
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// null�Ȃ�
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �L�[���͂��ꂽ
	if (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(CJoyPad::JOYKEY_START))
	{
		m_isAnimating = true;
		m_nFrame = 0;
	}

	if (m_isAnimating)
	{
		if (m_nFrame < m_nMaxFrame) m_nFrame++;

		CEasing ease;
		float t = ease.SetEase(m_nFrame, m_nMaxFrame);

		// EaseOutCubic��K�p
		float e = ease.EaseOutCubic(t);

		// �J�n�ʒu�E�T�C�Y
		D3DXVECTOR3 startPos = GetPos();
		float startW = GetWidth(), startH = GetHeight();

		// �ړI�n�E�T�C�Y
		D3DXVECTOR3 destPos = { 200.0f, 80.0f, 0.0f };
		float destW = 180.0f, destH = 65.0f;

		// ���
		D3DXVECTOR3 pos = startPos + (destPos - startPos) * e;
		float width = startW + (destW - startW) * e;
		float height = startH + (destH - startH) * e;

		// ���S���B������Î~
		if (m_nFrame >= m_nMaxFrame)
		{
			pos = destPos;
			width = destW;
			height = destH;
			m_isAnimating = false;  // �A�j���[�V�����I��
		}

		// �l�𔽉f
		SetPos(pos);
		SetSize(width, height);
	}

	// �e�N���X�X�V
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CTitleLogo::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}
//================================
// �e�N�X�`�����蓖�ď���
//================================
void CTitleLogo::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\logo.png");
}
