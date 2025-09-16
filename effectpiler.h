//======================================
//
// ����G�t�F�N�g���� [ effectpiler.h ]
// Author: Asuma Nishio
//
//======================================

#ifndef _EFFECTPILER_H_ // ���̃}�N����`������ĂȂ�������
#define _EFFECTPILER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************  
// �C���N���[�h�t�@�C���錾
//**************************
#include "billboard.h"

//**************************  
// �G�t�F�N�g�N���X���`
//**************************
class CEffectPiler : public CBillboard
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEffectPiler(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectPiler();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CEffectPiler* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fRadius, int nLife);

private:
	int m_nLife;		// �̗�
	float m_fRadius;	// ���a
	int m_nIdxTex;
};

#endif
