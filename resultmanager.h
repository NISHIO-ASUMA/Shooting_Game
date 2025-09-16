//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _RESULTMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RESULTMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �O���錾
//**************************
class CResultScore;

//**************************
// ���U���g�Ǘ��N���X���`
//**************************
class CResultManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CResultManager();
	~CResultManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	void Load(void);

private:
	static constexpr int SCORELISTNUM = 3;

	bool m_isKeyDown; // �L�[���̓t���O
	int m_nGameScore; // �X�R�A���i�[
	int m_nLastTime; // ���Ԃ��i�[

	CResultScore* m_pResultScore[SCORELISTNUM];	// �X�R�A�|�C���^
};

#endif

