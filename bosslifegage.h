//=========================================
//
// �{�X�̗͏��� [ bosslifegage.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _BOSSLIFEGAGE_H_ // ���̃}�N����`������ĂȂ�������
#define _BOSSLIFEGAGE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "gage.h"

//**********************
// �O���錾
//**********************
class CBoss;

//***************************
// �{�X�̗͊Ǘ��N���X���`
//***************************
class CBossLifeGage : public CGage
{
public:
	//***********************
	// �Q�[�W�̎��
	//***********************
	enum TYPE
	{
		TYPE_FRAME,
		TYPE_GAGE,
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBossLifeGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CBossLifeGage();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetType(int nType) { m_Type = nType; }
	void SetTexture(int nType);

	// �ÓI�����o�֐�
	static CBossLifeGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);

private:
	int m_nCurrentLifeLength;		// �o�[�̒�����l
	int m_nMaxLifeLength;	// �ő�̗͎��̒���
	int m_Type;				// �񋓕ϐ�

	int m_nIdxTex;	// �e�N�X�`���C���f�b�N�X
	CBoss* m_pBoss; // �{�X�̃|�C���^

};

#endif

