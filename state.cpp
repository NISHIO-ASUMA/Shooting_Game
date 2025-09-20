//=============================================
//
// ��ԊǗ����� [ state.cpp ]
// Author: Asuma Nishio
//
//=============================================

//***********************
// �C���N���[�h�t�@�C��
//***********************
#include "state.h"
#include "playerstate.h"

//==================================
// �X�e�[�g�x�[�X�R���X�g���N�^
//==================================
CStateBase::CStateBase()
{
	// ����
}
//==================================
// �X�e�[�g�x�[�X�f�X�g���N�^
//==================================
CStateBase::~CStateBase()
{
	// ����
}


//==================================
// �X�e�[�g�}�V���R���X�g���N�^
//==================================
CStateMachine::CStateMachine()
{
	// �l�̃N���A
	m_pNowState = nullptr;
}
//==================================
// �X�e�[�g�}�V���f�X�g���N�^
//==================================
CStateMachine::~CStateMachine()
{
	// ����
}
//==================================
// �X�e�[�g�}�V���X�V����
//==================================
void CStateMachine::Update(void)
{
	// nullptr����Ȃ�������
	if (m_pNowState != nullptr)
	{
		// �X�V�J�n
		m_pNowState->OnUpdate();
	}
}
//==================================
// �X�e�[�g�ύX����
//==================================
void CStateMachine::ChangeState(CStateBase* pNewState)
{	
	// �|�C���^�����݂���Ƃ�
	if (m_pNowState != nullptr && pNewState != nullptr)
	{
		// ID �������Ȃ�
		if (m_pNowState->GetID() == pNewState->GetID())
		{
			delete pNewState;

			// �����ŏ�����Ԃ�
			return;
		}
	}

	// ���łɃX�e�[�g���Z�b�g����Ă���I������
	if (m_pNowState != nullptr)
	{
		// �I��
		m_pNowState->OnExit();

		// �|�C���^�̔j��
		delete m_pNowState;

		// nullptr�ɏ���������
		m_pNowState = nullptr;
	}

	// �V�����X�e�[�g���Z�b�g����
	m_pNowState = pNewState;

	// �V�����X�e�[�g���J�n����
	m_pNowState->OnStart();
}
//==================================
// �X�e�[�g�I������
//==================================
void CStateMachine::OnExit()
{
	// ���łɃX�e�[�g���Z�b�g����Ă���I������
	if (m_pNowState != nullptr)
	{
		// �j��
		delete m_pNowState;

		// null������
		m_pNowState = nullptr;
	}
}
//==================================
// ���ݏ�Ԃ��擾
//==================================
int CStateMachine::GetNowStateID()
{
	if (m_pNowState)
		return m_pNowState->GetID(); // ���z�֐��Ƃ���

	return 0; // �j���[�g����
}