//====================================
//
// UI���� [ ui.h ]
// Author: Asuma Nishio
//
//=====================================
#ifndef _UI_H_ // ���̃}�N����`������ĂȂ�������
#define _UI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "object2D.h"

//****************************
// UI�N���X���`
//****************************
class CUi : public CObject2D
{
public:
	//***************************
	// ��ԊǗ�
	//***************************
	enum STATE
	{
		STATE_NONE,
		STATE_FALL,
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUi();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(const char * pRegistername);
	void SetUseFall(bool isFlags,int nState) { m_isFlash = isFlags,m_nState = nState;}

	// �ÓI�����o�֐�
	static CUi* Create(D3DXVECTOR3 pos, int nFlashFrame,float fWidth, float fHeight,const char * Filename,bool isUse);

private:
	int m_nTexIdxType;		// �e�N�X�`���C���f�b�N�X
	int m_nFlashFrame;		// �_�ŊԊu
	bool m_isFlash;			// �_�ł��邩�ǂ���
	int m_nState;
};

#endif