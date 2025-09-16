//============================================
//
// ���b�V���C���p�N�g���� [ meshimpact.cpp ]
// Author: Asuma Nishio
// 
//=============================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshimpact.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "effect.h"

//**********************
// �萔�錾
//**********************
namespace IMPACTINFO
{
	constexpr int NUM_X = 30; // X���ʂ̕�����
	constexpr int NUM_Z = 1;  // Z���ʂ̕�����
	constexpr int VERTEX = (NUM_X + 1) * (NUM_Z + 1); // ���_��
	constexpr int PRIM = (VERTEX - 2);				  // �|���S����
	constexpr int INDEX = (VERTEX + 2);				  // �C���f�b�N�X�o�b�t�@��
	constexpr float HEIGHTSIZE = 3.0f;
}

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CMeshImpact::CMeshImpact(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_col = COLOR_WHITE;
	m_mtxWorld = {};
	m_pIdx = nullptr;
	m_pVtx = nullptr;
	m_fInRadius = NULL;
	m_nLife = NULL;
	m_fOutRadius = NULL;
	m_fSpeed = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CMeshImpact::~CMeshImpact()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CMeshImpact::Init(void)
{
	// �e�N�X�`�����W�v�Z
	float fTex = 1.0f / IMPACTINFO::NUM_X;

	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * IMPACTINFO::VERTEX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// ���_�o�b�t�@�̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�J�E���g�p�̕ϐ�
	int nCnt = 0;

	//���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	D3DXCOLOR col = m_col;

	// ���W���
	D3DXVECTOR3 pos = m_pos;

	// �O���̔��a
	float OutRadius = m_fOutRadius;

	// �O�a�̌v�Z
	for (int nCntOut = 0; nCntOut <= IMPACTINFO::NUM_X; nCntOut++)
	{
		// �p�x���v�Z
		float fAngel = (D3DX_PI * 2.0f) / IMPACTINFO::NUM_X * nCntOut;

		// ���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * OutRadius,2.0f,cosf(fAngel) * OutRadius);

		// �@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = col;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(fTex * nCntOut, 1.0f);

		// ���Z
		nCnt++;
	}

	// �����̔��a
	float InRadius = m_fInRadius;

	// ���a�̌v�Z
	for (int nCntIn = 0; nCntIn <= IMPACTINFO::NUM_X; nCntIn++)
	{
		// �p�x�v�Z
		float fAngel = (D3DX_PI * 2.0f) / IMPACTINFO::NUM_X * nCntIn;

		// ���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * InRadius,2.0f,cosf(fAngel) * InRadius);

		// �@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = col;

		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(fTex * nCntIn, 1.0f);

		// ���Z
		nCnt++;
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * IMPACTINFO::INDEX,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdx,
		NULL);

	// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	WORD* pIdx;

	//�C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	// X�����ւ̕�����
	WORD IndxNum = IMPACTINFO::NUM_X + 1;

	// �z��
	WORD IdxCnt = 0;

	// �i�[�p�ϐ�
	WORD Num = 0;

	// �C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < IMPACTINFO::NUM_Z; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= IMPACTINFO::NUM_X; IndxCount2++, IndxNum++, Num++)
		{
			pIdx[IdxCnt] = IndxNum;
			pIdx[IdxCnt + 1] = Num;
			IdxCnt += 2;
		}

		// NOTE:�Ō�̍s����Ȃ�������
		if (IndxCount1 < IMPACTINFO::NUM_Z - 1)
		{
			pIdx[IdxCnt] = Num - 1;
			pIdx[IdxCnt + 1] = IndxNum;
			IdxCnt += 2;
		}
	}

	// �C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_pIdx->Unlock();

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CMeshImpact::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtx != nullptr)
	{
		// ���,nullptr��
		m_pVtx->Release();
		m_pVtx = nullptr;
	}

	// �C���f�b�N�X�o�b�t�@�̔j��
	if (m_pIdx != nullptr)
	{
		// ���,nullptr��
		m_pIdx->Release();
		m_pIdx = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CMeshImpact::Update(void)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// ���_�v�Z�ϐ�
	int nCntVertex = NULL;

	// �J���[�ݒ�
	m_col = D3DXCOLOR(1.0f, 1.0f, 0.0f,0.7f);

	// ���x�����Z,���񂾂�L����
	m_fOutRadius += m_fSpeed;
	m_fInRadius += m_fSpeed;

	//���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// ���W���
	D3DXVECTOR3 pos = m_pos;

	// X���W�����ւ̕����� (�O��)
	for (int nCntImpact = 0; nCntImpact <= IMPACTINFO::NUM_X; nCntImpact++)
	{
		// �p�x�̌v�Z
		float fAngel = (D3DX_PI * 2.0f) / IMPACTINFO::NUM_X * nCntImpact;

		// ���_���W�̐ݒ�
		pVtx[nCntVertex].pos = D3DXVECTOR3(
			sinf(fAngel) * m_fOutRadius,
			3.0f,
			cosf(fAngel) * m_fOutRadius);

		// �J���[�̐ݒ�
		pVtx[nCntVertex].col = m_col;

		// ���_�J�E���g���C���N�������g
		nCntVertex++;
	}

	//  X���W�����ւ̕����� (����)
	for (int nCntImpact = 0; nCntImpact <= IMPACTINFO::NUM_X; nCntImpact++)
	{
		// �p�x���v�Z
		float fAngel = (D3DX_PI * 2.0f) / IMPACTINFO::NUM_X * nCntImpact;

		// ���_���W�̐ݒ�
		pVtx[nCntVertex].pos = D3DXVECTOR3(
			sinf(fAngel) * m_fInRadius,
			3.0f,
			cosf(fAngel) * m_fInRadius);

		// ���_�J���[�̐ݒ�
		pVtx[nCntVertex].col = m_col;

		// ���_�J�E���g���C���N�������g
		nCntVertex++;
	}

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtx->Unlock();

	// ���������炷
	m_nLife--;

	// TODO : ������̗͂ɉ����ē����ɂ��Ă��������ɕύX
	m_col.a -= 0.5f;

	// �������s����
	if (m_nLife <= 0)
	{
		// ���g�p�ɂ���
		Release();

		// ������Ԃ�
		return;
	}
}
//===============================
// �`�揈��
//===============================
void CMeshImpact::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// Z�e�X�g��K�p
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���u�����f�B���O�̉��Z����
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

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
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, IMPACTINFO::VERTEX, 0, IMPACTINFO::PRIM);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

	// Z�e�X�g��߂�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���u�����f�B���O��߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �f�o�b�O�t�H���g
	CDebugproc::Print("�Ռ��g�̍��W { %.2f,%.2f,%.2f }", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(1000,180);
}
//===============================
// ��������
//===============================
CMeshImpact* CMeshImpact::Create(D3DXVECTOR3 pos, int nLife,float fOutRadius,float fInRadius, float fSpeed)
{
	// �C���X�^���X����
	CMeshImpact* pMesh = new CMeshImpact;

	// �C���X�^���X��nullptr��������
	if (pMesh == nullptr) return nullptr;

	// �l����
	pMesh->m_pos = pos;				// ���W
	pMesh->m_fInRadius = fInRadius; // ���a
	pMesh->m_fOutRadius = fOutRadius; // �O�a
	pMesh->m_nLife = nLife;			// �p������
	pMesh->m_fSpeed = fSpeed;		// �g�U���x
	pMesh->SetObjType(TYPE_MESH);   // �I�u�W�F�N�g�̃^�C�v��ݒ�

	// ���������s��
	if (FAILED(pMesh->Init()))
	{
		// �|�C���^�̔j��
		delete pMesh;

		// nullptr���
		pMesh = nullptr;

		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pMesh;
}
//===============================
// �����蔻�菈��
//===============================
bool CMeshImpact::Collision(D3DXVECTOR3* pPos)
{
	// ���_���̃|�C���^
	VERTEX_3D* pVtx = nullptr;

	// �t���O�ϐ�
	bool isHit = false;

	// ���_�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// X���W�̕������Ō���
	for (int nCnt = 0; nCnt < IMPACTINFO::NUM_X; nCnt++)
	{
		// �C���p�N�g���_�̃��[���h���W�Ƃ�XZ�������v�Z
		float dx = pPos->x - (m_pos.x + pVtx[nCnt].pos.x);
		float dy = pPos->y - (m_pos.y + pVtx[nCnt].pos.y);
		float dz = pPos->z - (m_pos.z + pVtx[nCnt].pos.z);

		// ���a�̍������Ƃ�
		float fDisSize = (m_fOutRadius - m_fInRadius);

		// Y�����ŊO��Ă�Ȃ瓖����Ȃ�
		if (dy > IMPACTINFO::HEIGHTSIZE)
		{
			continue;
		}

		// XZ���ʂ͈̔͌v�Z
		float fDisVerTexXZ = sqrtf(dx * dx + dz * dz);

		// �������������Ȃ�����
		if (fDisVerTexXZ <= fDisSize)
		{
			// �������Ă���
			isHit = true;
		}
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// ���茋�ʂ�Ԃ�
	return isHit;
}