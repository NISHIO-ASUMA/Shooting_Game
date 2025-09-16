//====================================
//
// ���f������ [ model.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "model.h"
#include "manager.h"
#include "texture.h"

//=================================
// �R���X�g���N�^
//=================================
CModel::CModel()
{
	// �l�̃N���A
	m_dwNumMat = NULL;
	m_pBuffMat = nullptr;
	m_pMesh = nullptr;
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pTexture = nullptr;
	m_offPos = VECTOR3_NULL;
	m_offRot = VECTOR3_NULL;
	m_parttype = PARTTYPE_NONE;
	m_isPlayer  = false;
	m_isBoss = false;
}
//=================================
// �f�X�g���N�^
//=================================
CModel::~CModel()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * pFilename)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	// �ʒu�̐ݒ�
	m_pos = pos;
	m_rot = rot;

	// �I�t�Z�b�g����
	m_offPos = pos;
	m_offRot = rot;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �e�N�X�`���C���f�b�N�X�z��̓��I�m��
	m_pTexture = new int[m_dwNumMat];

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �e�N�X�`�����ǂݍ��߂���
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���|�C���^�擾
			CTexture* pTexture = CManager::GetTexture();

			// �e�N�X�`���Z�b�g
			m_pTexture[nCntMat] = pTexture->Register(pMat[nCntMat].pTextureFilename);
		}
		else
		{
			m_pTexture[nCntMat] = -1; // �e�N�X�`���Ȃ�
		}
	}

	// ���ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CModel::Uninit(void)
{
	// ���b�V���̔j��
	if (m_pMesh != nullptr)
	{
		m_pMesh->Release();
		m_pMesh = nullptr;
	}

	// �}�e���A���̔j��
	if (m_pBuffMat != nullptr)
	{
		m_pBuffMat->Release();
		m_pBuffMat = nullptr;
	}

	// �e�N�X�`���|�C���^�̔j��
	if (m_pTexture != nullptr)
	{
		delete[] m_pTexture;

		m_pTexture = nullptr;
	}
}
//=================================
// �X�V����
//=================================
void CModel::Update(void)
{
	// ����
}
//=================================
// �`�揈��
//=================================
void CModel::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y + m_offRot.y, m_rot.x + m_offRot.x, m_rot.z + m_offRot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x + m_offPos.x, m_pos.y + m_offPos.y, m_pos.z + m_offPos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// �e�̃y�A�l���g�i�[�p�ϐ�
	D3DXMATRIX mtxParent;

	if (m_pParent != nullptr)
	{// �e�����݂���
		// ���[���h�}�g���b�N�X�擾
		mtxParent = m_pParent->GetMtxWorld();
	}
	else
	{// �e�����݂��Ȃ�
		// �}�g���b�N�X�擾
		pDevice->GetTransform(D3DTS_WORLD, &mtxParent);
	}

	// �e�̃}�g���b�N�X�Ƃ������킹��
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxParent);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���݂̃}�g���b�N�X�̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
	{
		// �}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// �C���f�b�N�X�ɉ����ĕύX����
		if (m_pTexture[nCntMat] != -1)
		{
			// �e�N�X�`���擾
			CTexture* pTexture = CManager::GetTexture();

			// �e�N�X�`���Z�b�g
			pDevice->SetTexture(0, pTexture->GetAddress(m_pTexture[nCntMat]));
		}
		else
		{
			// �e�N�X�`���Ȃ�
			pDevice->SetTexture(0, NULL); 
		}

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}
//=================================
// ��������
//=================================
CModel* CModel::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CModel* pModel = new CModel;

	// null��������
	if (pModel == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pModel->Init(pos, rot,pFilename)))
	{
		// nullptr�Z�b�g
		return  nullptr;
	}

	// �|�C���^��Ԃ�
	return pModel;
}
//=================================
// �e�p�[�c�ݒ菈��
//=================================
void CModel::SetParent(CModel* pModel)
{
	// �ݒ�
	m_pParent = pModel;
}
