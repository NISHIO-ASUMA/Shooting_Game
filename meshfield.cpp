//=============================================
//
// ���b�V���t�B�[���h���� [ meshfield.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshfield.h"
#include "manager.h"
#include "texture.h"

//*******************************
// �}�N����`
//*******************************
#define XVTX (1) // X�̒l
#define ZVTX (1) // Z�̒l

#define VERTEX ((XVTX + 1) * (ZVTX + 1))				 // ���_��
#define POLYGON (((XVTX * ZVTX) * 2)) + (4 * (ZVTX - 1)) // �|���S����
#define INDEX (POLYGON + 2)								 // �C���f�b�N�X��

//============================================
// �R���X�g���N�^
//============================================
CMeshField::CMeshField(int nPrio) : CObject(nPrio)
{
	// �l�̃N���A����
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
	m_nNumAllVtx = 0;
	m_nNumIdx = 0;
	m_nNumPrimitive = 0;
	m_nTexIdx = NULL;
}
//============================================
// �f�X�g���N�^
//============================================
CMeshField::~CMeshField()
{
	// ����
}
//============================================
// ��������
//============================================
CMeshField* CMeshField::Create(D3DXVECTOR3 pos, float fRadius)
{
	// �C���X�^���X����
	CMeshField* pMeshField = new CMeshField;

	// nullptr��������
	if (pMeshField == nullptr) return nullptr;

	// ���W���
	pMeshField->m_pos = pos;

	// ���a���
	pMeshField->m_fRadius = fRadius;

	// �e�N�X�`���ݒ�
	pMeshField->SetTexture();

	// ���������s��
	if (FAILED(pMeshField->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pMeshField;
}
//============================================
// �e�N�X�`���ݒ�
//============================================
void CMeshField::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// ���蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\DomeTex.jpg");
}
//============================================
// ����������
//============================================
HRESULT CMeshField::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// �ϐ��̏�����
	m_rot = VECTOR3_NULL;

	// ���_���̃|�C���^��錾
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W���v�Z����ϐ�
	float fTexX = 1.0f / XVTX;
	float fTexY = 1.0f / ZVTX;
	int nCnt = 0;

	//�c
	for (int nCntZ = 0; nCntZ <= ZVTX; nCntZ++)
	{
		//��
		for (int nCntX = 0; nCntX <= XVTX; nCntX++)
		{
			// ���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(
				(0.0f + (m_fRadius / XVTX) * nCntX) - (m_fRadius * 0.5f),
				 0.0f,
				 m_fRadius - ((m_fRadius / XVTX) * nCntZ) - (m_fRadius * 0.5f));

			// �@���x�N�g���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCnt].col = COLOR_WHITE;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntX, nCntZ * fTexY);

			// ���Z
			nCnt++;
		}
	}

	// �A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = XVTX + 1;// X

	WORD IdxCnt = 0;// �z��

	WORD Num = 0;

	// �C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < ZVTX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= XVTX; IndxCount2++, IndxNum++, Num++)
		{
			pIdx[IdxCnt] = IndxNum;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt += 2;
		}

		// NOTE:�Ō�̍s����Ȃ�������
		if (IndxCount1 < ZVTX - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxNum;
			IdxCnt += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdx->Unlock();

	return S_OK;
}
//============================================
// �I������
//============================================
void CMeshField::Uninit(void)
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
//============================================
// �X�V����
//============================================
void CMeshField::Update(void)
{
	// ����
}
//============================================
// �`�揈��
//============================================
void CMeshField::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �Z�b�g
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

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdx);

	// �e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, VERTEX, 0, POLYGON);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
}