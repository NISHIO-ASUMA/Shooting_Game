//==========================================================
//
// �J�����A�j���[�V�������ɓK�p����UI���� [ moveui.cpp ]
// Author: Asuma Nishio
//
//==========================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "moveui.h"
#include "manager.h"
#include "texture.h"

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CMoveUi::CMoveUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTexture = NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CMoveUi::~CMoveUi()
{
	// ����
}
//=================================
// ������������
//=================================
CMoveUi* CMoveUi::Create(D3DXVECTOR3 pos, const char* pFileName, MOVETYPE type)
{
	// �C���X�^���X����
	CMoveUi* pMoveUi = new CMoveUi;
	if (pMoveUi == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pMoveUi->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pMoveUi->SetPos(pos);
	pMoveUi->SetSize(SCREEN_WIDTH * 0.5f, 30.0f);
	pMoveUi->SetTexture(pFileName);
	pMoveUi->m_nMoveType = type;
	pMoveUi->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pMoveUi->SetDrawType(1);

	// �������ꂽ�|�C���^
	return pMoveUi;
}
//=================================
// ����������
//=================================
HRESULT CMoveUi::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CMoveUi::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//=================================
// �X�V����
//=================================
void CMoveUi::Update(void)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// ��ʒ������W
	float fCenterPos = SCREEN_WIDTH * 0.5f;
	float fSpeed = 12.0f;		// �ړ��X�s�[�h

	switch (m_nMoveType)
	{
	case MOVETYPE_RIGHT: // �E���璆����

		if (NowPos.x > fCenterPos)
		{
			NowPos.x -= fSpeed;

			if (NowPos.x <= fCenterPos)
			{
				NowPos.x = fCenterPos;
				m_nMoveType = MOVETYPE_CENTER; // ���B�����璆���Œ�
			}
			SetPos(NowPos);
		}

		break;

	case MOVETYPE_LEFT:   // �����璆����

		if (NowPos.x < fCenterPos)
		{
			NowPos.x += fSpeed;

			if (NowPos.x >= fCenterPos)
			{
				NowPos.x = fCenterPos;
				m_nMoveType = MOVETYPE_CENTER; // ���B�����璆���Œ�
			}

			SetPos(NowPos);
		}
		break;

	case MOVETYPE_CENTER: // �����Ŏ~�܂�

		NowPos.x = fCenterPos;
		SetPos(NowPos);

		break;
	}

	// �J�����A�j���[�V�������I�������
	if (CManager::GetCamera()->GetAnim())
	{
		// ��������̍��W�Ȃ���,������艺�̍��W�Ȃ牺�ɏ����Ă���
		float fCenterY = SCREEN_HEIGHT * 0.5f;

		if (NowPos.y < fCenterY)
		{
			NowPos.y -= 3.0f;
		}
		else
		{
			NowPos.y += 3.0f;
		}

		// ���W�Z�b�g
		SetPos(NowPos);

		// ��ʊO�ɏo����j��
		if (NowPos.y < -30.0f || NowPos.y > SCREEN_HEIGHT + 30.0f)
		{
			Uninit();

			return;
		}
	}


	// �e�N���X�X�V����
	CObject2D::Update();
}
//=================================
// �`�揈��
//=================================
void CMoveUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���Z�b�g
	CTexture* pTexture = CManager::GetTexture();

	// ���蓖��
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �I�u�W�F�N�g�̕`��
	CObject2D::Draw();
}
//=================================
// �e�N�X�`������
//=================================
void CMoveUi::SetTexture(const char* pRegistername)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null����Ȃ�������
	if (pTexture != nullptr)
	{
		// �e�N�X�`���ݒ�
		m_nIdxTexture = pTexture->Register(pRegistername);
	}
}