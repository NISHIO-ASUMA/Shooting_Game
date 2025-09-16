//===============================================
//
// UI�G�f�B�^�[�I�u�W�F�N�g [ uiobject.h ]
// Author : Asuma Nishio
// 
// TODO : �Ƃō�Ƃ���
//
//===============================================

#ifndef _UIOBJECT_H_ // ���̃}�N����`������ĂȂ�������
#define _UIOBJECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "object2D.h"

//**********************************
// UI�I�u�W�F�N�g�N���X���`
//**********************************
class CUiObject : public CObject2D
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CUiObject(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUiObject();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	int GetIdx() const { return m_nIdx; }

	// �ÓI�����o�֐�
	static CUiObject* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float fWidth,float fHeight,int nIdx);

private:
	int m_nIdx;			// �C���f�b�N�X
	float m_fWidth;		// ����
	float m_fHeight;	// ����
	D3DXVECTOR3 m_pos;	// ���W
	D3DXVECTOR3 m_rot;	// �p�x
};

#endif
