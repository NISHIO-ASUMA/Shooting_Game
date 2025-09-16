//====================================
//
// �������� [ explosion.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EXPLOSION_H_ // ���̃}�N����`������ĂȂ�������
#define _EXPLOSION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**************************
// �����N���X���`
//**************************
class CExplosion : public CObject2D
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	CExplosion(int nPriority = 3);
	~CExplosion();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture();

	// �ÓI�����o�֐�
	static CExplosion* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot,D3DXCOLOR col);


private:
	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X
};

#endif