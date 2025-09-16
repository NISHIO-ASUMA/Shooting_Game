//=============================================
//
// �`���[�g���A���^�X�N���� [ tutotask.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _TUTOTASK_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTOTASK_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include <string>
#include <vector>

//******************************
// �O���錾
//******************************
class CTutorialUi;

//********************************
// �^�X�N�N���X���`
//********************************
class CTutoTask
{
public:
	//**************************
	// �ǂݍ��ݏ��\����
	//**************************
	struct TASKINFO
	{
		D3DXVECTOR3 pos;	// ���W
		float fWidth;		// ����
		float fHeight;		// ����
		std::string TexName; // �e�N�X�`����
		int nState;			// ���
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTutoTask();
	~CTutoTask();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(void);
	void NextTask(void);

	// �Q�b�^�[
	int GetTaskIndex() const { return m_nCurrentIndex; }

private:
	std::vector<TASKINFO>m_pTutoUi;	// ���I�z��
	int m_nCurrentIndex;			// ���̃^�X�N�ԍ�
	CTutorialUi* m_pCurrentUi;		// �\������UI
	TASKINFO m_Info;				// �\���̕ϐ�

	void CreateTaskUi(int index);	// ����
};


#endif

