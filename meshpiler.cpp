//==================================
//
// �����b�V������ [ meshpiler.cpp ]
// Author: Asuma Nishio
//
//==================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "meshpiler.h"
#include "texture.h"
#include "manager.h"
#include "template.h"

//**********************
// ���O���
//**********************
namespace PILERINFO
{
	constexpr int NUMX = 30;	// ���_������ ( X )
	constexpr int NUMZ = 1;		// ���_������ ( Z )
	constexpr float VALUEHEIGHT = 800.0f;	// �����̍ő���Z��
	constexpr float COLLISIONRADIUS = 60.0f;// �R���W�������锼�a
	constexpr float MOVESPEED = 15.0f;	// ����
};

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CMeshPiler::CMeshPiler(int nPrio) : CObject(nPrio)
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
	m_fMoveSpeed = NULL;
	m_fNowHeight = NULL;
	m_nLife = NULL;

	m_nLifeFrame = NULL;
	m_nActiveDelay = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CMeshPiler::~CMeshPiler()
{
	// ����
}
//===============================
// ��������
//===============================
CMeshPiler* CMeshPiler::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CMeshPiler* pMesh = new CMeshPiler;

	// null�`�F�b�N
	if (pMesh == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pMesh->SetTexture();
	pMesh->m_pos = pos;

	// ���������s��
	if (FAILED(pMesh->Init()))
	{
		return nullptr;
	}
	
	// �������ꂽ�|�C���^��Ԃ�
	return pMesh;
}
//===============================
// ����������
//===============================
HRESULT CMeshPiler::Init(void)
{
	// �f�o�C�X�̃|�C���^
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_��,�C���f�b�N�X��,�|���S�������v�Z����
	m_nNumAllVtx = (PILERINFO::NUMX + 1) * (PILERINFO::NUMZ + 1);
	m_nNumPrimitive = ((PILERINFO::NUMX * PILERINFO::NUMZ) * 2) + (4 * (PILERINFO::NUMZ - 1));
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
	VERTEX_3D* pVtx = nullptr;

	//���_�o�b�t�@�����b�N
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W
	float fTexX = 1.0f / PILERINFO::NUMX;
	float fTexY = 1.0f / PILERINFO::NUMZ;
	int nCnt = 0;

	// �@���ݒ�p
	D3DXVECTOR3 nor = VECTOR3_NULL;

	// �c
	for (int nCntZ = 0; nCntZ <= PILERINFO::NUMZ; nCntZ++)
	{
		// ��
		for (int nCntX = 0; nCntX <= PILERINFO::NUMX; nCntX++)
		{
			// �p�x�v�Z
			float fAngle = (D3DX_PI * 2.0f) / PILERINFO::NUMX * nCntX;

			// ���_���W�̐ݒ�
			pVtx[nCnt].pos = D3DXVECTOR3(sinf((fAngle)) * PILERINFO::COLLISIONRADIUS, nCntZ * PILERINFO::VALUEHEIGHT, cosf((fAngle)) * PILERINFO::COLLISIONRADIUS);

			// �@���x�N�g���̐ݒ�
			nor = pVtx[nCnt].pos - m_pos;	// �e���_���猴�_�̒l������
			D3DXVec3Normalize(&pVtx[nCnt].nor, &nor);	// �@���̐��K��

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

	// ���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// �C���f�b�N�X�|�C���^��錾
	WORD* pIdx;

	// �C���f�b�N�X�o�b�t�@�̃��b�N
	m_pIdx->Lock(0, 0, (void**)&pIdx, 0);

	WORD IndxNum = PILERINFO::NUMX + 1;// X

	WORD IdxCnt = 0;// �z��

	WORD Num = 0;

	// �C���f�b�N�X�̐ݒ�
	for (int IndxCount1 = 0; IndxCount1 < PILERINFO::NUMZ; IndxCount1++)
	{
		for (int IndxCount2 = 0; IndxCount2 <= PILERINFO::NUMX; IndxCount2++, IndxNum++, Num++)
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

	// �I�u�W�F�N�g�̎�ސݒ�
	SetObjType(TYPE_PILER);

	// �����o�ϐ��̏�����
	m_nLife = 60;
	m_nActiveDelay = 3;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CMeshPiler::Uninit(void)
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
//===============================
// �X�V����
//===============================
void CMeshPiler::Update(void)
{
	// �o�ߎ��Ԃ��J�E���g
	m_nLifeFrame++;

	// ���Z
	m_nLife--;

	// �p�x��]
	 m_rot.y += 0.45f;

	 // ���K���֐�
	 m_rot.y = NormalAngle(m_rot.y);

	// �����𑝉�������
	m_fNowHeight += PILERINFO::MOVESPEED;

	// �ő�l�Ŏ~�߂�
	if (m_fNowHeight > PILERINFO::VALUEHEIGHT)
		m_fNowHeight = PILERINFO::VALUEHEIGHT;

	// ������0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		// �I������
		Uninit();

		// �����I��
		return;
	}

	// ���_�����X�V
	VERTEX_3D* pVtx = nullptr;

	// ���b�N�ɐ���������
	if (SUCCEEDED(m_pVtx->Lock(0, 0, (void**)&pVtx, 0)))
	{
		int nCnt = 0;

		for (int nCntZ = 0; nCntZ <= PILERINFO::NUMZ; nCntZ++)
		{
			for (int nCntX = 0; nCntX <= PILERINFO::NUMX; nCntX++)
			{
				float fAngle = (D3DX_PI * 2.0f) / PILERINFO::NUMX * nCntX;

				// ������m_fNowHeight�ɒu��
				float fHeight = (float)nCntZ * m_fNowHeight;

				pVtx[nCnt].pos = D3DXVECTOR3(
					sinf(fAngle) * PILERINFO::COLLISIONRADIUS,
					fHeight,
					cosf(fAngle) * PILERINFO::COLLISIONRADIUS
				);

				nCnt++;
			}
		}

		// �A�����b�N
		m_pVtx->Unlock();
	}
}
//===============================
// �`�揈��
//===============================
void CMeshPiler::Draw(void)
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
}

//===============================
// �����蔻�菈�� ( �����x�[�X )
//===============================
bool CMeshPiler::Collision(D3DXVECTOR3* CollisionPos)
{
	// �܂��L�������ԂɒB���Ă��Ȃ��ꍇ�͔��肵�Ȃ�
	if (m_nLifeFrame < m_nActiveDelay)
	{
		return false;
	}

	// ���ݍ��W�̎擾
	D3DXVECTOR3 NowPos = GetPos();

	// XZ���ʂł̋��������߂�
	D3DXVECTOR2 diffXZ = D3DXVECTOR2(CollisionPos->x - NowPos.x,
		CollisionPos->z - NowPos.z);

	float fRangeXZ = D3DXVec2Length(&diffXZ);

	// �����͈͂��`�F�b�N
	float fMinY = NowPos.y;
	float fMaxY = NowPos.y + PILERINFO::VALUEHEIGHT;	// ���݂̍����܂�

	if (fRangeXZ < PILERINFO::COLLISIONRADIUS &&
		CollisionPos->y >= fMinY && CollisionPos->y <= fMaxY)
	{
		// �I������
		Uninit();

		// �������������Ԃ�
		return true;
	}

	return false;
}
//===============================
// �e�N�X�`�����蓖�ď���
//===============================
void CMeshPiler::SetTexture(void)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();
	// null�`�F�b�N
	if (pTexture == nullptr) return;

	// �e�N�X�`�����蓖��
	m_nTexIdx = pTexture->Register("data\\TEXTURE\\MeshPiler1.jpg");
}