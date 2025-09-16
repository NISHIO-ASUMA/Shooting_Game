//=====================================
//
// �{�X��ԊǗ����� [ bossstate.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BOSSSTATE_H_ // ���̃}�N����`������ĂȂ�������
#define _BOSSSTATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "state.h"
#include "boss.h"

//*****************************
// �{�X��ԊǗ��e�N���X���`
//*****************************
class CBossStateBace : public CStateBase
{
public:
	//***************************
	// ��ԊǗ�ID�񋓌^
	//***************************
	enum ID
	{
		ID_NEUTRAL, // �ҋ@
		ID_ACTION,	// �U��
		ID_DAMAGE,	// �_���[�W
		ID_EVENT,	// �C�x���g
		ID_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBossStateBace();
	~CBossStateBace();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	virtual void OnStart() {}

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	virtual void OnUpdate() {}

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	virtual void OnExit() {}

	// �Z�b�^�[
	void SetOwner(CBoss* pBoss) { m_pBoss = pBoss; }

	// �Q�b�^�[
	int GetID() const override { return m_ID; }
	void SetID(ID id) { m_ID = id; }

protected:
	CBoss* m_pBoss;		// �v���C���[�̃|�C���^

private:
	ID m_ID;		// �񋓌^�̃|�C���^
};

//*****************************
// �ҋ@��ԊǗ��N���X���`
//*****************************
class CBossStateNeutral : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBossStateNeutral(int nTime);
	~CBossStateNeutral();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);

private:
	int m_CoolTime;		// �X�e�[�g�؂�ւ�����
	int m_nCurrentState; // ���ݏ��
};

//*****************************
// �U����ԊǗ��N���X���`
//*****************************
class CBossStateAttack : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBossStateAttack();
	~CBossStateAttack();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);
};

//*****************************
// �C�x���g��ԊǗ��N���X
//*****************************
class CBossStateEvent : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBossStateEvent();
	~CBossStateEvent();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);
};


#endif