//============================================
//
// �G�f�B�^�[�V�[���Ǘ����� [ editmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _EDITMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _EDITMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "modellist.h"

//**********************************
// �O���錾
//**********************************
class CRubble;
class CMapManager;
class CShadow;

//**********************************
// �G�f�B�^�[�Ǘ��N���X���`
//**********************************
class CEditManager
{
public:
	//=====================
	// �����o���p�X�̎��
	//=====================
	enum SAVEPASS
	{
		SAVEPASS_SMALL,
		SAVEPASS_MEDIUM,
		SAVEPASS_LARGE,
		SAVEPASS_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CEditManager();
	~CEditManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);
	void Reload(void);

	// �Z�b�^�[
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }


private:
	//*******************************
	// �t�@�C���p�X���i�[���郊�X�g
	//*******************************
	const char* FILELIST[SAVEPASS_MAX] =
	{
		"data\\Loader\\RubbleList_small.txt",
		"data\\Loader\\RubbleList_medium.txt",
		"data\\Loader\\RubbleList_large.txt",
	};

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;

	CMapManager* m_pMapManager; // �}�l�[�W���[�|�C���^
	CShadow* m_pShadow;

	int m_nTypeIdx; // �C���f�b�N�X
	int m_nSelectIndex; // �I�𒆃I�u�W�F�N�g�̃C���f�b�N�X
	int m_nSavePassIdx;
	int m_nNumAll;		// ������
};

#endif
