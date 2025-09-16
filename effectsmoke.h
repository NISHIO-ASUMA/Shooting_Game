//==========================================
//
// ���G�t�F�N�g���� [ effectsmoke.h ]
// Author : Asuma Nishi
//
//==========================================

#ifndef _EFFECTSMOKE_H_	 // ���̃}�N����`������ĂȂ�������
#define _EFFECTSMOKE_H_	 // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "billboard.h"

//**********************************
// �O���錾
//**********************************
class CObject;

//**********************************
// ���G�t�F�N�g�N���X���`
//**********************************
class CEffectSmoke : public CBillboard
{
public:
	CEffectSmoke(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectSmoke();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	static CEffectSmoke* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nIdxTex;		// �e�N�X�`���C���f�b�N�X
	int m_nLife;		// �̗�
	float m_fRadius;	// ���a
	D3DXVECTOR3 m_move;	// �ړ���
};

#endif