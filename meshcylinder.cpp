//=============================================
//
// ���b�V���V�����_�[���� [ meshcylinder.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshcylinder.h"
#include "manager.h"
#include "texture.h"
#include "debugproc.h"

//===============================
// �R���X�g���N�^
//===============================
CMeshCylinder::CMeshCylinder(int nPrio) : CObject(nPrio)
{
	// �l�̃N���A����
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < DIGIT_X; nCnt++)
	{
		m_vtxPos[nCnt] = VECTOR3_NULL;
	}

	m_nTexIdx = NULL;
	m_nNumIdx = NULL;
	m_nNumPrimitive = NULL;
	m_nNumDigitZ = NULL;
	m_nNumDigitX = NULL;
	m_nNumAllVtx = NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CMeshCylinder::~CMeshCylinder()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CMeshCylinder::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_��,�C���f�b�N�X��,�|���S�������v�Z����
	m_nNumAllVtx = (DIGIT_X + 1) * (DIGIT_Z + 1);
	m_nNumPrimitive = ((DIGIT_X * DIGIT_Z) * 2) + (4 * (DIGIT_Z - 1));
	m_nNumIdx = (m_nNumPrimitive + 2);

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumAllVtx,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	//�C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// ���_���̃|�C���^
	VERTEX_3D* pVtx = NULL;

	//���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	float fTexX = 1.0f / DIGIT_X;
	float fTexY = 1.0f / DIGIT_Z;
	int nCnt = 0;

	// �@���ݒ�p
	D3DXVECTOR3 nor = VECTOR3_NULL;

	// �c
	for (int nCntZ = 0; nCntZ <= DIGIT_Z; nCntZ++)
	{
		// ��
		for (int nCntX = 0; nCntX <= DIGIT_X; nCntX++)
		{
			// �p�x�v�Z
			float fAngle = (D3DX_PI * 2.0f) / DIGIT_X * nCntX;

			// ���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(sinf((fAngle)) * m_fRadius, nCntZ * 10.0f, cosf((fAngle)) * m_fRadius);

			// �@���x�N�g���̐ݒ�
			nor = pVtx[nCnt].pos - m_pos;	// �e���_���猴�_�̒l������
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);	// �@���̐��K��

			// �@���x�N�g���̐ݒ�
			pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���_�J���[�̐ݒ�
			pVtx[nCnt].col = COLOR_NULL;

			// �e�N�X�`�����W�̐ݒ�
			pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntX, nCntZ * fTexY);

			// ���Z
			nCnt++;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�|�C���^��錾
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = DIGIT_X + 1;// X

	WORD IdxCnt = 0;// �z��

	WORD Num = 0;

	// �C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < DIGIT_Z; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= DIGIT_X; IndxCount2++, IndxNum++, Num++)
		{
			pIdx[IdxCnt] = IndxNum;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt += 2;
		}

		// �Ō�̍s����Ȃ�������
		if (IndxCount1 < m_nNumDigitZ - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxNum;
			IdxCnt += 2;
		}
	}

	//�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdx->Unlock();

	return S_OK;
}
//===============================
// �I������
//===============================
void CMeshCylinder::Uninit(void)
{
	//���_�o�b�t�@�̉��
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}

	//�C���f�b�N�X�o�b�t�@�̉��
	if (m_pIdx != nullptr)
	{
		m_pIdx->Release();
		m_pIdx = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CMeshCylinder::Update(void)
{
	// �Ȃ�
}
//===============================
// �`�揈��
//===============================
void CMeshCylinder::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nTexIdx));

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdx);

	//�e�N�X�`���t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumAllVtx, 0, m_nNumPrimitive);

	//�e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

	// �f�o�b�O�\��
	CDebugproc::Print("���b�V���V�����_�[�̍��W [ %.2f,%.2f,%.2f ]", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 80);
}
//===============================
// �e�N�X�`�����蓖��
//===============================
void CMeshCylinder::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\field100.jpg");
}
//===============================
// ��������
//===============================
CMeshCylinder* CMeshCylinder::Create(D3DXVECTOR3 pos, float fRadius)
{
	// �C���X�^���X����
	CMeshCylinder* pMeshcylinder = new CMeshCylinder;

	// nullptr��������
	if (pMeshcylinder == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pMeshcylinder->SetTexture();
	pMeshcylinder->m_pos = pos;
	pMeshcylinder->m_fRadius = fRadius;

	// ���������s��
	if (FAILED(pMeshcylinder->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �|�C���^��Ԃ�
	return pMeshcylinder;
}