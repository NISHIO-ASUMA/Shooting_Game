//============================================
//
// �V�[���h�֐� [ barrierdurability.h ]
// Author : Asuma Nishio
// 
//============================================

#ifndef _BARRIERDURABILITY_H_ // ���̃}�N����`������ĂȂ�������
#define _BARRIERDURABILITY_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "objectX.h"

//*********************************
// �O���錾
//*********************************
class CObject;

//*********************************
// �o���A�I�u�W�F�N�g�N���X���`
//*********************************
class CBarrierDurability : public CObjectX
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBarrierDurability(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CBarrierDurability();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool Collision(D3DXVECTOR3* DestPos);

	// �Z�b�^�[
	void SetIdx(int nValue) { m_nIdx = nValue; }
	
	/**
	* @brief �N���X
	* @param m_nIdx 
	* @return �߂�l
	*/
	static CBarrierDurability* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,const char * pFilename);

private:
	int m_nIdx;		// �����ԍ�
};


#endif