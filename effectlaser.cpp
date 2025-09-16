//===================================================
//
// ���[�U�[�G�t�F�N�g���� [ effectlaser.cpp ]
// Author: Asuma Nishio
//
//===================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "effectlaser.h"
#include "manager.h"
#include "texture.h"

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CEffectLaser::CEffectLaser(int nPriority) : CBillboard(nPriority)
{
	m_nIdxTex = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;
	m_fLength = NULL;
	m_EndPos = VECTOR3_NULL;
	m_OldPos = VECTOR3_NULL;
}
//====================================
// �f�X�g���N�^
//====================================
CEffectLaser::~CEffectLaser()
{
	// ����
}
//====================================
// ��������
//====================================
CEffectLaser* CEffectLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// �C���X�^���X����
	CEffectLaser* pLaser = new CEffectLaser;

	// null�Ȃ�
	if (pLaser == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLaser->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pLaser->SetTexture();
	pLaser->SetPos(pos);
	pLaser->SetSize(fRadius, fRadius);
	pLaser->SetCol(col);

	pLaser->m_fRadius = fRadius;
	pLaser->m_nLife = nLife;
	pLaser->m_EndPos = Endpos;

	// �������ꂽ�|�C���^��Ԃ�
	return pLaser;
}
//====================================
// ����������
//====================================
HRESULT CEffectLaser::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//====================================
// �I������
//====================================
void CEffectLaser::Uninit(void)
{
	// �e�N���X�̏I��
	CBillboard::Uninit();
}
//====================================
// �X�V����
//====================================
void CEffectLaser::Update(void)
{
	// ���W,�J���[�擾
	D3DXVECTOR3 Effectpos = GetPos();

	// �I�u�W�F�N�g�X�V
	CBillboard::Update();

	// �ړ��ʂ̍X�V
	Effectpos += m_move;

	// ���a���f�N�������g
	m_fRadius -= 0.05f;

	if (Effectpos > m_EndPos)
	{
		// �I�[���W�ɐݒ�
		Effectpos = m_EndPos;

		// �̗͂�0�ɂ���
		m_nLife = 0;
	}

	// ���W���Z�b�g����
	SetPos(Effectpos);

	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// �T�C�Y�Z�b�g
	SetSize(m_fRadius, m_fRadius);

	// �̗͂����炷
	m_nLife--;

	// 0�ȉ��̎�
	if (m_nLife <= 0)
	{
		// �폜����
		Uninit();

		return;
	}

	// �I�u�W�F�N�g�X�V
	CBillboard::Update();
}
//====================================
// �`�揈��
//====================================
void CEffectLaser::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// ���u�����f�B���O�̉��Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���e�X�g��L��
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Z�e�X�g��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	//�@�e�N���X�`��
	CBillboard::Draw();

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// ���u�����f�B���O��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}
//====================================
// �e�N�X�`�����蓖�ď���
//====================================
void CEffectLaser::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�Ȃ�
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}