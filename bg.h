//====================================
//
// �w�i���� [ bg.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BG_H_ // ���̃}�N����`������ĂȂ�������
#define _BG_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �w�i�N���X��錾
//**********************
class CBg : public CObject2D
{
public:
	// �w�i���
	typedef enum
	{
		BG_BACK = 0,
		BG_CENTER,
		BG_FRONT,
		BG_MAX
	}BG;

	CBg(int nPriority = 2);
	~CBg();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CBg* Create(int nIdxBg);

	void SetTexture(int nType);

private:
	void SetScrollSpeed(float speed) { m_ScrollSpeed = speed; }	// �X�N���[���֐�

	D3DXVECTOR2 m_TexScroll;	// �e�N�X�`���X�N���[���ϐ�

	int m_IndexBg;				// ���C���[�ԍ�
	float m_ScrollSpeed;		// �X�N���[���̑��x

	static LPDIRECT3DTEXTURE9 m_pTexture[BG_MAX]; // �e�N�X�`���|�C���^


	int m_nIdxTexture;

};

#endif