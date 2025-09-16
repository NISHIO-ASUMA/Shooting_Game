//=============================================
//
// �v���C���[��ԊǗ����� [ playerstate.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _PLAYERSTATE_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYERSTATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "state.h"
#include "player.h"

//*********************************
// �v���C���[�̃x�[�X��ԊǗ�
//*********************************
class CPlayerStateBase : public CStateBase
{
public:

	//***************************
	// ��ԊǗ�ID�񋓌^
	//***************************
	enum ID
	{
		ID_NEUTRAL, // �ҋ@
		ID_MOVE, // �ړ�
		ID_ACTION, // �U��
		ID_JUMP, // �W�����v
		ID_GUARD, // �h��
		ID_DAMAGE,// �_���[�W
		ID_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateBase();
	~CPlayerStateBase();


	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	virtual void OnStart() {}

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	virtual void OnUpdate() {}

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	virtual void OnExit() {}

	// �Q�b�^�[
	int GetID() const override { return m_ID; }
	void SetID(ID id) { m_ID = id; }

	// �Z�b�^�[
	void SetOwner(CPlayer* pPlayer) { m_pPlayer = pPlayer; }

protected:
	CPlayer* m_pPlayer;		// �v���C���[�̃|�C���^

private:
	ID m_ID;		// �񋓌^�̃|�C���^
};

//*********************************
// �ҋ@��Ԏ��̏�ԊǗ�
//*********************************
class CPlayerStateNeutral : public CPlayerStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateNeutral();
	~CPlayerStateNeutral();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();
};

//*********************************
// �ړ����̏�ԊǗ�
//*********************************
class CPlayerStateMove : public CPlayerStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateMove();
	~CPlayerStateMove();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();
};

//*********************************
// �U�����̏�ԊǗ�
//*********************************
class CPlayerStateAction : public CPlayerStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateAction();
	~CPlayerStateAction();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();
};

//*********************************
// �_���[�W��Ԏ��̊Ǘ�
//*********************************
class CPlayerStateDamage : public CPlayerStateBase
{
public:

	//**************************
	// ��ԗ񋓌^
	//**************************
	enum DAMAGESTATE
	{
		DAMAGESTATE_NONE,
		DAMAGESTATE_NORMAL,
		DAMAGESTATE_DAMAGE,
		DAMAGESTATE_INVINCIBLE,
		DAMAGESTATE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateDamage(int nDamage);
	~CPlayerStateDamage();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();

	// �Q�b�^�[
	int GetState()const { return m_nStateCount; }

private:
	int m_nStateCount;		// �Ǘ��J�E���g
	int m_nDamage;			// �_���[�W��
	int m_nCurrentstate;	// ���ݏ��
};

//*********************************
// �W�����v��Ԏ��̊Ǘ�
//*********************************
class CPlayerStateJump : public CPlayerStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateJump();
	~CPlayerStateJump();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();

private:
};

//*********************************
// �K�[�h��Ԏ��̊Ǘ�
//*********************************
class CPlayerStateGuard : public CPlayerStateBase
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayerStateGuard();
	~CPlayerStateGuard();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart();

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate();

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit();

private:

};

#endif