//====================================
//
// �r���{�[�h���� [ billboard.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"
#include "manager.h"

//================================
// �R���X�g���N�^
//================================
CBillboard::CBillboard(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_col = COLOR_WHITE;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_nIdxTexture = NULL;
	m_pVtxBuff = nullptr;
	m_mtxWorld = {};
	m_fWidth = NULL;
	m_fHeight = NULL;
	m_isTests = false;
	m_FlashCount = NULL;
	m_nCountAnim = NULL;
	m_nPatterAnim = NULL;
}
//================================
// �f�X�g���N�^
//================================
CBillboard::~CBillboard()
{
	// ����
}
//================================
// ��������
//================================
CBillboard* CBillboard::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,float fWidth, float fHeight)
{
	// �C���X�^���X����
	CBillboard* pBillboard = new CBillboard;

	// nullptr��������
	if (pBillboard == nullptr) return nullptr;

	// �I�u�W�F�N�g�Z�b�g
	pBillboard->SetPos(pos);
	pBillboard->SetSize(fWidth, fHeight);
	pBillboard->SetRot(rot);
	pBillboard->SetTexture();

	// ���������s��
	if (FAILED(pBillboard->Init()))
	{
		// ���s���ʂ�Ԃ�
		return nullptr;
	}

	// �r���{�[�h�̃|�C���^��Ԃ�
	return pBillboard;
}
//================================
// ����������
//================================
HRESULT CBillboard::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY, FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	// �@�����̐ݒ�
	pVtx[0].nor = 
	pVtx[1].nor = 
	pVtx[2].nor = 
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f,-1.0f);	

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = COLOR_WHITE;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//================================
// �I������
//================================
void CBillboard::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		// ���
		m_pVtxBuff->Release();

		// nullptr������
		m_pVtxBuff = nullptr;
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}
//================================
// �X�V����
//================================
void CBillboard::Update(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, m_fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, m_fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, -m_fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, -m_fHeight, 0.0f);

	// �e���_�̖@��(�x�N�g��)�̐ݒ�
	pVtx[0].nor = 
	pVtx[1].nor = 
	pVtx[2].nor = 
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);	// �@�����

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = m_col;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
//================================
// �`�揈��
//================================
void CBillboard::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���C�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �e�N�X�`����߂�
	// pDevice->SetTexture(0, CManager::GetTexture()->GetAddress(m_nIdxTexture));

	if (m_isTests)
	{
		// Z�e�X�g��K�p
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �r���[�}�g���b�N�X��錾
	D3DXMATRIX mtxView;

	// �r���[�}�g���b�N�X�̎擾
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �J�����̋t�s���ݒ�
	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;
	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;
	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

	if (m_isTests)
	{
		// Z�e�X�g��߂�
		pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	}

	// ���C�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//================================
// �e�N�X�`���Z�b�g
//================================
void CBillboard::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\Billboard_startmenu.png");
}
//================================
// UV�ݒ菈��
//================================
void CBillboard::SetUV(float fTexU, float fTexU1, float fTexV)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + fTexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + fTexU1, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + fTexU, fTexV);
	pVtx[3].tex = D3DXVECTOR2(0.0f + fTexU1, fTexV);

	//�A�����b�N
	m_pVtxBuff->Unlock();
}
//================================
// �A�j���[�V��������
//================================
void CBillboard::SetAnim(const int nMaxPattern,const int nMaxAnimCount,float fTexU, float fTexV)
{
	// �A�j���[�V�����J�E���^�[�����Z
	m_nCountAnim++;

	// �J�E���g��������傫���Ȃ�����
	if (m_nCountAnim >= nMaxAnimCount)
	{
		m_nCountAnim = 0;		// �J�E���^�[�������l�ɖ߂�

		m_nPatterAnim++;		// �p�^�[���i���o�[���X�V

		// �e�N�X�`�����W�X�V
		SetUV(m_nPatterAnim * fTexU, fTexU + m_nPatterAnim * fTexU, fTexV); // U,U1,V1���W
	}

	// �p�^�[���i���o�[���ő�l���傫���Ȃ�����
	if (m_nPatterAnim > nMaxPattern)
	{
		m_nPatterAnim = 0;			// �p�^�[���i���o�[�������l�ɖ߂�
	}
}
//================================
// �_�ŏ���
//================================
void CBillboard::Flash(const int nMaxFlashTime, const int Digittime)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �_�ŃJ�E���g�����Z
	m_FlashCount++;

	// �J���[�ϐ�
	D3DXCOLOR col = COLOR_WHITE;

	// �_�ŃJ�E���g�ƈ�v�����Ƃ�
	if (m_FlashCount == Digittime)		
	{
		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);
		col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.7f);

		// �J���[�Z�b�g
		SetCol(col);
	}
	else if (m_FlashCount == nMaxFlashTime)	// �ő�p�����Ԃƈ�v�����Ƃ�
	{
		//���_�J���[�̐ݒ�
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �J���[�Z�b�g
		SetCol(col);

		// �����l�ɖ߂�
		m_FlashCount = NULL;
	}

	//�A�����b�N
	m_pVtxBuff->Unlock();

}
