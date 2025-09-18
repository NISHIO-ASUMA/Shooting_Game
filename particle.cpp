//=====================================
//
// �p�[�e�B�N������ [ particle.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C��
//****************************
#include "particle.h"
#include "manager.h"
#include "effect.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CParticle::CParticle(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nMaxParticle = NULL;
	m_nLife = NULL;
	m_nLength = NULL;
	m_nRadius = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CParticle::~CParticle()
{
	// ����
}
//===============================
// ��������
//===============================
CParticle* CParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle,int nRadius,int nLength,int nLife)
{
	// �p�[�e�B�N���̃|�C���^��錾
	CParticle* pParticle = new CParticle;

	// null��������
	if (pParticle == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pParticle->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pParticle->m_pos = pos;
	pParticle->m_col = col;
	pParticle->m_nMaxParticle = nMaxParticle;
	pParticle->m_nLength = nLength;
	pParticle->m_nLife = nLife;
	pParticle->m_nRadius = nRadius;

	// �|�C���^��Ԃ�
	return pParticle;
}
//===============================
// ����������
//===============================
HRESULT CParticle::Init(void)
{
	// �z��N���A
	m_pEffect.clear();

	//�����̎��錾(1�݂̂̐錾)
	srand((unsigned int)time(NULL));

	return S_OK;
}
//===============================
// �I������
//===============================
void CParticle::Uninit(void)
{
	// �z��N���A
	m_pEffect.clear();

	// �e�N���X�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CParticle::Update(void)
{
	//�J���[�̐ݒ�
	D3DXCOLOR col = m_col;

	// ���W���擾
	D3DXVECTOR3 pos = m_pos;

	//�p�[�e�B�N���̐���
	for (int nCntApper = 0; nCntApper < m_nMaxParticle; nCntApper++)
	{
		// �ړ��ʂ̐ݒ�
		float fAngelX = (float)(rand() % 629 - 314) / 100.0f;
		float fAngelY = (float)(rand() % 629 - 314) / 100.0f;

		// �����ݒ�
		float fLength = ((float)(rand() % m_nLength) / 10.0f);

		// �ړ��ʕϐ�
		D3DXVECTOR3 Move = VECTOR3_NULL;

		// �ړ������ݒ�
		Move.x = sinf(fAngelX) * sinf(fAngelY) * fLength;
		Move.y = cosf(fAngelX) * fLength;
		Move.z = sinf(fAngelX) * cosf(fAngelY) * fLength;

		//���a�̐ݒ�
		float fRadius = ((float)(rand() % m_nRadius) / 10.0f + 0.7f);

		// �����̐ݒ�
		int nLife = ((float)(rand() % m_nLife) / 10);

		// �G�t�F�N�g����
		CEffect* pEffect = CEffect::Create(pos, col, Move, nLife, fRadius);

		if (pEffect)
		{
			// �z��ɒǉ�
			m_pEffect.push_back(pEffect);
		}
		else
		{
			break;
		}
	}

	// �j��
	Uninit();
}
//=========================
// �`�揈��
//==========================
void CParticle::Draw(void)
{
	// ����
}
