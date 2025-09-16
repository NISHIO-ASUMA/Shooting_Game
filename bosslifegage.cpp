//=========================================
//
// �{�X�̗͏��� [ bosslifegage.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bosslifegage.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"
#include "object2D.h"

//**********************
// �萔�錾
//**********************
namespace BOSSLIFE
{
	constexpr float VALUELENGTH = 0.32f;	// �����l
	constexpr float HEIGHT = 60.0f;			// ����
};

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CBossLifeGage::CBossLifeGage(int nPriority) : CGage(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_pBoss = nullptr;

	m_nCurrentLifeLength = NULL;
	m_nMaxLifeLength = NULL;
	m_Type = TYPE_FRAME;
}
//===============================
// �f�X�g���N�^
//===============================
CBossLifeGage::~CBossLifeGage()
{
	// ����
}
//===============================
// ��������
//===============================
CBossLifeGage* CBossLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// �C���X�^���X����
	CBossLifeGage* pBossLife = new CBossLifeGage;

	// null��������
	if (pBossLife == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pBossLife->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pBossLife->SetPos(pos);
	pBossLife->SetSize(fWidth, fHeight);
	pBossLife->SetType(nType);
	pBossLife->SetTexture(nType);
	pBossLife->SetAnchor(CObject2D::ANCHORTYPE_LEFTSIDE);

	// �������ꂽ�|�C���^��Ԃ�
	return pBossLife;
}
//===============================
// ����������
//===============================
HRESULT CBossLifeGage::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// �{�X�̎擾
	if (m_pBoss == nullptr)
	{
		m_pBoss = CGameManager::GetBoss();
	}

	// �擾�ł�����
	if (m_pBoss != nullptr)
	{
		// �p�����[�^�[�擾
		CParameter* pParam = m_pBoss->GetParam();

		// �ő�l�̗͂�ݒ肷��
		m_nMaxLifeLength = pParam->GetMaxHp();
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CBossLifeGage::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//===============================
// �X�V����
//===============================
void CBossLifeGage::Update(void)
{
	// ���S���Ă�����
	if (m_pBoss->IsDaeth()) return;

	// null����Ȃ� ���� ��ނ��o�[�̎�
	if (m_pBoss != nullptr && m_Type == TYPE_GAGE)
	{
		// �p�����[�^�[�擾
		CParameter* pParam = m_pBoss->GetParam();

		// ���݂̗̑͂��擾
		m_nCurrentLifeLength = pParam->GetHp();

		// �Q�[�W�̒����ݒ�
		SetGageLength(m_nMaxLifeLength, m_nCurrentLifeLength, BOSSLIFE::VALUELENGTH, BOSSLIFE::HEIGHT);
	}

	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//===============================
// �`�揈��
//===============================
void CBossLifeGage::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �e�N���X�̕`��
	CObject2D::Draw();
}
//===============================
// �e�N�X�`�����蓖�ď���
//===============================
void CBossLifeGage::SetTexture(int nType)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	switch (nType)
	{
	case CBossLifeGage::TYPE_FRAME:	// �O�g

		// �e�N�X�`�����蓖��
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\bosslife_frame.png");
		break;

	case CBossLifeGage::TYPE_GAGE:	// �̗̓o�[

		// �e�N�X�`�����蓖��
		m_nIdxTex = pTexture->Register("data\\TEXTURE\\boss_life.png");
		break;

	default:
		m_nIdxTex = -1;
		break;
	}
}
