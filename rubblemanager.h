//=================================================
//
// ���I�I�u�W�F�N�g�Ǘ����� [ rubblemanager.h ]
// Author : Asuma Nishio
//
//=================================================

#ifndef _RUBBLEMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _RUBBLEMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubble.h"
#include <vector>
#include <string>

//**********************************
// ���I�Ǘ��N���X���`
//**********************************
class CRubbleManager
{
public:
	//*************************
	// �g���t�@�C���p�X�̎��
	//*************************
	enum FILETYPE
	{
		FILETYPE_SMALL,		// ���Ȃ�
		FILETYPE_MEDIUM,	// ����
		FLIETYPE_lARGE,		// ����
		FILETYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CRubbleManager();
	~CRubbleManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void LoadAllList(const char * pFileList);
	void LoadSplitFile(int type);

	// �ÓI�����o�֐�
	static CRubble* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	static const std::vector<CRubble*>& GetRubbles() { return m_rubbles; } // �z��擾

private:
	static std::vector<CRubble*> m_rubbles; // ���I�z��
	static int m_nIdxCount;					// ���f���C���f�b�N�X�ԍ�
	static constexpr const char* FILEPASS = "data\\Loader\\AllRubbleList.txt"; // �t�@�C���p�X

	std::vector<std::string> m_SubListFiles;	// AllRubbleList����ǂݍ��񂾃t�@�C���Q
	int m_nUseType;								// �g�����
};

#endif
