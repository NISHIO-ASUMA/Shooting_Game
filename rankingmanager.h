//==========================================
//
// �����L���O�Ǘ����� [ rankingmanager.h ]
// Author: Asuma Nishio
//
//==========================================

#ifndef _RANKINGMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RANKINGMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �O���錾
//******************************
class CResultScore;

//******************************
// �����L���O�Ǘ��N���X���`
//******************************
class CRankingManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRankingManager();
	~CRankingManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	// �N���X�|�C���^

};

#endif