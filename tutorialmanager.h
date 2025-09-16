//=============================================
//
// �`���[�g���A���Ǘ����� [ tutorialmanager.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTORIALMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIALMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �O���錾
//******************************
class CTutorialUi;
class CTutoTask;

//********************************
// �`���[�g���A���Ǘ��N���X���`
//********************************
class CTutorialManager
{
public:
	//***********************
	// �������^�X�N�̎��
	//***********************
	enum TASKTYPE
	{
		TASKTYPE_MOVE,
		TASKTYPE_ATTACK,
		TASKTYPE_JUMP,
		TASKTYPE_JUMPATTACK,
		TASKTYPE_LASER,
		TASKTYPE_LASERACTION,
		TASKTYPE_FREE,
		TASKTYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTutorialManager();
	~CTutorialManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	CTutorialUi* m_pTutoui; // �`���[�g���A��ui�N���X�̃|�C���^
	CTutoTask* m_pTask;		// �^�X�N�N���X�|�C���^	
	TASKTYPE m_Tasktype;	// ���
	bool m_isFreeDone;
};

#endif
