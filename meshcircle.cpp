//=====================================
//
// �~�`���b�V������ [ meshcircle.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshcircle.h"
#include "manager.h"
#include "texture.h"
#include "effectsmoke.h"
#include "spread.h"

//**********************
// ���O���
//**********************
namespace CIRCLEINFO
{
	constexpr int NUM_XVERTEX = 30;	// ���_������ ( X )
	constexpr int NUM_ZVERTEX = 1;	// ���_������ ( Z )
	constexpr float CIRCLERADIUS = 60.0f;	// �ő�̔��a
	constexpr int NUMSPREAD = 16;	// �g�U�I�u�W�F�N�g�ő�o����
};

//===================================
// �I�[�o�[���[�h�R���X�g���N�^
//===================================
CMeshCircle::CMeshCircle(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A����
	m_pIdx = nullptr;
	m_pVtx = nullptr;

	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;

	m_nTexIdx = NULL;
	m_nNumIdx = NULL;
	m_nNumPrimitive = NULL;
	m_nNumDigitZ = NULL;
	m_nNumDigitX = NULL;
	m_nNumAllVtx = NULL;
	m_mtxWorld = {};
	m_fRadius = NULL;
	m_nLife = NULL;
}
//===================================
// �f�X�g���N�^
//===================================
CMeshCircle::~CMeshCircle()
{
	// ����
}
//===================================
// ��������
//===================================
CMeshCircle* CMeshCircle::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CMeshCircle* pMeshCircle = new CMeshCircle;

	// null�`�F�b�N
	if (pMeshCircle == nullptr)	return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pMeshCircle->m_pos = pos;

	// ���������s��
	if (FAILED(pMeshCircle->Init()))
	{
		return nullptr;
	}

	// ���G�t�F�N�g����
	CEffectSmoke::Create(pos, D3DXCOLOR(1.0f, 0.1f, 0.22f, 1.0f), VECTOR3_NULL, 50, 70.0f);

	// �������ꂽ�|�C���^��Ԃ�
	return pMeshCircle;
}
//===================================
// ����������
//===================================
HRESULT CMeshCircle::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_��,�C���f�b�N�X��,�|���S�������v�Z����
	m_nNumAllVtx = (CIRCLEINFO::NUM_XVERTEX + 1) * (CIRCLEINFO::NUM_ZVERTEX + 1);
	m_nNumPrimitive = m_nNumAllVtx - 2;
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
	float fTexX = 1.0f / CIRCLEINFO::NUM_XVERTEX;
	int nCnt = 0;

	// �@���ݒ�p
	D3DXVECTOR3 nor = VECTOR3_NULL;

	// �O�a�̌v�Z
	for (int nCntOut = 0; nCntOut <= CIRCLEINFO::NUM_XVERTEX; nCntOut++)
	{
		// �p�x���v�Z
		float fAngel = (D3DX_PI * 2.0f) / CIRCLEINFO::NUM_XVERTEX * nCntOut;

		// ���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * CIRCLEINFO::CIRCLERADIUS, 2.0f, cosf(fAngel) * CIRCLEINFO::CIRCLERADIUS);

		// �@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntOut, 1.0f);

		// ���Z
		nCnt++;
	}

	// ���a�̌v�Z
	for (int nCntIn = 0; nCntIn <= CIRCLEINFO::NUM_XVERTEX; nCntIn++)
	{
		// �p�x�v�Z
		float fAngel = (D3DX_PI * 2.0f) / CIRCLEINFO::NUM_XVERTEX * nCntIn;

		// ���_���W�̐ݒ�
		pVtx[nCnt].pos = D3DXVECTOR3(sinf(fAngel) * 0.5f, 2.0f, cosf(fAngel) * 0.5f);

		// �@���x�N�g���̐ݒ�
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���_�J���[�̐ݒ�
		pVtx[nCnt].col = D3DXCOLOR(1.0f,0.0f,0.0f,0.5f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[nCnt].tex = D3DXVECTOR2(fTexX * nCntIn, 1.0f);

		// ���Z
		nCnt++;
	}

	// ���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�|�C���^��錾
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = CIRCLEINFO::NUM_XVERTEX + 1;// X

	WORD IdxCnt = 0;// �z��

	WORD Num = 0;

	// �C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < CIRCLEINFO::NUM_ZVERTEX; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= CIRCLEINFO::NUM_XVERTEX; IndxCount2++, IndxNum++, Num++)
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

	// �̗͒l��ݒ�
	m_nLife = 90;

	// �T�[�N���̉~����ɐ΂ԂĂ𐶐�
	for (int nCntSpred = 0; nCntSpred < CIRCLEINFO::NUMSPREAD; nCntSpred++)
	{
		// �z�u�p�x���v�Z
		float fPopAngle = (D3DX_PI * 2.0f / CIRCLEINFO::NUMSPREAD) * nCntSpred;

		// �~����̍��W���v�Z
		float fRotX = sinf(fPopAngle) * CIRCLEINFO::CIRCLERADIUS;
		float fRotY = m_pos.y;
		float fRotZ = cosf(fPopAngle) * CIRCLEINFO::CIRCLERADIUS;

		// ���W�Z�b�g
		D3DXVECTOR3 MathPos(fRotX, fRotY, fRotZ);

		// ���[���h���W
		D3DXVECTOR3 pos = m_pos + MathPos;

		// �O�������x�N�g��
		D3DXVECTOR3 dir(sinf(fPopAngle), 0.0f, cosf(fPopAngle));

		// ���K��
		D3DXVec3Normalize(&dir, &dir);

		// ���W�Ɗp�x��ݒ�
		CSpread::Create(pos, dir);
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===================================
// �I������
//===================================
void CMeshCircle::Uninit(void)
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
//===================================
// �X�V����
//===================================
void CMeshCircle::Update(void)
{
	// ���Ԍo�߂ŏI������
	m_nLife--;

	if (m_nLife <= 0)
	{
		// �I������
		Uninit();
		return;
	}
}
//===================================
// �`�揈��
//===================================
void CMeshCircle::Draw(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

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
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumAllVtx, 0, m_nNumPrimitive);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);
}