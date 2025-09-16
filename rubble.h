//========================================
//
// ���I�I�u�W�F�N�g���� [ rubble.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _RUBBLE_H_ // ���̃}�N����`������ĂȂ�������
#define _RUBBLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "objectX.h"

//**********************************
// �O���錾
//**********************************
class CObject;
class CShadow;

//**********************************
// ���I�N���X���`
//**********************************
class CRubble : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRubble(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CRubble();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3 *DestPos);

	// ��������
	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:
	D3DXVECTOR3 m_Fallingspeed;	// �������x
	CShadow* m_pShadow;			// �e�N���X�|�C���^
};

#endif