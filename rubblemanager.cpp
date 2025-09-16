//=================================================
//
// ���I�I�u�W�F�N�g�Ǘ����� [ rubblemanager.cpp ]
// Author : Asuma Nishio
//
//=================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubblemanager.h"
#include <fstream>
#include <iostream>
#include <sstream>

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
std::vector<CRubble*>CRubbleManager::m_rubbles = {}; // ���I�z��
int CRubbleManager::m_nIdxCount = NULL;	// �C���f�b�N�X�J�E���g

//=====================================
// �R���X�g���N�^
//=====================================
CRubbleManager::CRubbleManager()
{
	// �l�̃N���A
	m_rubbles.clear();
	m_SubListFiles.clear();
	m_nUseType = FILETYPE_SMALL;
}
//=====================================
// �f�X�g���N�^
//=====================================
CRubbleManager::~CRubbleManager()
{
	// ����
}
//=====================================
// ��������
//=====================================
CRubble* CRubbleManager::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CRubble* pNewRubble = CRubble::Create(pos, rot, pFilename);

	// �C���X�^���X�̐������ł�����
	if (pNewRubble)
	{
		// �z��ɒǉ�
		m_rubbles.push_back(pNewRubble);

		// �C���f�b�N�X
		m_nIdxCount++;

		// �������ꂽ�|�C���^��Ԃ�
		return pNewRubble;
	}
	else
	{
		// ���ɂ��Ȃ��|�C���^��Ԃ�
		return nullptr;
	}
}

//=====================================
// ����������
//=====================================
HRESULT CRubbleManager::Init(void)
{
	// �l�̃N���A
	m_rubbles.clear();
	m_SubListFiles.clear();

	// �S���X�g�t�@�C���ǂݍ���
	CRubbleManager::LoadAllList(FILEPASS);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=====================================
// �I������
//=====================================
void CRubbleManager::Uninit(void)
{
	// �l�̃N���A
	m_rubbles.clear();
	m_SubListFiles.clear();
}
//=====================================
// �X�V����
//=====================================
void CRubbleManager::Update(void)
{
	// ����
}
//=====================================
// �S�t�@�C�����X�g�ǂݍ��ݏ���
//=====================================
void CRubbleManager::LoadAllList(const char* pFileList)
{
	// �w��t�@�C�����J��
	std::ifstream loadFile(pFileList);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", pFileList, MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumFile = NULL;

	// �z��̃N���A����
	m_SubListFiles.clear();

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_FILE")
		{// "NUM_FILE"�ǂݎ�莞

			// "="�̎�
			std::string eq;

			// ���
			iss >> eq >> nNumFile;

			// �t�@�C���z��̃T�C�Y���m��
			m_SubListFiles.reserve(nNumFile);

		}
		else if (token == "FILENAME")
		{// "FILENAME"�ǂݎ�莞
			// �p�X��"="����
			std::string eq, filepath;

			// �t�@�C���p�X��ϐ��Ɋi�[
			iss >> eq >> filepath;

			// ���I�z��ɒǉ�
			m_SubListFiles.push_back(filepath);
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//=====================================
// �����t�@�C���ǂݍ��ݏ���
//=====================================
void CRubbleManager::LoadSplitFile(int type)
{
	// ��ޔԍ���0�ȉ� �܂��� �t�@�C���T�C�Y�𒴉߂���Ƃ�
	if (type < 0 || type >= m_SubListFiles.size()) return;

	// �ǂݍ��ރt�@�C���̃^�C�v��ۑ�����
	const std::string& FilePath = m_SubListFiles[type];

	// �t�@�C�����J��
	std::ifstream loadFile(FilePath);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		// ���b�Z�[�W�{�b�N�X�\��
		MessageBox(NULL, "�t�@�C���I�[�v�����s", FilePath.c_str(), MB_OK);

		// �����I��
		return;
	}

	// ���[�J���ϐ��錾
	std::string line;
	int nNumRubbles = NULL;

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �s�ǂݍ���
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_RUBBLES")
		{// NUM_RUBBLES�ǂݎ��

			// "="�̎�
			std::string eq;

			// �l����
			iss >> eq >> nNumRubbles;

			// while�I��
			break;
		}
	}

	// �ǂݍ��񂾃I�u�W�F�N�g���ǂݍ���
	for (int nCnt = 0; nCnt < nNumRubbles; nCnt++)
	{
		// ���[�J���ϐ��錾
		D3DXVECTOR3 pos = VECTOR3_NULL;
		D3DXVECTOR3 rot = VECTOR3_NULL;
		std::string filePath;

		// �����\�t���O
		bool inSetting = false;

		// �ǂݍ��ݏI���܂ŉ�
		while (std::getline(loadFile, line))
		{
			// �R�����g�̕�����������
			if (line.empty() || line[0] == '#') continue;

			// �s�ǂݍ���
			std::istringstream iss(line);
			std::string token;
			iss >> token;

			if (token == "SETTING")
			{// "SETTING"�ǂݎ�莞

				// �����t���O��L����
				inSetting = true;
			}
			else if (token == "POS")
			{// "POS"�ǂݎ�莞

				// "="�̎�
				std::string eq;

				// �l����
				iss >> eq >> pos.x >> pos.y >> pos.z;
			}
			else if (token == "ROT")
			{// "ROT"�ǂݎ�莞

				// "="�̎�
				std::string eq;

				// �l����
				iss >> eq >> rot.x >> rot.y >> rot.z;
			}
			else if (token == "FILEPASS")
			{// "FILEPASS"�ǂݎ�莞

				// "="�̎�
				std::string eq;

				// �t�@�C���p�X���i�[
				iss >> eq >> filePath;
			}
			else if (token == "END_SETTING" && inSetting)
			{// "END_SETTING"�ǂݎ�莞 ���� �����t���O���L���Ȃ�

				// �I�u�W�F�N�g����
				CRubbleManager::Create(pos, rot, filePath.c_str());

				break; // ���̃I�u�W�F�N�g��
			}
		}
	}

	// �t�@�C�������
	loadFile.close();
}