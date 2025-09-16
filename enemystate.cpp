//=====================================
//
// �G�̏�ԊǗ����� [ enemystate.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemystate.h"

//**********************
// �萔�錾
//**********************
constexpr float FALL_VALUE = 15.0f; // �������x

//==================================
// �G��Ԋ��N���X�R���X�g���N�^
//==================================
CEnemyStateBase::CEnemyStateBase()
{
	// �l�̃N���A
	m_ID = ID_NONE;
	m_pEnemy = nullptr;
}
//==================================
// �G��Ԋ��N���X�f�X�g���N�^
//==================================
CEnemyStateBase::~CEnemyStateBase()
{
	// ����
}

//==================================
// ������ԃR���X�g���N�^
//==================================
CEnemyStateFall::CEnemyStateFall()
{
	// ID���Z�b�g����
	SetID(ID_FALL);
	m_fSpeedFall = NULL;
}
//==================================
// ������ԃf�X�g���N�^
//==================================
CEnemyStateFall::~CEnemyStateFall()
{
	// ����
}
//==================================
// ������ԊJ�n�֐�
//==================================
void CEnemyStateFall::OnStart()
{
	// �l���Z�b�g
	m_fSpeedFall = FALL_VALUE;
}
//==================================
// ������ԍX�V�֐�
//==================================
void CEnemyStateFall::OnUpdate()
{
	// ���ݍ��W�̎擾
	D3DXVECTOR3 NowPos = m_pEnemy->GetPos();

	// �����X�s�[�h���|����
	NowPos.y -= m_fSpeedFall;

	// ���ݍ��W�ɃZ�b�g
	m_pEnemy->SetPos(NowPos);


	//	if ( �n�ʂɂ����� )
	//	{ 
	//	  // �ړ��ʂ�0�ɂ���
	//	  m_fSpeedFall = NULL;
	// 
	//	  // ��ԕύX
	//	  ChangeState(new CEnemyStateMove(),ID_MOVE);
	//	}
}
//==================================
// ������ԏI���֐�
//==================================
void CEnemyStateFall::OnExit()
{

}


//==================================
// �ړ���Ԏ��R���X�g���N�^
//==================================
CEnemyStateMove::CEnemyStateMove()
{
	// ID���Z�b�g����
	SetID(ID_MOVE);
}
//==================================
// �ړ���Ԏ��f�X�g���N�^
//==================================
CEnemyStateMove::~CEnemyStateMove()
{
	// ����
}
//==================================
// �ړ���ԊJ�n�֐�
//==================================
void CEnemyStateMove::OnStart()
{
	// ����
}
//==================================
// �ړ���ԍX�V�֐�
//==================================
void CEnemyStateMove::OnUpdate()
{
	// �ړ�����
	m_pEnemy->UpdateMoving();
}
//==================================
// �ړ���ԏI���֐�
//==================================
void CEnemyStateMove::OnExit()
{

}

