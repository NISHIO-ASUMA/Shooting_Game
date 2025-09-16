//=============================================
//
// �^�C�g���v���C���[���� [ titleplayer.cpp ]
// Author: Asuma Nishio
//
//=============================================

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "titleplayer.h"
#include "manager.h"
#include "input.h"

//============================
// �R���X�g���N�^
//============================
CTitlePlayer::CTitlePlayer(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_rotDest = VECTOR3_NULL;
	m_nIdxPlayer = NULL;

	// ���f���̃|�C���^�̃N���A
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// �N���X�|�C���^
	m_pMotion = nullptr;
	m_pFilename = {};
}
//============================
// �f�X�g���N�^
//============================
CTitlePlayer::~CTitlePlayer()
{
	// ����
}
//============================
// ��������
//============================
CTitlePlayer* CTitlePlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nIdxParson, const char* pFilename)
{
	// �C���X�^���X����
	CTitlePlayer* pTitlePlayer = new CTitlePlayer;

	// nullptr��������
	if (pTitlePlayer == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pTitlePlayer->m_pos = pos;
	pTitlePlayer->m_rot = rot;
	pTitlePlayer->m_nIdxPlayer = nIdxParson;
	pTitlePlayer->m_pFilename = pFilename;

	// ���������s��
	if (FAILED(pTitlePlayer->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pTitlePlayer;
}
//============================
// �w��ԍ��̃v���C���[�擾
//============================
CTitlePlayer* CTitlePlayer::GetIdxPlayer(int Idx)
{
	// �I�u�W�F�N�g�̐擪�擾
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::CHARACTOR));

	// pObj��nullptr����Ȃ�������
	while (pObj != nullptr)
	{
		// �I�u�W�F�N�g�̃^�C�v��PLAYER�̎�
		if (pObj->GetObjType() == CObject::TYPE_PLAYER)
		{
			// �v���C���[�^�ɃL���X�g
			CTitlePlayer* pPlayer = static_cast<CTitlePlayer*>(pObj);

			// �ԍ�����v���Ă�����
			if (pPlayer->GetPlayerIndex() == Idx)
			{
				// �|�C���^��Ԃ�
				return pPlayer;
			}
		}

		// ���̃v���C���[����
		pObj = pObj->GetNext();
	}

	// �擾�ł��Ȃ������ꍇ
	return nullptr;
}
//============================
// ����������
//============================
HRESULT CTitlePlayer::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_PLAYER);

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load(m_pFilename, TITLE_MODEL, m_apModel, TITLEMOTION_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(TITLEMOTION_MAX);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CTitlePlayer::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_apModel[nCnt] != nullptr)
		{
			// �I������
			m_apModel[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_apModel[nCnt];

			// nullptr�ɂ���
			m_apModel[nCnt] = nullptr;
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
//============================
// �X�V����
//============================
void CTitlePlayer::Update(void)
{
	// ���̓f�o�C�X���擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �L�[���� ���� ��]�I���� ���[�V�����ύX
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) 
		&& CManager::GetCamera()->GetKeyFlag())
	{
		// �A�N�V������ԂɕύX
		m_pMotion->SetMotion(TITLEMOTION_ACTION);
	}

	// ���[�V�����̍X�V
	if (m_pMotion != nullptr)
	{
		m_pMotion->Update(m_apModel,TITLE_MODEL);
	}
}
//============================
// �`�揈��
//============================
void CTitlePlayer::Draw(void)
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
	for (int nCnt = 0; nCnt < TITLE_MODEL; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}
}
