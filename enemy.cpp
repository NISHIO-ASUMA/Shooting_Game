//====================================
//
// �G�̏��� [ enemy.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemy.h"
#include "gamemanager.h"
#include "debugproc.h"
#include "parameter.h"
#include "particle.h"
#include "state.h"
#include "enemystate.h"
#include "player.h"

//***********************************
// �ÓI�����o�ϐ��錾
//***********************************
int CEnemy::m_NumEnemy = NULL;			// �G�̑���

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CEnemy::CEnemy(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_move = VECTOR3_NULL;
	m_StateCount = NULL;
	m_State = ENEMYSTATE_NONE;
	m_nMoveCount = NULL;
	m_pParam = nullptr;
	m_pStateMachine = nullptr;

	m_mtxRot = {};
	m_VecAxis = VECTOR3_NULL;
	m_quat = {};
	m_fValueRot = 0.009f;

	m_fAngle = NULL;
	m_fRadius = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CEnemy::~CEnemy()
{
	// ����
}
//===============================
// �G�̐���
//===============================
CEnemy* CEnemy::Create(const char* pFileName,const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,TYPE nType,int nHp)
{
	// �G�̃C���X�^���X����
	CEnemy* pEnemy = new CEnemy;

	// nullptr��������
	if (pEnemy == nullptr) return nullptr;

	// X�t�@�C���ݒ�
	pEnemy->SetFilePass(pFileName);
	pEnemy->SetRot(rot);
	pEnemy->SetPos(pos);

	// �������Ɏ��s������
	if (FAILED(pEnemy->Init()))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �G�̎�ރZ�b�g
	pEnemy->SetType(nType);

	// null����Ȃ�������
	if (pEnemy->m_pParam != nullptr)
	{
		// �p�����[�^�[���Z�b�g
		pEnemy->m_pParam->SetHp(nHp);
	}

	// �G���J�E���g���C���N�������g
	m_NumEnemy++;

	// �|�C���^��Ԃ�
	return pEnemy;
}
//===============================
// �G�̏���������
//===============================
HRESULT CEnemy::Init(void)
{
	// �e�N���X�̏�����
	CObjectX::Init();

	// �����o�ϐ��̏�����
	m_State = ENEMYSTATE_NORMAL;

	// null��������
	if (m_pParam == nullptr)
	{
		// �p�����[�^�[�|�C���^�𐶐�
		m_pParam = new CParameter;
	}

	// null��������
	if (m_pStateMachine == nullptr)
	{
		// �X�e�[�g�}�V���̃|�C���^����
		m_pStateMachine = new CStateMachine;

		// ������Ԃ��Z�b�g
		ChangeState(new CEnemyStateFall, CEnemyStateBase::ID_FALL);
	}

	// �I�u�W�F�N�g�̎��
	SetObjType(TYPE_ENEMY);

	// �N�H�[�^�j�I���K�p
	SetUseQuat(true);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �G�̏I������
//===============================
void CEnemy::Uninit(void)
{
	// nullptr�`�F�b�N
	if (m_pParam != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pParam;

		// nullptr���
		m_pParam = nullptr;
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

	// �I�u�W�F�N�g�̔j��
	CObjectX::Uninit();

	// �f�N�������g
	m_NumEnemy--;
}
//===========================================
// �G�̍X�V���� ( �~���̊O�������C���[�W )
//===========================================
void CEnemy::Update(void)
{
	// ���f�����S���W�̐ݒ�
	D3DXVECTOR3 Pos = VECTOR3_NULL;

	// ��]�ʂ����Z
	m_fValueRot += 0.03f;

	m_fRadius = CGameManager::GetCylinder()->GetRadius();
	float fLength = D3DX_PI * 2.0f * 30.0f;

	// �ʒu���v�Z
	float posx = Pos.x + cosf(m_fValueRot) * m_fRadius;
	float posz = Pos.z + sinf(m_fValueRot) * m_fRadius;
	float posy = GetPos().y; // �Œ�̍���

	// �ʒu�̍X�V
	SetPos(D3DXVECTOR3(posx, posy, posz));

	// ��]�����v�Z����
	m_VecAxis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	

#if 0
	// ��Ԃ̍X�V
	m_pStateMachine->Update();
#endif
}
//===========================================
// �G�̕`�揈�� ( �N�H�[�^�j�I����K�p���� )
//===========================================
void CEnemy::Draw(void)
{
	// �N�H�[�^�j�I���𐶐�
	D3DXQuaternionRotationAxis(&m_quat, &m_VecAxis, m_fValueRot);

	// ��]�}�g���b�N�X�𐶐�
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);

	// ���[���h�}�g���b�N�X�̎擾
	D3DXMATRIX mtx = GetMtxWorld();

	// �����𔽉f
	D3DXMatrixMultiply(&mtx, &m_mtxRot, &mtx);

	// �Z�b�g����
	SetMtxWorld(mtx);

	// �I�u�W�F�N�g�`��
	CObjectX::Draw();

	// �f�o�b�O�\��
	CDebugproc::Print("[ �G�̈ʒu : %.2f,%.2f,%.2f ]", GetPos().x, GetPos().y, GetPos().z);
	CDebugproc::Draw(0,280);
	CDebugproc::Print("[ �G�̊p�x : %.2f,%.2f,%.2f ]", GetRot().x, GetRot().y, GetRot().z);
	CDebugproc::Draw(0, 260);

}
//===============================
// �G�̃_���[�W����
//===============================
void CEnemy::HitEnemy(int nDamage)
{
	// �p�����[�^�[�擾
	int nHp = m_pParam->GetHp();

	// �̗͂����炷
	nHp -= nDamage;

	// ���ݑ̗͂�0�ȉ�
	if (nHp <= NULL)
	{
		// �G��j��
		Uninit();

		// �p�[�e�B�N������
		CParticle::Create(D3DXVECTOR3(GetPos().x, GetPos().y + 15.0f, GetPos().z), D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f), 100, 30, 60, 100);

		// �����ŏ�����Ԃ�
		return;
	}
	else
	{
		// ���ݑ̗͂��Z�b�g
		m_pParam->SetHp(nHp);
	}
}
//=================================
// �G�ƃv���C���[�̓����蔻�菈��
//=================================
bool CEnemy::Collision(D3DXVECTOR3* pPos)
{// ��������쐬����
	
	// ���݂̍��W���擾
	D3DXVECTOR3 EnemyPos = GetPos();

	// ������͈͂�ݒ�
	float HitRadius = 20.0f;
	float EHitRadius = 20.0f;

	// 2�_�Ԃ̋������v�Z
	float fRangeX = EnemyPos.x - pPos->x;
	float fRangeY = EnemyPos.y - pPos->y;
	float fRangeZ = EnemyPos.z - pPos->z;

	// ������2����v�Z
	float fDis = (fRangeX * fRangeX) + (fRangeY * fRangeY) + (fRangeZ * fRangeZ);

	// ���a�̋������v�Z
	float fHitAll = HitRadius + EHitRadius;
	float fRadiusSum = fHitAll * fHitAll;

	// �͈͓��ɂ���Ȃ�
	if (fDis <= fRadiusSum)
	{
		// �G������
		Uninit();

		// �����������ʂ�Ԃ�
		return true;
	}
	 
	// �f�t�H���g�ŕԂ�
	return false;
}
//=================================
// ��ԕύX����
//=================================
void CEnemy::ChangeState(CEnemyStateBase* pNewState, int id)
{
	// �Z�b�g����
	pNewState->SetOwner(this);

	// �X�e�[�g�ύX
	m_pStateMachine->ChangeState(pNewState);
}
//=================================
// �ړ���ԍX�V����
//=================================
void CEnemy::UpdateMoving(void)
{
	// ����
}
