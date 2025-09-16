//===========================================
//
// �`���[�g���A���{�X���� [ tutoboss.h ]
// Author: Asuma Nishio
//
//===========================================

#ifndef _TUTORIALBOSS_H_ // ���̃}�N����`������ĂȂ�������
#define _TUTORIALBOSS_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// �`���[�g���A���{�X�N���X���`
//********************************
class CTutorialBoss : public CObject
{
public:
	//***************************
	// ���[�V�����񋓌^�錾
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL = 0,	// �j���[�g����
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTutorialBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTutorialBoss();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CTutorialBoss* Create(D3DXVECTOR3 pos);

private:
	static constexpr int TUTO_MODEL = 21; // �g�����f����

	D3DXVECTOR3 m_pos;		// ���\
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxworld;	// �}�g���b�N�X

	CModel* m_pModel[TUTO_MODEL];	// ���f���̃|�C���^
	CMotion* m_pMotion;				// ���[�V�����|�C���^

};

#endif
