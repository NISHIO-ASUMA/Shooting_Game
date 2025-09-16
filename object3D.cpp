//=====================================
//
// 3D�I�u�W�F�N�g���� [ object3D.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object3D.h"
#include "texture.h"
#include "manager.h"

//===============================
// �R���X�g���N�^
//===============================
CObject3D::CObject3D(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pVtxBuff = nullptr;
	m_mtxWorld = {};
	m_rot = VECTOR3_NULL;
	m_pos = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_nIdxTexture = NULL;
	m_fWidth = NULL;
	m_fHeight = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CObject3D::~CObject3D()
{
	// ����
}
//===============================
// ��������
//===============================
CObject3D* CObject3D::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CObject3D* pObj3D = new CObject3D;

	// nullptr��������
	if (pObj3D == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pObj3D->SetPos(pos);
	pObj3D->SetTexture();

	// �������������s��
	if (FAILED(pObj3D->Init()))
	{
		// nullptr���
		pObj3D = nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pObj3D;
}
//===============================
// ����������
//===============================
HRESULT CObject3D::Init(void)
{
	// �f�o�C�X�|�C���^��錾
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
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 0.0f, m_fWidth);	// 1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, 0.0f, m_fWidth);	// 2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 0.0f, -m_fWidth);	// 3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 0.0f, -m_fWidth);	// 4�ڂ̒��_���

	// �e���_�̖@��(�x�N�g��)�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 1�ڂ̖@�����
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 2�ڂ̖@�����
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 3�ڂ̖@�����
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 4�ڂ̖@�����

	// ���_�J���[�̐ݒ�
	pVtx[0].col = COLOR_WHITE;
	pVtx[1].col = COLOR_WHITE;
	pVtx[2].col = COLOR_WHITE;
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
//===============================
// �I������
//===============================
void CObject3D::Uninit(void)
{
	// �o�b�t�@���
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CObject3D::Update(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWidth, 5.0f, m_fWidth);	// 1�ڂ̒��_���
	pVtx[1].pos = D3DXVECTOR3(m_fWidth, 5.0f, m_fWidth);	// 2�ڂ̒��_���
	pVtx[2].pos = D3DXVECTOR3(-m_fWidth, 5.0f, -m_fWidth);	// 3�ڂ̒��_���
	pVtx[3].pos = D3DXVECTOR3(m_fWidth, 5.0f, -m_fWidth);	// 4�ڂ̒��_���

	// �e���_�̖@��(�x�N�g��)�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 1�ڂ̖@�����
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 2�ڂ̖@�����
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 3�ڂ̖@�����
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 4�ڂ̖@�����

	// ���_�J���[�̐ݒ�
	pVtx[0].col = COLOR_WHITE;
	pVtx[1].col = COLOR_WHITE;
	pVtx[2].col = COLOR_WHITE;
	pVtx[3].col = COLOR_WHITE;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}
//===============================
// �`�揈��
//===============================
void CObject3D::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y,m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// �e�N�X�`��NULL�ɂ���
	pDevice->SetTexture(0, NULL);
}
//===============================
// �e�N�X�`�����蓖��
//===============================
void CObject3D::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\field100.jpg");
}
//===============================
// �I�u�W�F�N�g�̍����擾
//===============================
float CObject3D::GetHeight(D3DXVECTOR3 pos)
{
	// �x�N�g���v�Z�p�ϐ�
	float fHeight = 0.0f;

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 Cross1, Cross2, Cross3;
	D3DXVECTOR3 Pvec1, Pvec2, Pvec3;
	D3DXVECTOR3 Vec1, Vec2,Vec3, nor;

	// �n�_�x�N�g��
	Vec1 = pVtx[0].pos - pVtx[2].pos;
	Pvec1 = pos - pVtx[2].pos;

	Vec2 = pVtx[1].pos - pVtx[0].pos;
	Pvec2 = pos - pVtx[0].pos;

	Vec3 = pVtx[2].pos - pVtx[1].pos;
	Pvec3 = pos - pVtx[1].pos;

	// �O�όv�Z
	D3DXVec3Cross(&Cross1, &Vec1, &Pvec1);
	D3DXVec3Cross(&Cross2, &Vec2, &Pvec2);
	D3DXVec3Cross(&Cross3, &Vec3, &Pvec3);

	// ���K������
	D3DXVec3Normalize(&Cross1, &Cross1);
	D3DXVec3Normalize(&Cross2, &Cross2);
	D3DXVec3Normalize(&Cross3, &Cross3);

	D3DXVECTOR3 edge1, edge2;

	// �x�N�g������
	edge1 = pVtx[2].pos - pVtx[0].pos;
	edge2 = pVtx[1].pos - pVtx[0].pos;

	// �O�όv�Z
	D3DXVec3Cross(&nor, &edge2, &edge1);

	// ���߂��x�N�g���𐳋K������
	D3DXVec3Normalize(&nor, &nor);

	// ����������
	if (Cross1.y >= 0.0f && Cross2.y >= 0.0f && Cross3.y >= 0.0f)
	{
		// ����Ă��鎞
		if (nor.y != 0.0f)
		{
			// �����v�Z
			fHeight = ((-nor.x * (pos.x - pVtx[0].pos.x)) - (nor.z * (pos.z - pVtx[0].pos.z))) / nor.y + pVtx[0].pos.y;
		}
	}

	// �A�����b�N
	m_pVtxBuff->Unlock();

	// �l��Ԃ�
	return fHeight;

}