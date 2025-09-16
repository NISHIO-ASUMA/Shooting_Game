//==========================================
//
// ����G�t�F�N�g���� [ effectpiler.cpp ]
// Author: Asuma Nishio
//
// 
// TODO : ����̃G�t�F�N�g�쐬
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "effectpiler.h"
#include "manager.h"
#include "template.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CEffectPiler::CEffectPiler(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nLife = NULL;
	m_fRadius = NULL;
	m_nIdxTex = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CEffectPiler::~CEffectPiler()
{
	// ����
}
//===============================
// ��������
//===============================
CEffectPiler* CEffectPiler::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife)
{
	// �C���X�^���X����
	CEffectPiler* pEffect = new CEffectPiler;
	if (pEffect == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pEffect->SetPos(pos);
	pEffect->SetRot(rot);
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetCol(LASER);
	pEffect->SetTexture();

	pEffect->m_nLife = nLife;
	pEffect->m_fRadius = fRadius;

	// �������ꂽ�|�C���^��Ԃ�
	return pEffect;
}
//===============================
// ����������
//===============================
HRESULT CEffectPiler::Init(void)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CEffectPiler::Uninit(void)
{
	// �e�N���X�̏I������
	CBillboard::Uninit();
}
//===============================
// �X�V����
//===============================
void CEffectPiler::Update(void)
{
	// ���������炷
	m_nLife--;

	float fWidth = GetWidth();
	float fHeight = GetHeight();

	float maxHeight = 180.0f;	// �����̍ő卂��

	// �c�����ɐL�΂�
	float growSpeed = 5.0f;	// �c�ɐL�т�X�s�[�h

	if (fHeight < maxHeight)
	{
		fHeight += growSpeed;

		D3DXVECTOR3 pos = GetPos();
		pos.y += growSpeed;
		SetPos(pos);
	}

	// �傫���̍X�V
	SetSize(fWidth, fHeight);

	// �����؂�ō폜
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		// �����I��
		return;
	}

	// �e�N���X�̍X�V����
	CBillboard::Update();
}
//===============================
// �`�揈��
//===============================
void CEffectPiler::Draw(void)
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
void CEffectPiler::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// null�Ȃ�
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\effect000.jpg");
}