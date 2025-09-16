//==========================================
//
// ���G�t�F�N�g���� [ effectsmoke.h ]
// Author : Asuma Nishi
//
//==========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "effectsmoke.h"
#include "manager.h"
#include "texture.h"

//=====================================
// �I�[�o�[���[�h�R���X�g���N�^
//=====================================
CEffectSmoke::CEffectSmoke(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_fRadius = NULL;
	m_nLife = NULL;
	m_move = VECTOR3_NULL;
}
//=====================================
// �f�X�g���N�^
//=====================================
CEffectSmoke::~CEffectSmoke()
{
	// ����
}
//=====================================
// ��������
//=====================================
CEffectSmoke* CEffectSmoke::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// �C���X�^���X����
	CEffectSmoke* pEffect = new CEffectSmoke;

	// null�Ȃ�
	if (pEffect == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pEffect->SetSize(fRadius, 40.0f);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->m_nLife = nLife;

	// ���������|�C���^��Ԃ�
	return pEffect;
}
//=====================================
// ����������
//=====================================
HRESULT CEffectSmoke::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CEffectSmoke::Uninit(void)
{
	// �e�N���X�̏I������
	CBillboard::Uninit();
}
//=====================================
// �X�V����
//=====================================
void CEffectSmoke::Update(void)
{
	// ���������Z
	m_nLife--;

	// 0�ȉ��Ȃ�
	if (m_nLife <= 0)
	{
		// �j��
		Uninit();

		// �����I��
		return;
	}

	// �e�N���X�X�V����
	CBillboard::Update();

	// �e�N�X�`���A�j���[�V����
	SetAnim(8,1,0.25f, 1.0f);
}
//=====================================
// �`�揈��
//=====================================
void CEffectSmoke::Draw(void)
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
//=====================================
// �e�N�X�`�����蓖�ď���
//=====================================
void CEffectSmoke::SetTexture(void)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();
	if (pTexture == nullptr) return;

	// ���蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\explosion000.png");
}