//==============================================================
//
// �J�����A�j���[�V�������ɓK�p����UI���� [ moveui.h ]
// Author: Asuma Nishio
//
//==============================================================

#ifndef _MOVEUI_H_ // ���̃}�N����`������ĂȂ�������
#define _MOVEUI_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object2D.h"

//********************************************************
// �J�����A�j���[�V�������ɓK�p����UI�N���X
//********************************************************
class CMoveUi : public CObject2D
{
public:
	//**********************
	// �ړ��������
	//**********************
	enum MOVETYPE
	{
		MOVETYPE_RIGHT,
		MOVETYPE_LEFT,
		MOVETYPE_CENTER,
		MOVETYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CMoveUi(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CMoveUi();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(const char* pRegistername);

	// �ÓI�����o�֐�
	static CMoveUi* Create(D3DXVECTOR3 pos, const char* pFileName, MOVETYPE type);

private:
	int m_nIdxTexture;	// �e�N�X�`���C���f�b�N�X
	MOVETYPE m_nMoveType;	// �ړ����
};
#endif