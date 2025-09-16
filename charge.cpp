//========================================
//
// �`���[�W���� [ charge.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "charge.h"
#include "manager.h"
#include "texture.h"

//**********************************
// ���O���
//**********************************
namespace CHARGEINFO
{
	constexpr float MAX_CHARGE = 100.0f;	// �ő�`���[�W��
	constexpr float MIN_CHARGE = 0.0f;		// �����`���[�W��
	constexpr float CHAGE_LENGTH = 305.0f;	// �o�[�̒���
	constexpr float BAR_MAXHEIGHT = 38.0f;  // �|���S���̍���
};

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
float CCharge::m_fCharge = CHARGEINFO::MIN_CHARGE;	// �`���[�W�J�E���g
bool CCharge::m_isCharge = false;					// �`���[�W�����t���O

//================================
// �R���X�g���N�^
//================================
CCharge::CCharge(int nPriority) : CGage(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_nType = NULL;
}
//================================
// �f�X�g���N�^
//================================
CCharge::~CCharge()
{
	// ����
}
//================================
// ��������
//================================
CCharge* CCharge::Create(D3DXVECTOR3 pos,float fWidth, float fHeight, int nType)
{
	// �C���X�^���X����
	CCharge* pCharge = new CCharge;

	// null�Ȃ�
	if (pCharge == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pCharge->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pCharge->SetPos(pos);
	pCharge->SetSize(fWidth, fHeight);
	pCharge->SetType(nType);
	pCharge->SetTexture(nType);
	pCharge->SetAnchor(ANCHORTYPE_LEFTSIDE);

	// �������ꂽ�|�C���^��Ԃ�
	return pCharge;
}
//================================
// ���Z����
//================================
void CCharge::AddCharge(float fValue)
{
	// �ő�l��蒴�ߎ�
	if (m_fCharge >= CHARGEINFO::MAX_CHARGE)
	{
		// �ő�l�̒����ɐݒ�
		m_fCharge = CHARGEINFO::MAX_CHARGE;

		// ������Z�b�g
		m_isCharge = true;

		// ������Ԃ�
		return;
	}

	// �Q�[�W�l�����Z
	m_fCharge += fValue;
}
//================================
// ���Z����
//================================
void CCharge::DecCharge(float fValue)
{
	// 0�ȉ��̎�
	if (m_fCharge <= CHARGEINFO::MIN_CHARGE)
	{
		// 0�ɐݒ�
		m_fCharge = CHARGEINFO::MIN_CHARGE;

		// �t���O�𖳌���
		m_isCharge = false;

		// �e�̎�ނ�ύX
		CBullet::SetType(CBullet::BTYPE_PLAYER);

		// ������Ԃ�
		return;
	}

	// �Q�[�W�����炷
	m_fCharge -= fValue;
}
//================================
// ����������
//================================
HRESULT CCharge::Init(void)
{
	// �`���[�W��������
	m_fCharge = CHARGEINFO::MIN_CHARGE;

	// �e�N���X�̏���������
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CCharge::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CCharge::Update(void)
{
	// ��ނ��o�[�̎�
	if (m_nType == CHARGE_BAR)
	{
		// �Q�[�W�̒����ݒ�
		FSetGageLength(CHARGEINFO::MAX_CHARGE, m_fCharge, CHARGEINFO::CHAGE_LENGTH, CHARGEINFO::BAR_MAXHEIGHT);
	}

	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CCharge::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}
//================================
// �e�N�X�`�����蓖�ď���
//================================
void CCharge::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ����null�Ȃ�
	if (pTexture == nullptr) return;

	switch (nType)
	{
	case CHARGE_FRAME:	// �g
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser.png");
		break;

	case CHARGE_BAR:	// �{��
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\laser_gage.png");
		break;

	default:
		m_nIdxTex = -1;	// ��O�̒l
		break;
	}
}