//====================================
//
// ���b�V���h�[������ [ meshdome.h ]
// Author: Asuma Nishio
//
//====================================

#ifndef _MESHDONE_H_ // ���̃}�N����`������ĂȂ�������
#define _MESHDONE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"

//**********************************
// ���b�V���h�[���N���X���`
//**********************************
class CMeshDome : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMeshDome(int nPrio = static_cast<int>(CObject::PRIORITY::MESH));
	~CMeshDome();

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
	static CMeshDome* Create(D3DXVECTOR3 pos, float nRadius);

private:

	static constexpr int MeshDome_X_BLOCK = 10;		// X�u���b�N��
	static constexpr int MeshDome_Z_BLOCK = 10;		// Z�u���b�N��
	static constexpr int MeshDome_VERTEX_NUM = (MeshDome_X_BLOCK + 1) * (MeshDome_Z_BLOCK + 1); // ���_��
	static constexpr int MeshDome_INDEX_NUM = MeshDome_X_BLOCK * MeshDome_Z_BLOCK * 6;			// �C���f�b�N�X��
	static constexpr int MeshDome_PRIMITIVE_NUM = (MeshDome_X_BLOCK * MeshDome_Z_BLOCK * 2) + ((MeshDome_Z_BLOCK - 1) * 2); // �|���S����

	LPDIRECT3DINDEXBUFFER9 m_pIdx; // �C���f�b�N�X�o�b�t�@
	LPDIRECT3DVERTEXBUFFER9 m_pVtx;	// ���_�o�b�t�@

	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxWorld;	// ���[���h�}�g���b�N�X
	float m_nRadius;		// ���a
	int m_nTexIdx;
};


#endif