//====================================
//
// ���C�g���� [ light.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _LIGHT_H_ // ���̃}�N����`������ĂȂ�������
#define _LIGHT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// ���C�g�N���X���`
//**********************
class CLight
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CLight();
	~CLight();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:
	static inline constexpr int NUMLIGHT = 3;		// �ݒu���鐔

	D3DLIGHT9 m_aLight[NUMLIGHT]; // ���C�g��
	D3DXVECTOR3 m_vecDir[NUMLIGHT];	// �x�N�g��
};

#endif