//============================================
//
// ���[�U�[�G�t�F�N�g���� [ effectlaser.h ]
// Author: Asuma Nishio
// 
//============================================

#ifndef _EFFECTLASER_H_ // ���̃}�N����`������ĂȂ�������
#define _EFFECTLASER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//*********************************
// ���[�U�[�G�t�F�N�g�N���X���`
//*********************************
class CEffectLaser : public CBillboard
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEffectLaser(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CEffectLaser();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CEffectLaser* Create(D3DXVECTOR3 pos, D3DXVECTOR3 Endpos,D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;		// �̗�
	int m_nIdxTex;		// �e�N�X�`���C���f�b�N�X
	float m_fRadius;	// ���a
	float m_fLength;
	D3DXVECTOR3 m_move;	// �ړ���
	D3DXVECTOR3 m_EndPos; // �I�_���W
	D3DXVECTOR3 m_OldPos; // �ߋ��̍��W
};

#endif