//===========================================
//
// �`���[�g���A���{�X���� [ tutoboss.cpp ]
// Author: Asuma Nishio
//
//===========================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "tutorialboss.h"
#include "manager.h"

//=============================
// �R���X�g���N�^
//=============================
CTutorialBoss::CTutorialBoss(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_pMotion = nullptr;
	m_mtxworld = {};

	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}
}
//=============================
// �f�X�g���N�^
//=============================
CTutorialBoss::~CTutorialBoss()
{
	// ����
}
//=============================
// ��������
//=============================
CTutorialBoss* CTutorialBoss::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CTutorialBoss* pTutoBoss = new CTutorialBoss;
	if (pTutoBoss == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pTutoBoss->m_pos = pos;

	// ���������s��
	if (FAILED(pTutoBoss->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTutoBoss;
}
//=============================
// ����������
//=============================
HRESULT CTutorialBoss::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_BOSS);

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\BossTuto.txt", TUTO_MODEL, m_pModel, CTutorialBoss::TYPE_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(CTutorialBoss::TYPE_MAX);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=============================
// �I������
//=============================
void CTutorialBoss::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_pModel[nCnt] != nullptr)
		{
			// �I������
			m_pModel[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pModel[nCnt];

			// nullptr�ɂ���
			m_pModel[nCnt] = nullptr;
		}
	}

	// nullptr�`�F�b�N
	if (m_pMotion != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pMotion;

		// nullptr�ɂ���
		m_pMotion = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//=============================
// �X�V����
//=============================
void CTutorialBoss::Update(void)
{
	// null�`�F�b�N
	if (m_pMotion != nullptr) m_pMotion->Update(m_pModel, TUTO_MODEL);
}
//=============================
// �`�揈��
//=============================
void CTutorialBoss::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

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

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < TUTO_MODEL; nCnt++)
	{
		// �S���f���`��
		m_pModel[nCnt]->Draw();
	}
}
