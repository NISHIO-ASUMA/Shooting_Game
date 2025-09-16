//=========================================
//
// �^�C�g�����S���� [ titlelogo.h ]
// Author: Asuma Nishio
// 
//==========================================

#ifndef _TITLELOGO_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLELOGO_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "object2D.h"

//***************************
// �O���錾
//***************************
class CObject;

//***************************
// �^�C�g�����S�N���X��`
//***************************
class CTitleLogo : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleLogo(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleLogo();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �ÓI�����o�֐�
	static CTitleLogo* Create(D3DXVECTOR3 pos,float fWidth, float fHeight);

private:
	int m_nTexIdx;		// �e�N�X�`���C���f�b�N�X
	D3DXVECTOR3 m_move;	// �ړ���
	bool m_isAnimating;  // �A�j���[�V��������
	int  m_nFrame;		// �o�߃t���[����
	int  m_nMaxFrame;	// �A�j���[�V��������
};

#endif
