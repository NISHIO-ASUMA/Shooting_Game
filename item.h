//===================================
//
// �A�C�e������ [ item.h ]
// Author: Asuma Nishio
//
//===================================

#ifndef _ITEM_H_ // ���̃}�N����`������ĂȂ�������
#define _ITEM_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "objectX.h"

//****************************
// �O���錾
//****************************
class CObject;

//****************************
// �A�C�e���N���X���`
//****************************
class CItem : public CObjectX
{
public:
	//****************************
	// �A�C�e���̎��
	//****************************
	enum TYPE
	{
		TYPE_GUARD,	// �K�[�h
		TYPE_LIFE,	// �̗͉�
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CItem(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CItem();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* pPos);

	// �ÓI�����o�֐�
	static CItem* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,int nType);

private:
	int m_nType;	// �A�C�e���̎��
};

#endif