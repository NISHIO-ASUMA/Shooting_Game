//========================================
//
// �`���[�W���� [ charge.h ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "gage.h"

//****************************
// �O���錾
//****************************
class CObject;

//****************************
// �`���[�W�N���X���`
//****************************
class CCharge : public CGage
{
public:
	//***********************
	// �e�N�X�`����ޗ񋓌^
	//***********************
	enum CHARGE
	{
		CHARGE_FRAME,	// �t���[��
		CHARGE_BAR,		// �Q�[�W�{��
		CHARGE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CCharge(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CCharge();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetType(int nType) { m_nType = nType; }
	void SetTexture(int nType);

	// �ÓI�����o�֐�
	static CCharge* Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);
	static void AddCharge(float fValue);
	static void DecCharge(float fValue);
	static bool GetChargeFlag(void) { return m_isCharge; }

private:
	int m_nIdxTex;
	int m_nType;

	static bool m_isCharge;

	static float m_fCharge;
};

