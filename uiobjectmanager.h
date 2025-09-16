//=========================================================
//
// UI�G�f�B�^�[�I�u�W�F�N�g�Ǘ����� [ uiobjectmanager.h ]
// Author : Asuma Nishio
// 
// TODO : �Ƃō�Ƃ���
//
//=========================================================

#ifndef _UIOBJECTMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _UIOBJECTMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "object.h"
#include <vector>

//***************************
// �O���錾
//***************************
class CUiObject;

//**********************************
// �Ǘ��N���X���`
//**********************************
class CUiObjectManager : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CUiObjectManager(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CUiObjectManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void PushBack(CUiObject* pMapOjbect) { m_UiObj.push_back(pMapOjbect); };

	// �Q�b�^�[
	CUiObject* GetInfo(const int nIdx) { return m_UiObj[nIdx]; }
	int GetSize() const { return (int)m_UiObj.size(); }

	// �ÓI�����o�֐�
	static CUiObjectManager* Craete(void);

private:
	std::vector<CUiObject*>m_UiObj;	// ���I���X�g
};

#endif