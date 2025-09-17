//=====================================
//
// �{�X���� [ boss.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "boss.h"
#include "debugproc.h"
#include "manager.h"
#include "parameter.h"
#include "result.h"
#include "meshimpact.h"
#include "particle.h"
#include "bossstate.h"
#include "state.h"
#include "player.h"
#include "effect.h"
#include "sound.h"
#include <ctime>
#include "gamemanager.h"
#include "score.h"
#include "signal.h"
#include "handeffect.h"

//****************************
// ���O���
//****************************
namespace BOSSINFO
{
	constexpr float HITRANGE = 11.0f; // �R���W�����T�C�Y
	constexpr int COOLTIME = 60;	  // �����N�[���^�C��
	constexpr float CIRCLEHITRANGE = 200.0f;
}

//****************************
// �ÓI�����o�ϐ��錾
//****************************
bool CBoss::m_isdaeth = false;		// ���S�t���O

//====================================
// �I�[�o�[���[�h�R���X�g���N�^
//====================================
CBoss::CBoss(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_WeekPointPos = VECTOR3_NULL;

	m_pMotion = nullptr;
	m_pParam = nullptr;
	m_pState = nullptr;

	m_type = NULL;
	m_nCoolTime = NULL;
	m_fSize = NULL;

	m_mtxworld = {};

	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		m_pModel[nCnt] = nullptr;
	}

	m_isEvent = false;
	m_isSet = false;
	m_nCurrentMotion = TYPE_NEUTRAL;
}
//====================================
// �f�X�g���N�^
//====================================
CBoss::~CBoss()
{
	// ����
}
//====================================
// ��������
//====================================
CBoss* CBoss::Create(D3DXVECTOR3 pos,float fSize,int nLife)
{
	// �C���X�^���X����
	CBoss* pBoss = new CBoss;

	// �������s��
	if (pBoss == nullptr) return nullptr;

	// �I�u�W�F�N�g�Z�b�g
	pBoss->m_pos = pos;
	pBoss->m_fSize = fSize;

	// ���������s��
	if (FAILED(pBoss->Init()))
	{
		// null�|�C���^��Ԃ�
		return nullptr;
	}

	// �p�����[�^�[�|�C���^����
	pBoss->m_pParam = new CParameter;

	// �̗̓p�����[�^
	if (pBoss->m_pParam != nullptr)
	{
		pBoss->m_pParam->SetMaxHp(nLife);
		pBoss->m_pParam->SetHp(nLife);
	}

	// �|�C���^��Ԃ�
	return pBoss;
}
//=========================================
// ���f���̓��蕔���p�[�c�̎擾�֐�
//=========================================
CModel* CBoss::GetModelPartType(CModel::PARTTYPE modelpart)
{
	// �{�X�������Ă��郂�f���̐��̒�����T��
	for (int nModel = 0; nModel < NUMMODELS; nModel++)
	{
		// ���f�������� ���� �擾���������ƈ�v���Ă�����
		if (m_pModel[nModel] && m_pModel[nModel]->GetPartType() == modelpart)
		{
			// �Y�����f����idx�ԍ��̃��f����Ԃ�
			return m_pModel[nModel];
		}
	}

	// �Y���Ȃ��̏ꍇ
	return nullptr;
}
//====================================
// ����������
//====================================
HRESULT CBoss::Init(void)
{
	// �t���O��������
	m_isdaeth = false;

	// �I�u�W�F�N�g�̎�ނ��Z�b�g
	SetObjType(TYPE_BOSS);

	// �^�C�v���
	m_type = CBoss::TYPE_MAX;

	// �����N�[���^�C����ݒ�
	m_nCoolTime = BOSSINFO::COOLTIME;

	// ���[�V�����̓ǂݍ���
	m_pMotion = CMotion::Load("data\\MOTION\\Boss\\Bossmotion.txt", NUMMODELS, m_pModel, CBoss::TYPE_MAX);

	// ���[�V��������ݒ�
	m_pMotion->SetMotionNum(m_type);

	// �X�e�[�g����
	m_pState = new CStateMachine;

	// ������Ԃ��Z�b�g
	ChangeState(new CBossStateNeutral(120), CBossStateBace::ID_NEUTRAL);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//====================================
// �I������
//====================================
void CBoss::Uninit(void)
{
	// ���f�������̔j��
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
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

	// nullptr�`�F�b�N
	if (m_pParam != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pParam;

		// nullptr�ɂ���
		m_pParam = nullptr;
	}

	// nullptr�`�F�b�N
	if (m_pState != nullptr)
	{
		// �I������
		m_pState->OnExit();

		// �|�C���^�̔j��
		delete m_pState;

		// null������
		m_pState = nullptr;
	}

	// ���g�̔j��
	CObject::Release();
}
//====================================
// �X�V����
//====================================
void CBoss::Update(void)
{
	// ������-600.0f�ȉ�
	if (m_pos.y < -600.0f && !m_isSet)
	{
		// ��Ɉړ�
		m_pos.y += 1.0f;

		if (m_pos.y >= -600.0f)
		{
			// ���W�Z�b�g
			m_pos.y = -600.0f;

			// �t���O��L����
			m_isSet = true;
		}

		// ���[�V�����S�̍X�V
		m_pMotion->Update(m_pModel, NUMMODELS);

		return;
	}

	// ����ł�����
	if (m_isdaeth) return;

	// ���Z
	DecCoolTime();

	// null�`�F�b�N
	if (m_pState != nullptr)
	{
		// �X�e�[�g�X�V
		m_pState->Update();
	}

	//==========================
	// ��ڂ̎�_�p�[�c���擾
	//==========================
	CModel* pWeakHead = GetModelPartType(CModel::PARTTYPE_HEAD);

	// ��_�p�[�c�̃��[���h���W���擾
	D3DXMATRIX mtx = pWeakHead->GetMtxWorld();

	// ��_���W��ݒ�
	D3DXVECTOR3 weakPos(mtx._41, mtx._42 + 40.0f, mtx._43);

	// �G�t�F�N�g
	CEffect::Create(weakPos, COLOR_RED, VECTOR3_NULL, 50, 60.0f);

	// ���[�V�����S�̍X�V
	m_pMotion->Update(m_pModel, NUMMODELS);
}
//====================================
// �`�揈��
//====================================
void CBoss::Draw(void)
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
	for (int nCnt = 0; nCnt < NUMMODELS; nCnt++)
	{
		// �S���f���`��
		m_pModel[nCnt]->Draw();
	}

	// �f�o�b�O�\��
	CDebugproc::Print("�{�X���W [ %.2f ,%.2f , %.2f]", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 40);

	CDebugproc::Print("�{�X���[�V������ { %d }", m_type);
	CDebugproc::Draw(0, 180);

	CDebugproc::Print("�{�X�E����W { %.2f,%.2f,%.2f }", GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._41, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._42, GetModelPartType(CModel::PARTTYPE_RIGHT_HAND)->GetMtxWorld()._43);
	CDebugproc::Draw(0, 300);

	CDebugproc::Print("�{�X�̗� { %d }", m_pParam->GetHp());
	CDebugproc::Draw(0, 400);

	CDebugproc::Print("�{�X�N�[���^�C�� { %d }",m_nCoolTime);
	CDebugproc::Draw(1080, 400);

	// �f�o�b�O�t�H���g
	m_pMotion->Debug();
}
//====================================
// �E��ƃv���C���[�̓����蔻��
//====================================
bool CBoss::CollisionRightHand(D3DXVECTOR3* pPos)
{
	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if (m_pMotion->CheckFrame(25, 25, TYPE_ACTION) && !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CSignal::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	// ���t���[����
	if (m_pMotion->CheckFrame(100, 130, TYPE_ACTION) && m_isdaeth == false)
	{
		// ���f���̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

		// null��������
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// �����v�Z
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �v�Z���������̒����擾
		float fDist = D3DXVec3Length(&diff);

		// ������Ԃ�
		return fDist <= (BOSSINFO::HITRANGE * BOSSINFO::HITRANGE);
	}
	else
	{
		// ������Ȃ��Ƃ�
		return false;
	}
}
//====================================
// �C���p�N�g���[�V�������̓����蔻��
//====================================
bool CBoss::CollisionImpactScal(D3DXVECTOR3* pPos)
{
	// ���f���̃p�[�c�擾
	CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

	// null��������
	if (!pRightHand) return false;

	// ���f���̃p�[�c�擾
	CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND); // ����

	// null��������
	if (!pLeftHand) return false;

	// ��̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxRight = pRightHand->GetMtxWorld();
	D3DXMATRIX mtxLeft = pLeftHand->GetMtxWorld();

	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if (m_pMotion->CheckFrame(40, 40, TYPE_IMPACT) && !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CSignal::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	// ���W���i�[
	D3DXVECTOR3 posRight(mtxRight._41, mtxRight._42, mtxRight._43);
	D3DXVECTOR3 posLeft(mtxLeft._41, mtxLeft._42, mtxLeft._43);

	// ����̍��W�̒��S�_���v�Z
	D3DXVECTOR3 HandCenterPos = (posRight + posLeft) * 0.5f;

	// ���t���[����
	if (m_pMotion->CheckFrame(90, 120, TYPE_IMPACT) && !m_isdaeth)
	{
		// �v���C���[�Ƃ̋����𑪒�
		const float fHitRadius = 20.0f * BOSSINFO::HITRANGE; // ���蔼�a

		// �����v�Z�p
		D3DXVECTOR3 diff = VECTOR3_NULL;

		// �E��Ƃ̍���
		diff = posRight - *pPos;

		// ���a�ɓ����Ă���Ƃ�
		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			// ���b�V���Ռ��g�𐶐�	
			CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 100, 120.0f, 5.0f, 15.0f);
			return true;

		}

		// ����Ƃ̍���
		diff = posLeft - *pPos;

		// ���a�ɓ����Ă���Ƃ�
		if (D3DXVec3Length(&diff) <= fHitRadius)
		{
			// ���b�V���Ռ��g�𐶐�	
			CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 100, 120.0f, 5.0f, 15.0f);
			return true;
		}
	}

	// ���t���[����
	if (m_pMotion->CheckFrame(100, 100, TYPE_IMPACT) && !m_isdaeth)
	{
		// ���b�V���Ռ��g�𐶐�	
		CMeshImpact::Create(D3DXVECTOR3(HandCenterPos.x, 5.0f, HandCenterPos.z), 80, 120.0f, 5.0f, 15.0f);
	}

	// ������Ȃ��Ƃ�
	return false;
}
//=========================================
// �ガ�������̓����蔻��
//=========================================
bool CBoss::CollisionCircle(D3DXVECTOR3* pPos,float fHitRadius)
{
	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if (m_pMotion->CheckFrame(85, 85, TYPE_CIRCLE) && !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CSignal::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	// ���t���[���O
	if (m_pMotion->CheckFrame(305, 320, TYPE_CIRCLE) && m_isdaeth == false)
	{
		return false;
	}

	//  ���t���[����
	if ((m_pMotion->CheckFrame(110, 240, TYPE_CIRCLE)) && m_isdaeth == false)
	{
		// �E��̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// ���W�ɐݒ�
		D3DXVECTOR3 handPos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �G�t�F�N�g����
		CHandEffect::Create(handPos, D3DXCOLOR(1.0f,1.0f,1.0f,0.5f), VECTOR3_NULL, 60, 90.0f);

		// �v���C���[�Ƃ̋�������
		float fDisX = pPos->x - handPos.x;
		float fDisY = pPos->y - handPos.y;
		float fDisZ = pPos->z - handPos.z;

		// ���a��ݒ�
		float fBossradius = 25.0f;

		// ���a�̃T�C�Y���v�Z
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;

		float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// ���a���ɓ����Ă�����
		if (fDissAll <= fRadAll)
		{
			// �R���W���������Ԃ�
			return true;
		}
	}

	// �������ĂȂ��Ƃ�
	return false;

#if 0

	// ���t���[����
	if (m_pMotion->CheckFrame(90, 155, TYPE_CIRCLE) && m_isdaeth == false)
	{
		// ���f���̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

		// null��������
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// �����v�Z
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �v�Z���������̒����擾
		float fDist = D3DXVec3Length(&diff);

		// �����ȉ��Ȃ�
		if (fDist <= BOSSINFO::CIRCLEHITRANGE)
		{
			// ������Ԃ�
			return true;
		}

		return false;
	}
	// ���t���[����
	else if (m_pMotion->CheckFrame(195, 250, TYPE_CIRCLE) && m_isdaeth == false)
	{
		// ���f���̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND); // �E��

		// null��������
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// �����v�Z
		D3DXVECTOR3 diff = *pPos - D3DXVECTOR3(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �v�Z���������̒����擾
		float fDist = D3DXVec3Length(&diff);

		// �����ȉ��Ȃ�
		if (fDist <= BOSSINFO::CIRCLEHITRANGE)
		{
			// ������Ԃ�
			return true;
		}

		return false;
	}
	else
	{
		// ������Ȃ��Ƃ�
		return false;
	}
#endif
}
//=========================================
// �U�艺�낵�U���̓����蔻��
//=========================================
bool CBoss::CollisionSwing(D3DXVECTOR3* pPos, float fHitRadius)
{
	// �����t���O���쐬
	static bool isCreate = false;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// ���t���[����
	if ((m_pMotion->CheckFrame(40, 40, TYPE_ARMRIGHTLEFT) || m_pMotion->CheckFrame(150, 150, TYPE_ARMRIGHTLEFT))&& !isCreate)
	{
		// �Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_ALART);

		// �U���T�C���𐶐�
		CSignal::Create();

		// �����t���O��L����
		isCreate = true;
	}
	else
	{
		// �t���[���O�Ȃ烊�Z�b�g
		isCreate = false;
	}

	//  ���t���[����
	if ((m_pMotion->CheckFrame(100, 160, TYPE_ARMRIGHTLEFT)) && m_isdaeth == false)
	{
		// �E��̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		if (!pRightHand) return false;

		// �E��̃��[���h�}�g���b�N�X���擾
		D3DXMATRIX mtxWorld = pRightHand->GetMtxWorld();

		// ���W�ɐݒ�
		D3DXVECTOR3 handPos(mtxWorld._41, mtxWorld._42, mtxWorld._43);

		// �v���C���[�Ƃ̋�������
		float fDisX = pPos->x - handPos.x;
		float fDisY = pPos->y - handPos.y;
		float fDisZ = pPos->z - handPos.z;

		// ���a��ݒ�
		float fBossradius = 25.0f;

		// ���a�̃T�C�Y���v�Z
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;

		float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// �Ռ��g
		if ((m_pMotion->CheckFrame(130, 130, TYPE_ARMRIGHTLEFT)))
		{
			// ���b�V���Ռ��g�𐶐�	
			CMeshImpact::Create(D3DXVECTOR3(handPos.x, 5.0f, handPos.z), 100, 120.0f, 5.0f, 15.0f);
		}

		// ���a���ɓ����Ă�����
		if (fDissAll <= fRadAll)
		{			
			// �R���W���������Ԃ�
			return true;
		}
	}

	if ((m_pMotion->CheckFrame(200, 200, TYPE_ARMRIGHTLEFT)))
	{
		// ����
		RollToPlayer();
	}

	//  ���t���[����
	if ((m_pMotion->CheckFrame(260, 310, TYPE_ARMRIGHTLEFT)) && m_isdaeth == false)
	{
		// ���a��ݒ�
		float fBossradius = 60.0f;

		// ���a�̃T�C�Y���v�Z
		float fradX = fBossradius + fHitRadius;
		float fradY = fBossradius + fHitRadius;
		float fradZ = fBossradius + fHitRadius;
		float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

		// �E��̃p�[�c�擾
		CModel* pRightHand = GetModelPartType(CModel::PARTTYPE_RIGHT_HAND);
		D3DXMATRIX mtxWorldR = pRightHand->GetMtxWorld();
		D3DXVECTOR3 handPosR(mtxWorldR._41, mtxWorldR._42, mtxWorldR._43);

		// ����̃p�[�c�擾
		CModel* pLeftHand = GetModelPartType(CModel::PARTTYPE_LEFT_HAND);
		D3DXMATRIX mtxWorldL = pLeftHand->GetMtxWorld();
		D3DXVECTOR3 handPosL(mtxWorldL._41, mtxWorldL._42, mtxWorldL._43);

		// �������W
		D3DXVECTOR3 CenterPos = (handPosL + handPosR) * 0.5f;

		// �Ռ��g
		if ((m_pMotion->CheckFrame(270, 270, TYPE_ARMRIGHTLEFT)))
		{
			// ���b�V���Ռ��g�𐶐�	
			CMeshImpact::Create(D3DXVECTOR3(CenterPos.x, 5.0f, CenterPos.z), 200, 120.0f, 5.0f, 15.0f);
		}

		if (pRightHand)
		{
			float fDisX = pPos->x - handPosR.x;
			float fDisY = pPos->y - handPosR.y;
			float fDisZ = pPos->z - handPosR.z;

			float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);

			if (fDissAll <= fRadAll)
			{
				return true; // �E��ɓ�����
			}
		}

		if (pLeftHand)
		{
			float fDisX = pPos->x - handPosL.x;
			float fDisY = pPos->y - handPosL.y;
			float fDisZ = pPos->z - handPosL.z;

			float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);

			if (fDissAll <= fRadAll)
			{
				return true; // ����ɓ�����
			}
		}
	}

	// �������ĂȂ��Ƃ�
	return false;
}
//====================================
// �q�b�g����
//====================================
void CBoss::Hit(int nDamage,D3DXVECTOR3 HitPos)
{
	// �t���O�������Ă�����
	if (m_isdaeth) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g���[�h�Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// �����̃_���[�W���i�[
	int realDamage = nDamage;

	//==========================
	// ��ڂ̎�_�p�[�c���擾
	//==========================
	CModel* pWeakHead = GetModelPartType(CModel::PARTTYPE_HEAD);

	// null����Ȃ�������
	if (pWeakHead)
	{
		// ��_�p�[�c�̃��[���h���W���擾
		D3DXMATRIX mtx = pWeakHead->GetMtxWorld();

		// ��_���W��ݒ�
		D3DXVECTOR3 weakPos(mtx._41, mtx._42, mtx._43 - 20.0f);

		// �q�b�g���W�Ƃ̋����𑪒�
		D3DXVECTOR3 diff = HitPos - weakPos;
		float fDist = D3DXVec3Length(&diff);

		// ����͈͓��Ȃ�
		if (fDist <= WEEKPOINTSIZE)
		{
			// �_���[�W3�{�ɂ���
			realDamage = nDamage * 3;
		}
	}

	// HP�����Z
	int nHp = m_pParam->GetHp();
	nHp -= realDamage;

	// 0�ȉ��Ȃ�
	if (nHp <= 0)
	{
		// �Z�b�g
		nHp = 0;
		m_pParam->SetHp(nHp);

		// ���S����
		m_isdaeth = true;

		// �X�R�A�����Z
		CScore::AddScore(50000);

		// �X�R�A�������o��
		CScore::SaveScore();

		// �|���̂ɂ����������Ԃ������o��
		CGameManager::GetTime()->Save();

		return;
	}
	else
	{
		// ���ݑ̗͂�ݒ�
		m_pParam->SetHp(nHp);

		// �ő�HP�̔��������������X�e�[�g�ύX
		int nMaxHp = m_pParam->GetMaxHp();

		if (nHp <= nMaxHp * 0.5f)
		{
			// �t���O�����g�p�Ȃ�
			if (!m_isEvent)
			{
				// �t���O��L����
				m_isEvent = true;

				// �C�x���g��Ԃֈڍs
				ChangeState(new CBossStateEvent(), CBossStateBace::ID_EVENT);

				return;
			}
		}
	}
}
//====================================
// ��ԕύX����
//====================================
void CBoss::ChangeState(CBossStateBace* pNewState, int Id)
{
	// �������g���Z�b�g����
	pNewState->SetOwner(this);

	// ��Ԃ�ύX����
	m_pState->ChangeState(pNewState);
}
//====================================
// ��������]�����鏈��
//====================================
void CBoss::RollToPlayer(void)
{
	// �v���C���[�̎擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);

	// null�Ȃ�
	if (pPlayer == nullptr) return;

	// �v���C���[�̍��W���擾
	D3DXVECTOR3 pPos = pPlayer->GetPos();

	// �{�X����v���C���[�Ɉ�{�̃x�N�g���𐶐�����
	D3DXVECTOR3 VecPlayer = m_pos - pPos;

	// ���������̊p�x�����߂�
	float angle = atan2f(VecPlayer.x, VecPlayer.z);

	// �v�Z�����p�x���Z�b�g
	m_rot.y = angle;
}
