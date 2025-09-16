//====================================
//
// �^�C�g��ui���� [ titleui.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TITLEUI_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLEUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//************************************
// �^�C�g��2D�I�u�W�F�N�g�N���X���`
//************************************
class CTitleUi : public CObject2D
{
public:
	//*********************
	// ���j���[���ʗ񋓌^
	//*********************
	enum MENU
	{
		MENU_GAME,
		MENU_TUTORIAL,
		MENU_EXIT,
		MENU_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTitleUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CTitleUi();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(int nType);

	// �ÓI�����o�֐�
	static CTitleUi* Create(D3DXVECTOR3 pos,D3DXCOLOR col,float fWidth,float fHeight,int nType);

private:
	int m_nTexIdx; // �e�N�X�`���C���f�b�N�X
};

#endif