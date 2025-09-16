//=====================================
//
// �p�[�e�B�N������ [ particle.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PARTICLE_H_ // ���̃}�N����`������ĂȂ�������
#define _PARTICLE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include <vector>

//*********************
// �O���錾
//*********************
class CEffect;

//***************************
// �p�[�e�B�N���N���X���`
//***************************
class CParticle : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CParticle(int nPriority = static_cast<int>(CObject::PRIORITY::EFFECT));
	~CParticle();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CParticle* Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nMaxParticle, int nRadius, int nLength, int nLife);

private:
	std::vector<CEffect*> m_pEffect; // �G�t�F�N�g�z��

	D3DXVECTOR3 m_pos;	// ���W
	D3DXCOLOR m_col;	// �F
	int m_nMaxParticle; // �ő吔
	int m_nLife;		// ����
	int m_nLength;		// ��U���鋗��
	int m_nRadius;		// ���̑傫��
};

#endif