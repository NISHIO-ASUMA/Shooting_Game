//=========================================
//
// �v���C���[���� [ player.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "player.h"
#include "manager.h"
#include "texture.h"
#include "boss.h"
#include "particle.h"
#include "shadow.h"
#include "meshimpact.h"
#include "input.h"
#include "camera.h"
#include "state.h"
#include "parameter.h"
#include "debugproc.h"
#include "shadowS.h"
#include "gamemanager.h"
#include "playerstate.h"
#include "state.h"
#include "item.h"
#include "barriermanager.h"
#include "rubble.h"
#include "charge.h"
#include "meshpiler.h"
#include "effect.h"
#include "exitpoint.h"
#include "game.h"
#include "effectsmoke.h"

//**********************
// ���O���
//**********************
namespace PLAYERINFO
{
	constexpr float MOVE = 0.012f;		 // 1�t���[���̈ړ���
	constexpr float JUMPVALUE = 18.3f;	 // �W�����v��
	constexpr float GRAVITY = 1.5f;		 // �d�͒l
	constexpr float HITRADIUS = 25.0f;	 // �����蔻��̔��a
	constexpr int   NUMBER_MAIN = 0;	 // ���C������v���C���[�ԍ�
	constexpr int   NUMBER_SUB = 1;		 // ���g����v���C���[�ԍ�
	constexpr int   KeyRepeatCount = 15; // �L�[�̃��s�[�g�ő�J�E���g
};

//**********************
// �ÓI�����o�ϐ��錾
//**********************
bool CPlayer::m_isDeath = false;  // ���S�t���O

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_Scal = VECTOR3_NULL;
	m_State = NULL;
	m_nIdxTexture = NULL;
	m_rotDest = VECTOR3_NULL;
	m_nNumAll = NULL;
	m_type = NULL;
	m_posOld = VECTOR3_NULL;
	m_pFilename = {};
	m_nIdxPlayer = NULL;
	m_fAngle = NULL;

	// ���f���̃|�C���^�̃N���A
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		m_apModel[nCnt] = nullptr;
	}

	// �N���X�|�C���^
	m_pMotion = nullptr;
	m_pShadow = nullptr;
	m_pParameter = nullptr;
	m_pShadowS = nullptr;
	m_pStateMachine = nullptr;

	// �t���O�����g
	m_isLanding = false;
	m_isJump = false;
	m_isAttack = false;
	m_isMoving = false;
	m_isShadow = false;
	m_isStateSynchro = false;
	m_isConectPad = false;
	m_isGuard = false;
	m_isDecHp = false;
}
//===============================
// �f�X�g���N�^
//===============================
CPlayer::~CPlayer()
{
	// ����
}
//===============================
// �v���C���[��������
//===============================
CPlayer* CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nLife,const int nIdxParson, const char* pFilename)
{
	// �v���C���[�̃C���X�^���X����
	CPlayer* pPlayer = new CPlayer;

	// �C���X�^���X��nullptr��������
	if (pPlayer == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pPlayer->m_pos = pos;
	pPlayer->m_rot = rot;
	pPlayer->m_nIdxPlayer = nIdxParson;
	pPlayer->m_pFilename = pFilename;

	// �̗͂�2�̂ŋ���
	if (nIdxParson == PLAYERINFO::NUMBER_MAIN)
	{
		// �|�C���^����
		pPlayer->m_pParameter = new CParameter;

		// null�`�F�b�N
		if (pPlayer->m_pParameter != nullptr)
		{
			// �̗̓p�����[�^�[��ݒ�
			pPlayer->m_pParameter->SetHp(nLife);
			pPlayer->m_pParameter->SetMaxHp(nLife);
		}
	}
	else
	{
		// ���C�����̏����Z�b�g
		CPlayer* pMain = CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN);

		// nullptr�`�F�b�N
		if (pMain != nullptr)
		{
			// �|�C���^�����L
			pPlayer->m_pParameter = pMain->m_pParameter; 
		}
	}

	// �v���C���[����������
	if (FAILED(pPlayer->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �v���C���[�̃|�C���^��Ԃ�
	return pPlayer;
}
//===============================
// �v���C���[����������
//===============================
HRESULT CPlayer::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_PLAYER);

	// �e�̎��
	CBullet::SetType(CBullet::BTYPE_PLAYER);

	// ���f����������
	m_nNumAll = MAX_MODEL;

	// ���[�V������ސ�����
	m_type = PLAYERMOTION_MAX;

	// �p�x������
	m_fAngle = NULL;

	// �X�P�[���T�C�Y��ݒ�
	m_Scal = D3DXVECTOR3(0.75f, 0.75f, 0.75f);

	// �t���O��ݒ�
	m_isDeath = false;
	m_isJump = false;
	m_isLanding = false;
	m_isMoving = false;

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load(m_pFilename, MAX_MODEL, m_apModel,PLAYERMOTION_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(PLAYERMOTION_MAX);

	// �v���C���[���ʃ��f���t���O��ݒ�
	for (int nCnt = 0; nCnt < MAX_MODEL; nCnt++)
	{
		// nullptr����Ȃ�������
		if (m_apModel[nCnt] != nullptr)
		{
			// �t���O��ݒ肷��
			m_apModel[nCnt]->SetIsPlayer(true);
		}
	}
	
	// ��l�ڂ̃v���C���[�Ȃ�
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		// �X�e���V���V���h�E����
		m_pShadowS = 
			CShadowS::Create(
			"data\\MODEL\\STAGEOBJ\\Shadowmodel.x",
			CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->GetPos(), 
			CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->GetRot()
			);
	}

	// �������W�̌�����ݒ�
	InitPos(NULL);

	// �X�e�[�g�}�V���𐶐�
	m_pStateMachine = new CStateMachine;	

	// ������Ԃ��Z�b�g
	ChangeState(new CPlayerStateNeutral,CPlayerStateBase::ID_NEUTRAL); 

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �v���C���[�I������
//===============================
void CPlayer::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
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

	// nullptr�`�F�b�N
	if (m_pParameter != nullptr && m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		// �|�C���^�̔j��
		delete m_pParameter;

		// nullptr�ɂ���
		m_pParameter = nullptr;
	}

	// nullptr�`�F�b�N
	if (m_pStateMachine != nullptr)
	{
		// �I������
		m_pStateMachine->OnExit();

		// �|�C���^�̔j��
		delete m_pStateMachine;

		// nullptr�ɂ���
		m_pStateMachine = nullptr;
	}

	// �I�u�W�F�N�g���g�̔j��
	CObject::Release();
}
//============================================================
// �v���C���[�X�V����
//============================================================
void CPlayer::Update(void)
{
	// ���݃V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	// �U�����̓{�X�̕����ɑ̂�������
	if (m_isAttack && nMode == CScene::MODE_GAME)
	{
		// �{�X�̕����փx�N�g����������
		D3DXVECTOR3 BossDir = CGameManager::GetBoss()->GetPos() - m_pos;
		BossDir.y = 0.0f;

		if (D3DXVec3LengthSq(&BossDir) > 0.0001f)
		{
			// ���K��
			D3DXVec3Normalize(&BossDir, &BossDir);

			// �p�x��K�p
			m_rot.y = atan2f(-BossDir.x, -BossDir.z);
		}
	}
	else if (m_isAttack && nMode == CScene::MODE_TUTORIAL)
	{
		// �����փx�N�g����������
		D3DXVECTOR3 DestPos = VECTOR3_NULL - m_pos;
		DestPos.y = 0.0f;

		if (D3DXVec3LengthSq(&DestPos) > 0.0001f)
		{
			// ���K��
			D3DXVec3Normalize(&DestPos, &DestPos);

			// �p�x��K�p
			m_rot.y = atan2f(-DestPos.x, -DestPos.z);
		}
	}

	// SUB�v���C���[��������
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB)
	{
		// MAIN�v���C���[�擾
		CPlayer* pMain = CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN);

		// �p�x����
		m_fAngle = pMain->m_fAngle;

		if (nMode == CScene::MODE_GAME)
		{
			// ���W����
			float fRadius = CGameManager::GetCylinder()->GetRadius();
			float IdxAngle = m_fAngle + D3DX_PI;
			D3DXVECTOR3 DestPos = CGameManager::GetCylinder()->GetPos();

			// ���W�ݒ�
			m_pos.x = DestPos.x - sinf(IdxAngle) * fRadius;
			m_pos.y = pMain->m_pos.y;
			m_pos.z = DestPos.z - cosf(IdxAngle) * fRadius;
		}
		else if (nMode == CScene::MODE_TUTORIAL)
		{
			// ���W����
			float fRadius = 550.0f;
			float IdxAngle = m_fAngle + D3DX_PI;
			D3DXVECTOR3 DestPos = VECTOR3_NULL;

			// ���W�ݒ�
			m_pos.x = DestPos.x - sinf(IdxAngle) * fRadius;
			m_pos.z = DestPos.z - cosf(IdxAngle) * fRadius;
		}

		// ���[�V�����𓝈ꂷ��
		m_pMotion->SetMotion(pMain->GetNowMotion());

		// MAIN�Ə�Ԃ���v�����瓯������
		if (m_pStateMachine->GetNowStateID() == pMain->m_pStateMachine->GetNowStateID())
		{
			m_isStateSynchro = true;
		}

		// ���[�V������v���Ă�����
		if (m_isStateSynchro)
		{
			// ���[�V�����𓝈ꂷ��
			m_pMotion->SetMotion(pMain->GetNowMotion());

			// �X�e�[�g���قȂ�ꍇ�̂ݕύX
			int mainStateID = pMain->m_pStateMachine->GetNowStateID();
			int subStateID = m_pStateMachine->GetNowStateID();

			if (mainStateID != subStateID)
			{
				switch (mainStateID)
				{
				case CPlayerStateBase::ID_NEUTRAL:	// �j���[�g����
					ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);
					break;

				case CPlayerStateBase::ID_MOVE:		// �ړ�
					ChangeState(new CPlayerStateMove(), CPlayerStateBase::ID_MOVE);
					break;

				case CPlayerStateBase::ID_ACTION:	// �U��
					ChangeState(new CPlayerStateAction(), CPlayerStateBase::ID_ACTION);
					break;

				case CPlayerStateBase::ID_DAMAGE:	// �_���[�W
					ChangeState(new CPlayerStateDamage(0), CPlayerStateBase::ID_DAMAGE);
					break;

				default:
					break;
				}
			}
		}
	}

	// nullptr����Ȃ��Ƃ�
	if (m_pStateMachine != nullptr)
	{
		// �X�e�[�g�X�V
		m_pStateMachine->Update();
	}

	// ���̓f�o�C�X�̃|�C���^�擾
	CInputKeyboard* pInput = nullptr;
	CJoyPad* pJoyPad = nullptr;

	pInput = CManager::GetInputKeyboard();
	pJoyPad = CManager::GetJoyPad();

	// ����̃��[���h�}�g���b�N�X�ƃ{�X�����擾
	CModel* pModelWeapon = GetModelPartType(CModel::PARTTYPE_WEAPON);
	if (!pModelWeapon) return;

	// �C�x���g���͓����蔻����Ƃ����Ȃ�
	if (CManager::GetCamera()->GetMode() != CManager::GetCamera()->MODE_EVENT)
	{
		// �����蔻�菈���֐�
		Collision();
	}

	// ���݂�y���W��0.0f�ȉ��̎�
	if (m_pos.y <= 0.0f)
	{
		// y���W��n�ʂ̍��W�ɐݒ�
		m_pos.y = 0.0f;

		// ���n�����L����
		m_isLanding = true;

		// �����ւ̈ړ��ʂ�0.0f�ɐݒ�
		m_move.y = 0.0f;
	}

	// �X�e���V���V���h�E������ ���� MAIN�v���C���[
	if (m_pShadowS && m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		// �e���W��MAIN�v���C���[���W�ɐݒ�
		D3DXVECTOR3 ShadowPos = GetIdxPlayer(0)->GetPos();

		// �I�u�W�F�N�g�ݒ�
		m_pShadowS->SetPos(ShadowPos);
		m_pShadowS->SetRot(GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->GetRot()); 
	}

	// �`���[�W����ɒB�����Ƃ� ���� �t���O���L���Ȃ�
	if ((pInput->GetTrigger(DIK_F) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT_B))&& CCharge::GetChargeFlag())
	{
		// �e�̎�ނ�؂�ւ��\�ɂ���
		CBullet::SetType(CBullet::BTYPE_LASER);
	}

	// ���[�V�����̑S�̍X�V
	m_pMotion->Update(m_apModel, MAX_MODEL); 
}
//===============================
// �v���C���[�`�揈��
//===============================
void CPlayer::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans,mtxScal;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScal, m_Scal.x, m_Scal.y, m_Scal.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxScal);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);


	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// �S���f���p�[�c�̕`��
	for (int nCnt = 0; nCnt < m_nNumAll; nCnt++)
	{
		m_apModel[nCnt]->Draw();
	}

	if (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		// ���
		CDebugproc::Print("�W�����v�̃t���O { m_isJump = %d } ", m_isJump);
		// �f�o�b�O�t�H���g�`��
		CDebugproc::Draw(0, 160);
	}

	// ���ʕ`��
	CDebugproc::Print("MAIN�v���C���[�̍��W { %.2f,%.2f,%.2f }", CPlayer::GetIdxPlayer(0)->GetPos().x, CPlayer::GetIdxPlayer(0)->GetPos().y, CPlayer::GetIdxPlayer(0)->GetPos().z);
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 200);

	// ���ʕ`��
	CDebugproc::Print("SUB�v���C���[�̍��W { %.2f,%.2f,%.2f }", CPlayer::GetIdxPlayer(1)->GetPos().x, CPlayer::GetIdxPlayer(1)->GetPos().y, CPlayer::GetIdxPlayer(1)->GetPos().z);
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 220);

	// �̗͕`��
	CDebugproc::Print("�v���C���[�̗̑� { %d } ", m_pParameter->GetHp());
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 340);

	// ���[�V�����`��
	CDebugproc::Print("MAIN�v���C���[�̃��[�V���� { %d } ", CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->GetNowMotion());
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 600);

	// ���[�V�����`��
	CDebugproc::Print("SUB�v���C���[�̃��[�V���� { %d } ", CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_SUB)->GetNowMotion());
	// �f�o�b�O�t�H���g�`��
	CDebugproc::Draw(0, 620);

	CDebugproc::Print("MAIN�p�x { %.2f }", CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->m_fAngle);
	CDebugproc::Draw(0, 660);
	CDebugproc::Print("SUB �p�x { %.2f }", CPlayer::GetIdxPlayer(PLAYERINFO::NUMBER_SUB)->m_fAngle);
	CDebugproc::Draw(0, 680);

	CDebugproc::Print("�v���C���[�̏�� { %d }", GetIdxPlayer(PLAYERINFO::NUMBER_MAIN)->GetStateMachine()->GetNowStateID());
	CDebugproc::Draw(1100, 500);
}

//=========================================
// ���ʔԍ����Ƃ̃v���C���[�̎擾
//=========================================
CPlayer* CPlayer::GetIdxPlayer(int Idx)
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
			CPlayer* pPlayer = static_cast<CPlayer*>(pObj);

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

//=========================================
// ���f���̓��蕔���p�[�c�̎擾�֐�
//=========================================
CModel* CPlayer::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// �v���C���[�������Ă��郂�f���̐��̒�����T��
	for (int nModel = 0; nModel < MAX_MODEL; nModel++)
	{
		// ���f�������� ���� �擾���������ƈ�v���Ă�����
		if (m_apModel[nModel] && m_apModel[nModel]->GetPartType() == modelpart)
		{
			// �Y�����f����idx�ԍ��̃��f����Ԃ�
			return m_apModel[nModel];
		}
	}

	// �Y���Ȃ�
	return nullptr;
}

//=========================================
// �X�e�[�g�ύX
//=========================================
void CPlayer::ChangeState(CPlayerStateBase* pNewState,int id)
{
	// �������g����
	pNewState->SetOwner(this);

	// �X�e�[�g�ύX
	m_pStateMachine->ChangeState(pNewState);

	// �������ꎞ����
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB)
		m_isStateSynchro = false;
}

//=========================================
// ���ʔԍ����Ƃ̍U���X�V����
//=========================================
void CPlayer::UpdateAction(CInputKeyboard* pInputKeyboard,D3DXMATRIX pMtx,const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{
	// SUB�v���C���[���X�e�[�g�������Ȃ珈�����Ȃ�
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB && !m_isStateSynchro) return;

	// �L�[�t���O���Z�b�g
	bool isKeyPress = false;

	//====================
	// �U������
	//====================
	if ((pInputKeyboard->GetPress(DIK_RETURN) || pPad->GetPress(pPad->JOYKEY_X) && m_pMotion->GetMotionType() != CPlayer::PLAYERMOTION_JUMPATTACK))
	{
		// �L�[�t���O���Z�b�g
		isKeyPress = true;

		// 15�t���[���U���L�[����͂��Ă�����
		if ((pInputKeyboard->GetRepeat(DIK_RETURN, PLAYERINFO::KeyRepeatCount)) || ((pPad->GetRepeat(pPad->JOYKEY_X, PLAYERINFO::KeyRepeatCount))))
		{
			// �e�𐶐�
			CBullet::Create(D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43), DestMove, CBullet::GetType(), 5.0f, 5.0f, 40);
		}

		// �U����Ԃ���Ȃ��Ƃ�
		if (!m_isAttack)
		{
			// �U���t���O��L��������
			m_isAttack = true;

			// �n��U�����[�V�����ɕύX
			m_pMotion->SetMotion(CPlayer::PLAYERMOTION_ACTION);
		}
		else if (m_isAttack && !m_pMotion->GetFinishMotion()) // �U����� ���� ���[�V�����I�����肪false�̎�
		{
			// �U���t���O�𖳌�������
			m_isAttack = false;

			// �L�[���̓t���O�𖳌��ɂ���
			isKeyPress = false;

			// �j���[�g�����X�e�[�g�ɕύX
			ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

			// �����ŏ�����Ԃ�
			return; 
		}
	}
	else if (!isKeyPress && m_pMotion->GetMotionType() == CPlayer::PLAYERMOTION_ACTION)
	{// �L�[�t���O������ ���� ���݂̃��[�V�������U�����[�V�����Ȃ�

		// �U����Ԃ�����
		m_isAttack = false;

		// �j���[�g�������[�V�����ɕύX
		ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;

	}

	// �U����� ���� ���[�V�����̏�Ԃ��U������Ȃ�������
	if (m_isAttack &&m_pMotion->GetMotionType() != CPlayer::PLAYERMOTION_ACTION)
	{
		// �U����Ԃ�����
		m_isAttack = false;
	}
}
//=========================================
// ���ʔԍ����Ƃ̈ړ��X�V����
//=========================================
void CPlayer::UpdateMove(const D3DXVECTOR3 DestPos,CInputKeyboard* pInputKeyboard, CJoyPad* pPad)
{
	// SUB�v���C���[���X�e�[�g�������Ȃ珈�����Ȃ�
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB && !m_isStateSynchro) return;

	// �W�����v�U�����Ȃ�ړ��������֎~
	if (m_pMotion->GetMotionType() == PLAYERMOTION_JUMPATTACK)
	{
		return; // ���̎��͈ړ�������ύX�Ȃ�
	}

	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	// �L�[���͎��̊p�x�v�Z
	static float fAngle = NULL;

	// �~���̔��a���擾
	float fRadius = NULL;

	// �Q�[���V�[��
	if (nMode == CScene::MODE_GAME)
	{
		fRadius = CGameManager::GetCylinder()->GetRadius();
	}
	else
	{
		fRadius = 550.0f;
	}

	// ���ʔԍ��ŏ����𕪕ʂ���
	switch (m_nIdxPlayer)
	{
	case PLAYERINFO::NUMBER_MAIN: // ���C���v���C���[

		// �L�[���͎��̊p�x�v�Z
		if (pInputKeyboard->GetPress(DIK_A) || (pPad->GetPress(pPad->JOYKEY_LEFT)))
		{
			// �p�x�X�V
			m_fAngle += PLAYERINFO::MOVE;

			// �ړI�p���v�Z
			m_rotDest.y = m_fAngle - D3DX_PI * 0.5f; // �������ɐݒ�

			if (!m_isJump) 	m_pMotion->SetMotion(PLAYERMOTION_MOVE, false, 0,false); // �ړ����[�V�����ɕύX
		}
		else if (pInputKeyboard->GetPress(DIK_D) || (pPad->GetPress(pPad->JOYKEY_RIGHT)))
		{
			// �p�x�X�V
			m_fAngle -= PLAYERINFO::MOVE;

			// �ړI�p���v�Z
			m_rotDest.y = m_fAngle + D3DX_PI * 0.5f; // �E�����ɐݒ�

			if (!m_isJump) 	m_pMotion->SetMotion(PLAYERMOTION_MOVE, false, 0, false); // �ړ����[�V�����ɕύX
		}
		else
		{
			// �ړ����[�V������,�j���[�g�������[�V�����ɕύX
			if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE) m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, false, 0, false);
		}
		break;

	case PLAYERINFO::NUMBER_SUB: // �Ίp����̃v���C���[

		// �L�[���͎��̊p�x�v�Z
		if (pInputKeyboard->GetPress(DIK_A) || (pPad->GetPress(pPad->JOYKEY_LEFT))) // A�L�[
		{
			// �p�x�X�V
			m_fAngle += PLAYERINFO::MOVE;

			// �ړI�p���v�Z
			m_rotDest.y = m_fAngle - D3DX_PI * 0.5f; // �������ɐݒ�

			if (!m_isJump) 	m_pMotion->SetMotion(PLAYERMOTION_MOVE, false, 0, false); // �ړ����[�V�����ɕύX
		}
		else if (pInputKeyboard->GetPress(DIK_D) || (pPad->GetPress(pPad->JOYKEY_RIGHT))) // D�L�[
		{
			// �p�x�X�V
			m_fAngle -= PLAYERINFO::MOVE;

			// �ړI�p���v�Z
			m_rotDest.y = m_fAngle + D3DX_PI * 0.5f; // �E�����ɐݒ�

			if (!m_isJump) 	m_pMotion->SetMotion(PLAYERMOTION_MOVE, false, 0, false); // �ړ����[�V�����ɕύX
		}
		else
		{
			// �ړ����[�V������,�j���[�g�������[�V�����ɕύX
			if (m_pMotion->GetMotionType() == PLAYERMOTION_MOVE) m_pMotion->SetMotion(PLAYERMOTION_NEUTRAL, false, 0, false);
		}
		break;

	default:
		break;
	}

	// �p�x�𐳋K��
	if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y - m_rotDest.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// ���g�̊p�x���v�Z
	float IdxAngle = (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN) ? m_fAngle : m_fAngle + D3DX_PI;

	// �Ίp�����W�𒆐S����v�Z
	m_pos.x = DestPos.x - sinf(IdxAngle) * fRadius;
	m_pos.z = DestPos.z - cosf(IdxAngle) * fRadius;

	// ���݂̊p�x��ݒ肷��
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		m_rot.y += (m_rotDest.y - m_rot.y) + D3DX_PI;
	}
	else if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB)
	{
		m_rot.y += (m_rotDest.y - m_rot.y);
	}

	// ���ݍ��W���X�V
	m_posOld = m_pos;
}

//=========================================
// ���ʔԍ����Ƃ̃W�����v�X�V����
//=========================================
void CPlayer::UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad)
{
	 // SUB�v���C���[���X�e�[�g�������Ȃ珈�����Ȃ�
	 if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB && !m_isStateSynchro) return;

	 // ���[�V�����̃t���O
	 bool isJumpAttacking = (m_pMotion->GetMotionType() == PLAYERMOTION_JUMPATTACK);

	 // �V�[���擾
	 CScene::MODE nMode = CManager::GetScene();

	 // �W�����v���Ɉړ�����ꍇ
	 if (!isJumpAttacking && m_pMotion->GetMotionType() == PLAYERMOTION_JUMP)
	 {
		 D3DXVECTOR3 DestPos = VECTOR3_NULL;

		 if (nMode == CScene::MODE_GAME)
		 {
			 // ���b�V���V�����_�[�̎擾
			 DestPos = CGameManager::GetCylinder()->GetPos();
		 }
		 else
		 {
			 DestPos = VECTOR3_NULL;
		 }

		 // �ړ������Ăяo��
		 UpdateMove(DestPos, pInputKeyboard, pPad);
	 }

	// �W�����v�U�����ɋ󒆂ŐÎ~����
	if (isJumpAttacking && ((pInputKeyboard->GetPress(DIK_RETURN)) || (pPad->GetPress(pPad->JOYKEY_X))))
	{
		// ���̍����ŐÎ~����
		m_move.y = 0.0f;
	}
	else
	{
		// �d�͒l��K�p
		m_move.y -= 0.7f;
	}

	// �W�����v������
	if (m_isJump)
	{
		// �W�����v���ɍU���L�[����
		if ((pInputKeyboard->GetPress(DIK_RETURN)) || ((pPad->GetPress(pPad->JOYKEY_X))))
		{
			// �U���L�[��15�t���[�����������Ă�����
			if ((pInputKeyboard->GetRepeat(DIK_RETURN, PLAYERINFO::KeyRepeatCount)) || ((pPad->GetRepeat(pPad->JOYKEY_X, PLAYERINFO::KeyRepeatCount))))
			{
				// �e�𐶐�
				CBullet::Create(D3DXVECTOR3(pMtx._41, pMtx._42, pMtx._43), DestMove, CBullet::GetType(), 5.0f, 5.0f, 45);
			}

			// �W�����v�U�����[�V�����ɕύX
			m_pMotion->SetMotion(PLAYERMOTION_JUMPATTACK,false,0, false);

			// �Q�[���V�[��
			if (nMode == CScene::MODE_GAME)
			{
				// �������{�X�Ɍ�������
				D3DXVECTOR3 BossDir = CGameManager::GetBoss()->GetPos() - m_pos;
				BossDir.y = 0.0f;

				if (D3DXVec3LengthSq(&BossDir) > 0.0001f)
				{
					D3DXVec3Normalize(&BossDir, &BossDir);
					m_rot.y = atan2f(-BossDir.x, -BossDir.z);
				}
			}
			// �`���[�g���A���V�[��
			else if (nMode == CScene::MODE_TUTORIAL)
			{
				// ������ݒ�
				D3DXVECTOR3 VecCenter = VECTOR3_NULL - m_pos;
				VecCenter.y = 0.0f;

				if (D3DXVec3LengthSq(&VecCenter) > 0.0001f)
				{
					D3DXVec3Normalize(&VecCenter, &VecCenter);
					m_rot.y = atan2f(-VecCenter.x, -VecCenter.z);
				}
			}
		}
	}

	// �����X�V
	AddMove();

	// ���n���̏���
	if (m_isLanding)
	{
		// ���n���[�V�����ɕύX
		m_pMotion->SetMotion(PLAYERMOTION_LANDING);

		// �W�����v�\��ԂɕύX
		m_isJump = false;

		// �t���O�L����
		m_isLanding = true;
	}

	// ���[�V�����I�����@���� ��ނ����n���[�V����
	if (m_pMotion->GetMotionType() == PLAYERMOTION_LANDING && m_pMotion->GetFinishMotion())
	{
		if (m_isLanding == true)
		{
			// �j���[�g�����ɕύX
			ChangeState(new CPlayerStateNeutral(), CPlayerStateBase::ID_NEUTRAL);

			// �����ŏ�����Ԃ�
			return;
		}
	}

	// ���n���Ɉړ��L�[���͂����݂��Ă���Ȃ�
	if (m_pMotion->GetMotionType() == PLAYERMOTION_LANDING && (isMoveInputKey(pInputKeyboard) || isMovePadButton(pPad)))
	{
		// �ړ���ԂɕύX
		ChangeState(new CPlayerStateMove(), CPlayerStateBase::ID_MOVE);

		// �����ŏ�����Ԃ�
		return;
	}
}
//=============================
// �R���W���������֐�
//=============================
void CPlayer::Collision(void)
{
	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	if (nMode == CScene::MODE_TUTORIAL)
	{// �|�C���g����

		if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB) return;

		// �I�u�W�F�N�g�擾
		CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::SHADOW));

		// nullptr����Ȃ��Ƃ�
		while (pObj != nullptr)
		{
			// �^�C�v���擾
			if (pObj->GetObjType() == CObject::TYPE_POINT)
			{
				// �L���X�g
				CExitPoint* pExit = static_cast<CExitPoint*>(pObj);

				// �R���W����������
				if (pExit->Collision(&m_pos))
				{
					if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_START)))
					{
						// ��ʑJ��
						CFade* pFade = CManager::GetFade();
						if (pFade != nullptr)
						{
							pFade->SetFade(new CGame());

							return;
						}
					}
				}
			}

			// ���̃I�u�W�F�N�g�����o����
			pObj = pObj->GetNext();
		}
	}

	// �Q�[������Ȃ��Ȃ�
	if (nMode != CScene::MODE_GAME) return;

	// �_���[�W�����m�F
	if (GetStateMachine()->GetNowStateID() == CPlayerStateBase::ID_DAMAGE)
		return;

	//=============================
	// �{�X�E��̓����蔻��
	//=============================
	CBoss* pBoss = CGameManager::GetBoss();  // �}�l�[�W���[�o�R�Ń{�X���擾����

	// null��������
	if (pBoss->IsDaeth())
	{
		return;
	}

	// ��Ԗڂ̃v���C���[�ɔ���
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		// ���[�V�����^�C�v���擾
		int nMotion = pBoss->GetMotion()->GetMotionType();
		bool isHit = false;

		if (!pBoss->IsDaeth()) // �������̂ݔ���
		{
			switch (nMotion)
			{
			case CBoss::TYPE_ACTION:
				// �E��̂ݔ���
				isHit = pBoss->CollisionRightHand(&m_pos);
				break;

			case CBoss::TYPE_IMPACT:
				// �C���p�N�g����
				isHit = pBoss->CollisionImpactScal(&m_pos);
				break;

			case CBoss::TYPE_CIRCLE:
				// �T�[�N������
				isHit = pBoss->CollisionCircle(&m_pos, PLAYERINFO::HITRADIUS);
				break;

			case CBoss::TYPE_ARMRIGHTLEFT:
				// �U�艺�낵
				isHit = pBoss->CollisionSwing(&m_pos, PLAYERINFO::HITRADIUS);
				break;

			default:
				// �f�t�H���g����
				isHit = pBoss->CollisionRightHand(&m_pos);
				break;
			}

			if (isHit)
			{
				// �_���[�W�X�e�[�g�ɑJ��
				ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);
				return;
			}
		}
	}

	//=============================
	// �C���p�N�g�Ƃ̓����蔻��
	//=============================
	// �I�u�W�F�N�g�擾
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::IMPACT));

	// nullptr����Ȃ��Ƃ�
	while (pObj != nullptr)
	{
		// ���b�V���^�C�v���擾
		if (pObj->GetObjType() == CObject::TYPE_MESH)
		{
			// �C���p�N�g�ɃL���X�g
			CMeshImpact* pImpact = static_cast<CMeshImpact*>(pObj);

			// �R���W���������� ���� ID���_���[�W�ȊO
			if (pImpact->Collision(&m_pos))
			{
				// �X�e�[�g�ύX
				ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);

				// ��񓖂������甲����
				return;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObj = pObj->GetNext();
	}

	//==========================
	// �~���Ƃ̓����蔻��
	//==========================
	// �I�u�W�F�N�g�擾
	CObject* pObjPiler = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MESH));

	// nullptr����Ȃ��Ƃ�
	while (pObjPiler != nullptr)
	{
		// �~���N���X�̃I�u�W�F�N�g�^�C�v���擾
		if (pObjPiler->GetObjType() == CObject::TYPE_PILER)
		{
			// �~���N���X�ɃL���X�g
			CMeshPiler* pMesh = static_cast<CMeshPiler*>(pObjPiler);

			// 2�̖ڂȂ�
			if (m_nIdxPlayer != PLAYERINFO::NUMBER_MAIN) break;

			// �R���W���������Ƃ�
			if (pMesh->Collision(&m_pos) == true)
			{
				// �X�e�[�g�ύX
				ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);

				return;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObjPiler = pObjPiler->GetNext();
	}
	//=============================
	// �G�Ƃ̓����蔻��
	//=============================
	// �I�u�W�F�N�g�擾
	CObject* pObjEnemy = CObject::GetTop(static_cast<int>(CObject::PRIORITY::CHARACTOR));

	// nullptr����Ȃ��Ƃ�
	while (pObjEnemy != nullptr)
	{
		// �G�̃I�u�W�F�N�g�^�C�v���擾
		if (pObjEnemy->GetObjType() == CObject::TYPE_ENEMY)
		{
			// �G�ɃL���X�g
			CEnemy* pEnemy = static_cast<CEnemy*>(pObjEnemy);

			if (m_nIdxPlayer != PLAYERINFO::NUMBER_MAIN) break;

			// �R���W���������Ƃ�
			if (pEnemy->Collision(&m_pos) == true)
			{
				// �o���A�}�l�[�W���[���擾
				CBarrierManager* pBarrier = CGameManager::GetBarrier();

				// null����Ȃ� ���� �ϋv�l������Ȃ�
				if (pBarrier && pBarrier->GetNumBarrier() > 0)
				{
					// �o���A�Ŗh��
					pBarrier->DamageBarrier(1);
				}
				else
				{
					// �X�e�[�g�ύX
					ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);
				}

				// ��񓖂������甲����
				break;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObjEnemy = pObjEnemy->GetNext();
	}

	//==========================
	// �A�C�e���Ƃ̓����蔻��
	//==========================
	// �I�u�W�F�N�g�擾
	CObject* pObjItem = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	// nullptr����Ȃ��Ƃ�
	while (pObjItem != nullptr)
	{
		// �A�C�e���̃I�u�W�F�N�g�^�C�v���擾
		if (pObjItem->GetObjType() == CObject::TYPE_ITEM)
		{
			// �A�C�e���ɃL���X�g
			CItem* pItem = static_cast<CItem*>(pObjItem);

			// 2�̖ڂȂ�
			if (m_nIdxPlayer != PLAYERINFO::NUMBER_MAIN) break;

			// �R���W���������Ƃ�
			if (pItem->Collision(&m_pos) == true)
			{
				// ��񓖂������甲����
				break;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObjItem = pObjItem->GetNext();
	}


	//==========================
	// ���I�Ƃ̓����蔻��
	//==========================
	// �I�u�W�F�N�g�擾
	CObject* pObjRubble = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	// nullptr����Ȃ��Ƃ�
	while (pObjRubble != nullptr)
	{
		// ���I�̃I�u�W�F�N�g�^�C�v���擾
		if (pObjRubble->GetObjType() == CObject::TYPE_RUBBLE)
		{
			// �L���X�g
			CRubble* pRubble = static_cast<CRubble*>(pObjRubble);

			// 2�̖ڂȂ�
			if (m_nIdxPlayer != PLAYERINFO::NUMBER_MAIN) break;

			// �R���W���������Ƃ�
			if (pRubble->Collision(&m_pos) == true)
			{
				// �X�e�[�g�ύX
				ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);

				// ��񓖂������甲����
				break;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObjRubble = pObjRubble->GetNext();
	}
}
//===============================
// �p�b�h�̍��X�e�B�b�N���͊֐�
//===============================
void CPlayer::StickState(void)
{
	// �p�b�h�擾
	CJoyPad* pPad = CManager::GetJoyPad();

	// �X�e�B�b�N�ϐ�
	XINPUT_STATE* pStick;

	// �p�x�擾
	pStick = pPad->GetStickAngle();

	if (pPad->GetLeftStick() == true)
	{
		// L�X�e�B�b�N�̊p�x
		float LStickAngleY = pStick->Gamepad.sThumbLY;
		float LStickAngleX = pStick->Gamepad.sThumbLX;

		// �f�b�h�]�[��
		float deadzone = 10920;

		// �X�e�B�b�N�̌X�����p�x�����߂�
		float magnitude = sqrtf(LStickAngleX * LStickAngleX + LStickAngleY * LStickAngleY);

		// ��������
		if (magnitude > deadzone)
		{
			// �A���O���𐳋K��
			float normalizeX = (LStickAngleX / magnitude);
			float normalizeY = (LStickAngleY / magnitude);

			// �ڑ������L����
			m_isConectPad = true;
		}
	}
	else
	{
		m_isConectPad = false;
	}
}
//===============================
// �v���C���[�ƃ{�X�Ԃ̃x�N�g��
//===============================
D3DXVECTOR3 CPlayer::VecToBoss(const D3DXVECTOR3& pPos)
{
	// �{�X�̍��W�擾
	D3DXVECTOR3 BossPos = CGameManager::GetBoss()->GetPos();

	// �v���C���[�ƃ{�X�ԂŃx�N�g������
	D3DXVECTOR3 VecBoss = BossPos - pPos;
	VecBoss.y = 0.0f;

	// �ł����x�N�g���𐳋K������
	D3DXVec3Normalize(&VecBoss, &VecBoss);

	// �x�N�g����Ԃ�
	return VecBoss;
}
//===============================
// ���S���W�Ƃ̃x�N�g��
//===============================
D3DXVECTOR3 CPlayer::VecToCenter(const D3DXVECTOR3& pPos)
{
	// �{�X�̍��W�擾
	D3DXVECTOR3 CenterPos = VECTOR3_NULL;

	// �v���C���[�ƃ{�X�ԂŃx�N�g������
	D3DXVECTOR3 VecCenter = CenterPos - pPos;
	VecCenter.y = 0.0f;

	// �ł����x�N�g���𐳋K������
	D3DXVec3Normalize(&VecCenter, &VecCenter);

	// �x�N�g����Ԃ�
	return VecCenter;
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMoveInputKey(CInputKeyboard* pKeyInput)
{
	// �����ꂩ�̈ړ��L�[����
	return (pKeyInput->GetPress(DIK_A) || pKeyInput->GetPress(DIK_D));
}
//===============================
// �L�[�������̓��͎擾
//===============================
bool CPlayer::isMovePadButton(CJoyPad* pPad)
{
	// �����ꂩ�̈ړ��L�[����
	return (pPad->GetPress(CJoyPad::JOYKEY_LEFT) || pPad->GetPress(CJoyPad::JOYKEY_RIGHT));
}
//===============================
// �������W�v�Z�֐�
//===============================
void CPlayer::InitPos(float fAngle)
{
	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	// �~�����a���擾
	float fRadius = 0.0f;
	D3DXVECTOR3 DestPos = VECTOR3_NULL;

	// �Q�[���Ȃ�
	if (nMode == CScene::MODE_GAME)
	{
		fRadius = CGameManager::GetCylinder()->GetRadius();
		DestPos = CGameManager::GetCylinder()->GetPos();
	}
	else
	{
		fRadius = 550.0f;
		DestPos = VECTOR3_NULL;
	}

	// �p�x�̏����ݒ�
	m_fAngle = fAngle;

	// ���g�̊p�x���v�Z
	float IdxAngle = (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN) ? m_fAngle : m_fAngle + D3DX_PI;

	// �~����̏����ʒu���v�Z
	m_pos.x = DestPos.x - sinf(IdxAngle) * fRadius;
	m_pos.z = DestPos.z - cosf(IdxAngle) * fRadius;
	m_pos.y = 0.0f;

	// ���݂̊p�x��ݒ肷��
	if (m_nIdxPlayer == PLAYERINFO::NUMBER_MAIN)
	{
		m_rot.y += (m_rotDest.y - m_rot.y) + D3DX_PI;
	}
	else if (m_nIdxPlayer == PLAYERINFO::NUMBER_SUB)
	{
		m_rot.y += (m_rotDest.y - m_rot.y);
	}

	// ��]���Z�b�g
	m_rotDest.y = m_rot.y;

	// �O�t���[�����W���Z�b�g
	m_posOld = m_pos;
}
//===============================
// �W�����v����֐�
//===============================
void CPlayer::StartJump(void)
{
	// �W�����v�L�[���� ���� �W�����v�t���O��false�̎�
	if (!m_isJump)
	{
		// �t���O��L����
		m_isJump = true;

		// �����n����ɕύX
		m_isLanding = false;

		// �㏸�l��ݒ�
		m_move.y = PLAYERINFO::JUMPVALUE;

		// �ړ��X�V
		AddMove();
	}
}
//===============================
// ���݂̃��[�V������ގ擾
//===============================
CPlayer::PLAYERMOTION CPlayer::GetNowMotion() const
{
	// null����Ȃ�������
	if (m_pMotion)
	{
		// ���ݔԍ���Ԃ�
		return static_cast<CPlayer::PLAYERMOTION>(m_pMotion->GetMotionType());
	}

	return PLAYERMOTION_NEUTRAL; // �f�t�H���g
}
//===============================
// �q�b�g����
//===============================
void CPlayer::HitDamage(int nDamage)
{
	// �p�����[�^�[�擾
	int nHp = m_pParameter->GetHp();

	// �̗͂����炷
	nHp -= nDamage;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return;

	// �Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_DAMAGE);

	// ���ݑ̗͂�0�ȉ�
	if (nHp <= NULL)
	{
		// ���ݑ̗͂��Z�b�g
		m_pParameter->SetHp(nHp);

		// ���S�t���O���Z�b�g
		m_isDeath = true;

		// ���[�V�����Z�b�g
		m_pMotion->SetMotion(PLAYERMOTION_DAMAGE, false, 0, false);

		return;
	}
	else
	{
		// ���ݑ̗͂��Z�b�g
		m_pParameter->SetHp(nHp);
	}
}
//===============================
// �d�͏���
//===============================
void CPlayer::GravityScal(void)
{
	// �d�͒l��K�p
	m_move.y -= PLAYERINFO::GRAVITY;
}