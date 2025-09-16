//=====================================
//
// �����L���O�V�[������ [ ranking.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RANKING_H_ // ���̃}�N����`������ĂȂ�������
#define _RANKING_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "scene.h"

//******************************
// �O���錾
//******************************
class CRankingManager;

//******************************
// �����L���O�V�[���N���X���`
//******************************
class CRanking : public CScene
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRanking();
	~CRanking();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CRanking* Create(void);

private:
	CRankingManager* m_pRankManager;	// �N���X�|�C���^
};

#endif