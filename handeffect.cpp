//========================================
//
// �n���h�G�t�F�N�g���� [ handeffect.cpp ]
// Author: Asuma Nishio
//
//========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "handeffect.h"
#include "manager.h"
#include "texture.h"

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CHandEffect::CHandEffect(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nIdxTexture = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;

}
//==============================
// �f�X�g���N�^
//==============================
CHandEffect::~CHandEffect()
{

}
//==============================
// ��������
//==============================
CHandEffect* CHandEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// �G�t�F�N�g�|�C���^
	CHandEffect* pEffect = new CHandEffect;

	// nullptr��������
	if (pEffect == nullptr) return nullptr;

	// �e�N�X�`���Z�b�g
	pEffect->SetTexture();

	// �������Ɏ��s������
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// 3D�I�u�W�F�N�g�Z�b�g
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);

	// �����o�ϐ��ɑ��
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->m_nLife = nLife;

	// �G�t�F�N�g�|�C���^��Ԃ�
	return pEffect;
}
//==============================
// ����������
//==============================
HRESULT CHandEffect::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	return S_OK;
}
//==============================
// �I������
//==============================
void CHandEffect::Uninit(void)
{
	// �e�N���X�̏I��
	CBillboard::Uninit();
}
//==============================
// �X�V����
//==============================
void CHandEffect::Update(void)
{
	// ���W,�J���[�擾
	D3DXVECTOR3 Effectpos = GetPos();

	//�J���[�̐ݒ�
	D3DXCOLOR col = GetCol();

	// �I�u�W�F�N�g�X�V
	CBillboard::Update();

	// �ړ��ʂ̍X�V
	Effectpos += m_move;

	// ���a���f�N�������g
	m_fRadius -= 0.015f;

	// ���l������
	col.a -= 0.005f;

	// ���W���Z�b�g����
	SetPos(Effectpos);

	// �F
	SetCol(col);

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
	}
}
//==============================
// �`�揈��
//==============================
void CHandEffect::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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

	// �r���{�[�h�`��
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
//==============================
// �e�N�X�`�����蓖�ď���
//==============================
void CHandEffect::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`����o�^����
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\handeffect.jpg");
}