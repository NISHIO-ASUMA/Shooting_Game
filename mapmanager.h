//========================================
//
// �}�b�v�}�l�[�W���[���� [ mapmanager.h ]
// Author : Asuma Nishio
//
//========================================

#ifndef _MAPMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _MAPMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C��
//***************************
#include "object.h"
#include <vector>

//***************************
// �O���錾
//***************************
class CMapObject;

//***************************
// �}�b�v�}�l�[�W���[�N���X
//***************************
class CMapManager : CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CMapManager(int nPriority = static_cast<int>(CObject::PRIORITY::MODELOBJECT));
	~CMapManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PushBack(CMapObject* pMapOjbect) { m_MapObj.push_back(pMapOjbect); };

	// �Q�b�^�[
	CMapObject* GetInfo(const int nIdx) { return m_MapObj[nIdx]; }
	int GetSize() const { return (int)m_MapObj.size(); }

	// �ÓI�����o�֐�
	static CMapManager* Craete(void);

private:
	std::vector<CMapObject*>m_MapObj;

};

#endif
