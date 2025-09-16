//=====================================
//
// �o���|�C���g���� [ exitpoint.cpp ]
// Author: Asuma Nishio
// 
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "exitpoint.h"
#include "manager.h"
#include "texture.h"

//**********************
// ���O���
//**********************
namespace EXITINFO
{
	constexpr float MOVEVALUE = 0.5f;	// �g���
	constexpr float MAXWIDTH = 40.0f;	// �ő�g���
};

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CExitPoint::CExitPoint(int nPriority) : CObject3D(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CExitPoint::~CExitPoint()
{
	// ����
}
//==============================
// ��������
//==============================
CExitPoint* CExitPoint::Create(D3DXVECTOR3 pos, float fWidth)
{
	// �C���X�^���X����
	CExitPoint* pExit = new CExitPoint;
	if (pExit == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pExit->SetPos(pos);
	pExit->SetSize(fWidth, fWidth);
	pExit->SetTexture();

	// ���������s��
	if (FAILED(pExit->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pExit;
}
//==============================
// ����������
//==============================
HRESULT CExitPoint::Init(void)
{
	// �e�N���X�̏���������
	CObject3D::Init();

	// ��ޒ�`
	SetObjType(CObject:: TYPE_POINT);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CExitPoint::Uninit(void)
{
	// �I������
	CObject3D::Uninit();
}
//==============================
// �X�V����
//==============================
void CExitPoint::Update(void)
{
	// ���W���擾
	D3DXVECTOR3 pos = GetPos();

	// ���݂̉����擾
	float fWidth = GetWidth();

	// ���X�ɉ��Z
	fWidth += EXITINFO::MOVEVALUE;

	// �ő�l�𒴂�����
	if (fWidth >= EXITINFO::MAXWIDTH) fWidth = EXITINFO::MAXWIDTH;

	// ���f
	SetSize(fWidth, fWidth);

	// �X�V����
	CObject3D::Update();
}
//==============================
// �`�揈��
//==============================
void CExitPoint::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �e�N���X�̕`�揈��
	CObject3D::Draw();
}
//==============================
// �e�N�X�`�����蓖��
//==============================
void CExitPoint::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\bullet002.png");
}
//==============================
// �����蔻�菈�� ( �~���� )
//==============================
bool CExitPoint::Collision(D3DXVECTOR3 * DestPos)
{
	// ���S���W���擾
	D3DXVECTOR3 pos = GetPos();

	// ���a
	float fRadius = GetWidth() * 0.5f;

	// 2�_�Ԃ̋���
	float dx = DestPos->x - pos.x;
	float dz = DestPos->z - pos.z;
	float distSq = dx * dx + dz * dz;

	// ���a�̓��Ɣ�r
	if (distSq <= fRadius * fRadius)
	{
		return true;	// �͈͓�
	}

	return false;		// �͈͊O
}