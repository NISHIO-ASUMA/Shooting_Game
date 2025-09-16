//============================================
//
// �Q�[�W�֌W�̃N���X���� [ gage.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "gage.h"
#include "texture.h"
#include "manager.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CGage::CGage(int nPriority) : CObject2D(nPriority)
{
	// ����
}
//===============================
// �f�X�g���N�^
//===============================
CGage::~CGage()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CGage::Init(void)
{
	// �e�N���X�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CGage::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CGage::Update(void)
{
	// �e�N���X�̍X�V
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CGage::Draw(void)
{
	// �e�N���X�̕`��
	CObject2D::Draw();
}
//===============================
// �`�揈��
//===============================
CGage* CGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CGage* pGage = new CGage;

	// �����ł��Ȃ�������
	if (pGage == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pGage->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pGage->SetPos(pos);
	pGage->SetSize(fWidth, fHeight);

	// �|�C���^��Ԃ�
	return pGage;
}
//===============================
// �Q�[�W�̒����ݒ菈��
//===============================
void CGage::SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue,float Height)
{
	// �ő�䗦���o��
	float fRatio = 1.0f;

	// 0�ȏ�Ȃ�
	if (nMaxLife > NULL)
	{
		// �������v�Z����
		fRatio = static_cast<float>(nCurrentLife) / static_cast<float>(nMaxLife);
	}

	// �\������̗̓o�[�̍ő啝
	const float fMaxWidth = SCREEN_WIDTH * fValue;

	// �T�C�Y��䗦�Ŕ��f
	SetSize(fMaxWidth * fRatio, Height);
}
//===============================
// �Q�[�W�̒����ݒ菈�� ( float )
//===============================
void CGage::FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight)
{
	// �����l
	float fRatio = 1.0f;

	// 0�ȏ�
	if (fMax > 0.0f)
	{
		// �����v�Z
		fRatio = fCurrent / fMax;
	}

	// �ő啝�Ɗ������������T�C�Y��ݒ�
	SetSize(fMaxWidth * fRatio, fHeight);
}
