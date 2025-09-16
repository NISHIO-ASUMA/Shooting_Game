//=====================================
//
// �e�̏��� [ bullet.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BULLET_H_ // ���̃}�N����`������ĂȂ�������
#define _BULLET_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"
#include "object.h"

//**************************
// �e�N���X���`
//**************************
class CBullet : public CBillboard
{
public:
	//********************
	// �e�̎�ނ��`
	//********************
	enum BTYPE
	{
		BTYPE_PLAYER,
		BTYPE_LASER,
		BTYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBullet(int nPriority = static_cast<int>(CObject::PRIORITY::BULLET));
	~CBullet();

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 pos); 

	// �ÓI�����o�֐�
	static CBullet* Create(const D3DXVECTOR3 pos,const D3DXVECTOR3 rot,BTYPE nType,const float fWidth, const float fHeight, const int nLife);

	// �Z�b�^�[
	static void SetType(BTYPE type);
	void SetTexture(BTYPE type);

	// �Q�b�^�[
	static BTYPE GetType(void) { return m_Type; }

private:
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_OldPos;	// �ߋ��̍��W
	static BTYPE m_Type;	// ���
	D3DCOLOR m_col;			// �e�̃J���[
	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	int m_nLife;			// �̗�
};
#endif
