//=============================================
//
// �Q�[�W�֌W�̃N���X���� [ gage.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _GAGE_H_ // ���̃}�N����`������ĂȂ�������
#define _GAGE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//**********************
// �O���錾
//**********************
class CObject;

//**********************
// �Q�[�W�N���X���`
//**********************
class CGage :public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CGage(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CGage();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetGageLength(const int nMaxLife, const int nCurrentLife, float fValue, float Height);
	void FSetGageLength(float fMax, float fCurrent, float fMaxWidth, float fHeight);

	// �ÓI�����o�֐�
	static CGage* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);

private:
};

#endif

