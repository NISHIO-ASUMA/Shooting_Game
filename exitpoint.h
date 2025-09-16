//====================================
//
// �o���|�C���g���� [ exitpoint.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _EXITPOINT_H_ // ���̃}�N����`������ĂȂ�������
#define _EXITPOINT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object3D.h"

//**********************
// �|�C���g�N���X���`
//**********************
class CExitPoint : public CObject3D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CExitPoint(int nPriority = static_cast<int>(CObject::PRIORITY::SHADOW));
	~CExitPoint();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);
	bool Collision(D3DXVECTOR3 * DestPos);

	// �ÓI�����o�֐�
	static CExitPoint* Create(D3DXVECTOR3 pos, float fWidth);

private:
	int m_nIdxTex;	// �e�N�X�`���C���f�b�N�X
};

#endif