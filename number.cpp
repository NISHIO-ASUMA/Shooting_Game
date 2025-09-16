//====================================
//
// �������� [ number.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "number.h"
#include "manager.h"
#include "template.h"

//=================================
// �R���X�g���N�^
//=================================
CNumber::CNumber()
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_fHeight = NULL;
	m_fWidth = NULL;
	m_TexU = NULL;
	m_TexU1 = NULL;
	m_TexV = NULL;
	m_pVtxBuff = nullptr;
	m_col = COLOR_WHITE;
	n_nColorCount = NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CNumber::~CNumber()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CNumber::Init(D3DXVECTOR3 pos,float fwidth,float fheight)
{
	// �����l���
	m_pos = pos;

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;	

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(pos.x - fwidth, pos.y - fheight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fwidth, pos.y - fheight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fwidth, pos.y + fheight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fwidth, pos.y + fheight, 0.0f);

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(DIGIT_VALUE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(DIGIT_VALUE, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//=================================
// �I������
//=================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//=================================
// �X�V����
//=================================
void CNumber::Update(void)
{
	// ����
}
//=================================
// �`�揈��
//=================================
void CNumber::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`���߂�
	pDevice->SetTexture(0, NULL);
}
//==================================
// �T�C�Y����
//==================================
void CNumber::SetSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���W�X�V
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fWidth, m_pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fWidth, m_pos.y + fHeight, 0.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//===================================
// �J���[�ݒ�
//===================================
void CNumber::SetCol(D3DXCOLOR col)
{
	// ���
	m_col = col;

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[
	pVtx[0].col =
	pVtx[1].col =
	pVtx[2].col =
	pVtx[3].col = m_col;

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
//==================================
// �_�ŏ���
//==================================
void CNumber::SetFlash(const int nStartFrame, const int nEndFrame, D3DXCOLOR col)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N����
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�J�E���g�����Z
	n_nColorCount++;

	// �_�ł���������v�Z����
	int nCycle = nEndFrame - nStartFrame;
	if (nCycle <= 0) nCycle = 1;

	// �i�s�x��ݒ�
	float fProgress = static_cast<float>((n_nColorCount - nStartFrame) % nCycle) / static_cast<float>(nCycle);

	// �����x���i�[����
	float alpha = NULL;

	if (fProgress < 0.5f)
	{
		// ���`���
		alpha = Lerp(0.5f, 1.0f, fProgress * 2.0f);
	}
	else
	{
		// ���`���
		alpha = Lerp(1.0f, 0.5f, (fProgress - 0.5f) * 2.0f);
	}

	// �J���[�ݒ�
	D3DXCOLOR ChangeCol(col.r, col.g, col.b, alpha);

	// ���݃J���[�ɓK�p
	SetCol(ChangeCol);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
//==================================
// �����v�Z����
//==================================
void CNumber::SetDigit(int nDigit)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�̃��b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̌v�Z
	float TexU = nDigit * DIGIT_VALUE;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(TexU, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(TexU + DIGIT_VALUE, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(TexU, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(TexU + DIGIT_VALUE, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtxBuff->Unlock();
}
