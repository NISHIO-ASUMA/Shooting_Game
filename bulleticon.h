//========================================
//
// �e�A�C�R������ [ bulleticon.h ]
// Author: Asuma Nishio
//
//========================================

#ifndef _BULLETICON_H_ // ���̃}�N����`������ĂȂ�������
#define _BULLETICON_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "object2D.h"

//***************************
// �e�A�C�R���\���N���X��`
//***************************
class CBulletIcon : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBulletIcon(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBulletIcon();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(const char * pTexName);

	// �ÓI�����o�֐�
	static CBulletIcon* Create(D3DXVECTOR3 pos, const char* pTexName, int nIdx);

private:
	int m_nIdxTex;	// �e�N�X�`���C���f�b�N�X
	int m_nIdx;
};

#endif