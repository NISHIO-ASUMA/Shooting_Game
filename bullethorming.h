//===================================================
//
// �e�̃I�u�W�F�N�g�z�[�~���O���� [ bullethorming.h ]
// Author: Asuma Nishio
//
//===================================================

#ifndef _BULLETHORMING_H_ // ���̃}�N����`������ĂȂ�������
#define _BULLETHORMING_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "objectX.h"

//**************************
// �O���錾
//**************************
class CObject;

//********************************
// �e�̃z�[�~���O�N���X���`
//********************************
class CBulletHorming : public CObjectX
{
public:

	//*************************
	// �z�[�~���O�̎�ޗ񋓌^
	//*************************
	enum HORMING
	{
		HORMING_PLAYER, // �v���C���[�Ǐ]
		HORMING_GROUND, // �n�ʂɒ��e����
		HORMING_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBulletHorming(int nPriority = static_cast<int>(CObject::PRIORITY::BULLET));
	~CBulletHorming();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void CollisionAll(void);
	bool Collision(D3DXVECTOR3 DestPos);

	// �ÓI�����o�֐�
	static CBulletHorming* Create(const char * pFileNama,D3DXVECTOR3 pos);

private:

	float m_fRange;		// �Ǐ]�����v�Z�p
	bool m_isHit;		// �����蔻��t���O
};

#endif
