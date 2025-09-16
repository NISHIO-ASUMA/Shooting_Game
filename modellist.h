//=======================================
//
// ���f���t�@�C�����X�g [ modellist.h ]
// Author: Asuma Nishio
//
//=======================================

#ifndef _MODELLIST_H_ // ���̃}�N����`������ĂȂ�������
#define _MODELLIST_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include <vector>

//**********************
// �ǂݍ��݃N���X���`
//**********************
class CModelList
{
public:
	//*************************
	// ���ۑ��p�\����
	//************************* 
	struct MODELINFO
	{
		LPD3DXMESH pMesh;		// ���b�V���̃|�C���^
		LPD3DXBUFFER pBuffMat;	// �}�e���A���̃|�C���^
		DWORD dwNumMat;			// �}�e���A����
		std::vector<int>pTexture; // �e�N�X�`���̓��I�|�C���^
		char FileName[MAX_WORD];		// ������
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CModelList();
	~CModelList();

	// �ÓI�����o�֐�
	static void Load(void);
	static void UnLoad(void);
	static MODELINFO GetInfo(const int Indx) { return m_ModelInfo[Indx]; };
	static std::vector <MODELINFO> GetInfo() { return m_ModelInfo; }

private:
	static std::vector<MODELINFO>m_ModelInfo; // ���I�z��
	static constexpr const char* MODELLIST = "data\\Loader\\ModelFile.txt"; // �t�@�C���p�X

};

#endif