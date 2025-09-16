//============================================
//
// ���b�V���t�B�[���h���� [ meshfield.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _MESHFIELD_H_ // ���̃}�N����`������ĂȂ�������
#define _MESHFIELD_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************************
// ���b�V���t�B�[���h�N���X���`
//**********************************
class CMeshField : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMeshField(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshField();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }

	// �ÓI�����o�֐�
	static CMeshField* Create(D3DXVECTOR3 pos, float fRadius);
private:
	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_fRadius;

	int m_nNumPrimitive;	// �v���~�e�B�u��
	int m_nNumIdx;			// �C���f�b�N�X��
	int m_nNumAllVtx;		// �S�̒��_��

	int m_nTexIdx;
};
#endif
