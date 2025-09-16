//================================================
//
// �}�b�v�ɏo���I�u�W�F�N�g���� [ mapobject.cpp ]
// Author: Asuma Nishio
//
//================================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "mapobject.h"
#include "manager.h"
#include "modellist.h"
#include "editmanager.h"

//=========================
// �R���X�g���N�^
//=========================
CMapObject::CMapObject(int nPriority) : CObject(nPriority)
{
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdx = NULL;
}
//=========================
// �f�X�g���N�^
//=========================
CMapObject::~CMapObject()
{
	// ����
}
//=========================
// ����
//=========================
CMapObject* CMapObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx)
{
	// �C���X�^���X����
	CMapObject* pMapObject = new CMapObject;

	// null�Ȃ�
	if (pMapObject == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pMapObject->Init()))
	{
		return nullptr;
	}

	// �Z�b�g
	pMapObject->m_pos = pos;
	pMapObject->m_rot = rot;
	pMapObject->m_nIdx = nIdx;

	// �������ꂽ�|�C���^��Ԃ�
	return pMapObject;
}
//=========================
// ������
//=========================
HRESULT CMapObject::Init(void)
{
	// �l�̏�����
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdx = -1;

	return S_OK;
}
//=========================
// �I��
//=========================
void CMapObject::Uninit(void)
{
	// ���g�̔j��
	CObject::Release();
}
//=========================
// �X�V
//=========================
void CMapObject::Update(void)
{
	// ����
}
//=========================
// �`��
//=========================
void CMapObject::Draw(void)
{
#if 1
	if (m_nIdx == -1) return;

	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���X�g�擾
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nIdx);

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���݂̃}�g���b�N�X�̎擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// �}�e���A���ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		// ���f��(�p�[�c)�̕`��
		Info.pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
#endif
}