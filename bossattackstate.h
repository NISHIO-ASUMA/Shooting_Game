//=============================================
//
// �{�X�̍U����ԊǗ����� [bossattackstate.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _BOSSATTACKSTATE_H_ // ���̃}�N����`������ĂȂ�������
#define _BOSSATTACKSTATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "bossstate.h"

//********************************
// ����U����ԊǗ��N���X���`
//********************************
class CBosshandAttack : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBosshandAttack();
	~CBosshandAttack();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);

private:

};

//************************************
// �@�����U����ԊǗ��N���X���`
//************************************
class CBossimpactAttack : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBossimpactAttack();
	~CBossimpactAttack();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);

private:

};

//************************************
// �U��񂵍U����ԊǗ��N���X���`
//************************************
class CBosscircleAttack : public CBossStateBace
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBosscircleAttack();
	~CBosscircleAttack();

	// �X�e�[�g���n�܂�Ƃ��Ɉ�x�����Ă΂��֐�
	void OnStart(void);

	// �X�e�[�g���X�V�����Ƃ��ɌĂ΂��֐�
	void OnUpdate(void);

	// �X�e�[�g���I�����鎞�Ɉ�x�����Ă΂��֐�
	void OnExit(void);

private:

};

#endif
