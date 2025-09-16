//======================================
//
// �ҏW�p���f������ [ edimodel.cpp ]
// Author: Asuma Nishio
//
//======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "editmodel.h"
#include "manager.h"
#include "modellist.h"
#include "editmanager.h"

//=============================
// �R���X�g���N�^
//=============================
CEditModel::CEditModel(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdxObj = NULL;
}
//=============================
// �f�X�g���N�^
//=============================
CEditModel::~CEditModel()
{
	// ����
}
//=============================
// ����
//=============================
CEditModel* CEditModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �C���X�^���X����	
	CEditModel* pEdit = new CEditModel;

	// null�Ȃ�
	if (pEdit == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pEdit->Init()))
	{
		return nullptr;
	}

	// ���������|�C���^��Ԃ�
	return pEdit;
}
//=============================
// ����������
//=============================
HRESULT CEditModel::Init(void)
{
	// �����o�ϐ��̏�����
	m_nIdxObj = 0;

	// ����������
	return S_OK;
}
//=============================
// �I������
//=============================
void CEditModel::Uninit(void)
{
	// ���g�̔j��
	CObject::Release();
}
//=============================
// �X�V����
//=============================
void CEditModel::Update(void)
{

}
//=============================
// �`�揈��
//=============================
void CEditModel::Draw(void)
{
#if 0
	// ���X�g�擾
	CModelList* pModelList = CEditManager::GetList();

	// �z�u�������f���̃C���f�b�N�X���擾
	int nIdx = m_nIdxObj;

	// �͈̓`�F�b�N
	auto modelInfoVec = pModelList->GetInfo();

	if (nIdx < 0 || nIdx >= (int)modelInfoVec.size()) return;

	// ���f�������擾
	CModelList::MODELINFO& info = modelInfoVec[nIdx];

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
	pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)info.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// �}�e���A���ݒ�
		pDevice->SetMaterial(&Col.MatD3D);

		// ���f��(�p�[�c)�̕`��
		info.pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);
#endif
}
