//=====================================
//
// 2D�I�u�W�F�N�g���� [ object2D.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _OBJECT2D_H_ // ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//****************************
// �I�u�W�F�N�g2D�N���X���`
//****************************
class CObject2D : public CObject
{
public:
	//****************************
	// �A���J�[�|�C���g�^�C�v
	//****************************
	enum ANCHORTYPE
	{
		ANCHORTYPE_NONE,
		ANCHORTYPE_CENTER,
		ANCHORTYPE_LEFTSIDE,
		ANCHORTYPE_RIGHTSIDE,
		ANCHORTYPE_MAX
	};

	//****************************
	// �`��^�C�v
	//****************************
	enum DRAWTYPE
	{
		DRAWTYPE_NONE,
		DRAWTYPE_ANIM,
		DRAWTYPE_MAX,
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CObject2D(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CObject2D();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CObject2D* Create(void);

	// �Z�b�^�[
	void SetUV(float TexU, float TexV);
	void SetCol(D3DXCOLOR col) { m_col = col; }
	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_Rot = rot; }
	void SetSize(float fWidth, float fHeight) { m_fWidth = fWidth, m_fHeight = fHeight; }
	void SetWidth(float fWidth) { m_fWidth = fWidth; }
	void SetHeight(float fHeight) { m_fWidth = fHeight; }
	void SetFlash(const int nFirstcount, const int nEndcount,const D3DXCOLOR col);
	void SetAnchor(int Type) { m_nAnchorType = Type; }
	void SetDrawType(int nType) { m_nDrawType = nType; }
	void SetCenter(void);
	void SetLeft(void);
	void SetRight(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_Pos; }	// ���݂̍��W���擾
	D3DXVECTOR3 GetRot(void) { return m_Rot; }	// ���݂̊p�x���擾
	D3DXCOLOR GetCol(void) { return m_col; }	// ���݂̐F���擾
	float GetWidth(void) { return m_fWidth; }
	float GetHeight(void) { return m_fHeight; }
	int GetDrawType(void) { return m_nDrawType; }

private:

	LPDIRECT3DTEXTURE9 m_pTexture;		// �e�N�X�`���|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff; // ���_�o�b�t�@�̃|�C���^

	D3DXVECTOR3 m_Rot;	// �p�x���
	D3DXVECTOR3 m_Pos;	// ���W���
	D3DXCOLOR m_col;	// �F���

	int m_nAnchorType;	// ����W�ݒ�
	int m_nColorCount;	// �_�ŃJ�E���g
	int m_nDrawType;	// �`��^�C�v
	float m_fWidth;		// ����
	float m_fHeight;	// ����
};

#endif