//=====================================
//
// �g�U�I�u�W�F�N�g���� [ spread.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "spread.h"

//**********************
// ���O���
//**********************
namespace SPREADINFO
{
	constexpr float GRAVITY = 0.5f;	// �d�͒l
	constexpr float FIRSTBOUNCE = 12.0f; // ���ڂ̃o�E���h
	constexpr float SECONDBOUNCE = 3.0f; // ���ڂ̃o�E���h
};

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CSpread::CSpread(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_fUpSpeed = NULL;
	m_nBounceCount = NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CSpread::~CSpread()
{
	// ����
}
//=================================
// ��������
//=================================
CSpread* CSpread::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	CSpread* pSpread = new CSpread;
	if (pSpread == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pSpread->SetFilePass("data\\MODEL\\STAGEOBJ\\Spread.x");
	pSpread->SetPos(pos);
	pSpread->SetRot(rot);

	// ���������s��
	if (FAILED(pSpread->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pSpread;
}
//=================================
// ����������
//=================================
HRESULT CSpread::Init(void)
{
	// �e�N���X�̏���������
	CObjectX::Init();

	return S_OK;
}
//=================================
// �I������
//=================================
void CSpread::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//=================================
// �X�V����
//=================================
void CSpread::Update(void)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 pos = GetPos();

	// �d�͂�������
	m_fUpSpeed -= SPREADINFO::GRAVITY;
	pos.y += m_fUpSpeed;

	// �n�ʂɓ��B
	if (pos.y <= 0.0f)
	{
		// ���W��ݒ�
		pos.y = 0.0f;

		// �J�E���g�����Z
		m_nBounceCount++;

		switch (m_nBounceCount)
		{
		case 1:
			// 1��ڂ̃o�E���h
			m_fUpSpeed = SPREADINFO::FIRSTBOUNCE;	// ���߂ɐݒ�
			break;

		case 2:
			// 2��ڂ̃o�E���h
			m_fUpSpeed = SPREADINFO::SECONDBOUNCE;	// �����߂ɐݒ�
			break;

		case 3:
			// 3��ڏI��
			Uninit();

			return;

		default:
			break;
		}
	}

	// ���W�ɃZ�b�g
	SetPos(pos);

	// �e�N���X�̍X�V����
	CObjectX::Update();
}
//=================================
// �`�揈��
//=================================
void CSpread::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}