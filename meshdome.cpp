//=====================================
//
// ���b�V���h�[������ [ meshdome.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshdome.h"
#include "manager.h"
#include "texture.h"

//==================================
// �R���X�g���N�^
//==================================
CMeshDome::CMeshDome(int nPrio) : CObject(nPrio)
{
	// �l�̃N���A����
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxWorld = {};
	m_nRadius = NULL;

	m_nTexIdx = NULL;
}
//==================================
// �f�X�g���N�^
//==================================
CMeshDome::~CMeshDome()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CMeshDome::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MeshDome_VERTEX_NUM,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * MeshDome_INDEX_NUM,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// ���_�o�b�t�@�̃|�C���^
	VERTEX_3D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntV = 0; nCntV <= MeshDome_Z_BLOCK; nCntV++)
	{
		for (int nCntH = 0; nCntH <= MeshDome_X_BLOCK; nCntH++)
		{
			// nCntH�Ԗڂ̊p�x���v�Z
			float angleH = (360.0f / MeshDome_X_BLOCK) * nCntH;

			// nCntV�Ԗڂ̊p�x���v�Z
			float angleV = 90.0f * ((float)nCntV / MeshDome_Z_BLOCK);

			// ���_�̈ʒu��ݒ�
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos = D3DXVECTOR3(
				sinf(D3DXToRadian(angleH)) * m_nRadius * cosf(D3DXToRadian(angleV)), // X���W
				m_nRadius * sinf(D3DXToRadian(angleV)),								 // Y���W
				cosf(D3DXToRadian(angleH)) * m_nRadius * cosf(D3DXToRadian(angleV))  // Z���W
			);

			// �@�����v�Z (���_���W����̒P�ʃx�N�g��)
			D3DXVECTOR3 normal = D3DXVECTOR3(
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.x / m_nRadius,
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.y / m_nRadius,
				pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].pos.z / m_nRadius
			);

			// ���K������
			D3DXVec3Normalize(&normal, &normal);

			// �@���Ɋ��蓖��
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].nor = normal;

			// ���_�J���[��ݒ�
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].col = COLOR_WHITE;

			// �e�N�X�`�����W��ݒ�
			pVtx[nCntV * (MeshDome_X_BLOCK + 1) + nCntH].tex = D3DXVECTOR2(
				(float)nCntH / MeshDome_X_BLOCK,						// U���W�i�~�������j
				1.0f - (float)nCntV / MeshDome_Z_BLOCK				    // V���W�i���������j
			);
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx = NULL;

	// �C���f�b�N�X�o�b�t�@�����b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	// �C���f�b�N�X�̐ݒ�
	WORD idx = 0;

	for (int nCntV = 0; nCntV < MeshDome_Z_BLOCK; nCntV++)
	{
		for (int nCntX = 0; nCntX < MeshDome_X_BLOCK; nCntX++)
		{
			// ��̃C���f�b�N�X
			WORD baseIndex = nCntV * (MeshDome_X_BLOCK + 1) + nCntX;

			// �O�p�`1
			pIdx[idx++] = baseIndex;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 1;
			pIdx[idx++] = baseIndex + 1;

			// �O�p�`2
			pIdx[idx++] = baseIndex + 1;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 1;
			pIdx[idx++] = baseIndex + MeshDome_X_BLOCK + 2;
		}

	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdx->Unlock();

	return S_OK;
}
//==================================
// �I������
//==================================
void CMeshDome::Uninit(void)
{
	// ���_�o�b�t�@�̉��
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdx != nullptr)
	{
		m_pIdx->Release();
		m_pIdx = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//==================================
// �X�V����
//==================================
void CMeshDome::Update(void)
{
	// ����
}
//==================================
// �`�揈��
//==================================
void CMeshDome::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdx);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, MeshDome_VERTEX_NUM, 0, MeshDome_INDEX_NUM);

	// �e�N�X�`��NULL
	pDevice->SetTexture(0, NULL);
}
//==================================
// ��������
//==================================
CMeshDome* CMeshDome::Create(D3DXVECTOR3 pos, float nRadius)
{
	// �C���X�^���X����
	CMeshDome* pMeshDome = new CMeshDome;

	// nullptr��������
	if (pMeshDome == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pMeshDome->m_pos = pos;
	pMeshDome->m_nRadius = nRadius;
	pMeshDome->SetTexture();

	// ���������s��
	if (FAILED(pMeshDome->Init()))
	{
		// nulptr��Ԃ�
		return nullptr;
	}

	// �h�[���̃|�C���^��Ԃ�
	return pMeshDome;
}
//==================================
// �e�N�X�`���ݒ�
//==================================
void CMeshDome::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\DomeTex.jpg");
}
