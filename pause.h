//====================================
//
// �|�[�Y���� [ pause.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PAUSE_H_ // ���̃}�N����`������ĂȂ�������
#define _PAUSE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//**********************
// �|�[�Y�N���X���`
//**********************
class CPause : public CObject2D
{
public:
	//******************
	// �I�����񋓌^
	//******************
	enum MENU
	{
		MENU_BACK,		// �w�i
		MENU_RETRY,		// ��蒼��
		MENU_CONTINUE,  // �p��
		MENU_QUIT,		// �^�C�g���J��
		MENU_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPause(int nPriority = static_cast<int>(CObject::PRIORITY::PAUSE));
	~CPause();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);
	void SetType(int nType) { m_nPauseType = nType; }

	// �ÓI�����o�֐�
	static CPause* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col, int nType);


private:
	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X�ԍ�
	int m_nPauseType;	// �|�[�Y�̎��
};

#endif
