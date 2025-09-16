//============================================
//
// ��ԊǗ����� [ state.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _STATE_H_ // ���̃}�N����`������ĂȂ�������
#define _STATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �X�e�[�g�x�[�X�N���X
//*********************************
class CStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CStateBase();
	virtual ~CStateBase();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	virtual void OnStart() {}

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	virtual void OnUpdate() {}

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	virtual void OnExit() {}

	// ID�擾�p�֐�
	virtual int GetID() const = 0;
};

//*********************************
// �X�e�[�g�}�V���N���X
//*********************************
class CStateMachine
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CStateMachine();
	~CStateMachine();

	// �����o�֐�
	void Update(void);						 
	void ChangeState(CStateBase* pNewState);
	void OnExit();	

	// �Q�b�^�[
	int GetNowStateID();
	CStateBase* GetNowState() const { return m_pNowState; }

private:
	CStateBase* m_pNowState;	// ���N���X�̃X�e�[�g�|�C���^
};

#endif
