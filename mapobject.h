//================================================
//
// �}�b�v�ɏo���I�u�W�F�N�g���� [ mapobject.h ]
// Author: Asuma Nishio
//
//================================================

#ifndef _MAPOBJECT_H_ // ���̃}�N����`������ĂȂ�������
#define _MAPOBJECT_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "object.h"

//*********************************
// �}�b�v�I�u�W�F�N�g�N���X���`
//*********************************
class CMapObject : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMapObject(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CMapObject();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXMATRIX GetMtx(void) { return m_mtxworld; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }
	int GetIdx() const { return m_nIdx; }

	// �ÓI�����o�֐�
	static CMapObject* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nIdx);

private:
	int m_nIdx; // �C���f�b�N�X
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;
};

#endif