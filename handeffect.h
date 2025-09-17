//========================================
//
// �n���h�G�t�F�N�g���� [ handeffect.h ]
// Author: Asuma Nishio
//
//========================================

#ifndef _HANDEFFECT_H_ // ���̃}�N����`������ĂȂ�������
#define _HANDEFFECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "billboard.h"

//**********************
// �O���錾
//**********************
class CObject;

//***********************************
// �n���h�G�t�F�N�g�N���X���`
//***********************************
class CHandEffect : public CBillboard
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CHandEffect(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CHandEffect();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CHandEffect* Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius);

private:
	int m_nLife;			// ����
	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
	float m_fRadius;		// ���a
	D3DXVECTOR3 m_move;		// �ړ���
};

#endif