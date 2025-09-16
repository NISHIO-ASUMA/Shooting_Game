//=========================================
//
// UI�S�̂��Ǘ����鏈�� [ uimanager.cpp ]
// Author: Asuma Nishio
//
//=========================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "uimanager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//****************************
// ���O���
//****************************
namespace UIINFO
{
	const char* FILEPASS = "data\\Loader\\GameUi.txt"; // �t�@�C���p�X
}

//****************************
// �ÓI�����o�ϐ��錾
//****************************
int CUimanager::m_nIdxUi = NULL; // ���z�u��
std::vector<CUi*>CUimanager::m_aUidata = {}; // ���I�z��

//===============================
// �R���X�g���N�^
//===============================
CUimanager::CUimanager()
{
	// �l�̃N���A
	m_aUidata.clear();
}
//===============================
// �f�X�g���N�^
//===============================
CUimanager::~CUimanager()
{
	// ����
}
//===============================
// ����������
//===============================
HRESULT CUimanager::Init(void)
{
	// �t�@�C�����[�h�֐�
	CUimanager::Load(UIINFO::FILEPASS);

	return S_OK;
}
//===============================
// �I������
//===============================
void CUimanager::Uninit(void)
{
	// �l�̃N���A
	m_aUidata.clear();
}
//===============================
// �X�V����
//===============================
void CUimanager::Update(void)
{
	// ����
}
//===============================
// �e�L�X�g�ǂݍ��ݏ���
//===============================
void CUimanager::Load(const char* pFileName)
{
	// �ǂݍ��ރt�@�C���p�X��ݒ�
	std::ifstream loadFile(pFileName);

	// �t�@�C����O�`�F�b�N
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", pFileName, MB_OK);

		// ���s���ʂ�Ԃ�
		return;
	}

	// ��s���ǂݍ��ޕϐ�
	std::string loadline;

	// �����ݒ�
	int nNumAll = 0;

	// �������ǂݑ�����
	while (std::getline(loadFile, loadline))
	{
		// �g�[�N���ݒ�
		std::istringstream Stringname(loadline);
		std::string Token;
		Stringname >> Token;

		// "NUM_UI"�ǂݎ�莞
		if (Token == "NUM_UI")
		{
			// ������ݒ�
			std::string eq;

			// �ǂݍ��񂾃��f������ݒ�
			Stringname >> eq >> nNumAll;
		}
		// "SET_UI"�ǂݎ�莞
		else if (Token == "SET_UI")
		{
			// 2D�I�u�W�F�N�g�̐ݒ�
			SetObjectUi(loadFile);

			// �C���f�b�N�X�J�E���g�����Z
			m_nIdxUi++;
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//===============================
// UI�I�u�W�F�N�g�����֐�����
//===============================
void CUimanager::SetObjectUi(std::ifstream& file)
{
	// �s�ǂݍ��ݐݒ�
	std::string line;

	// �g�p���[�J���ϐ�
	D3DXVECTOR3 pos = VECTOR3_NULL;
	float fWidth = 0.0f;
	float fHeight = 0.0f;
	int nAnchorType = 0;

	// �e�N�X�`���p�X�i�[
	std::string texturePath;

	// ����̕���������܂œǂ�
	while (std::getline(file, line))
	{
		// �g�[�N���ݒ�
		std::istringstream iString(line);
		std::string Token;
		iString >> Token;

		// "="�̔�΂�
		std::string eqal;

		if (Token == "POS")
		{// "POS"�ǂݎ�莞

			// ���W�ݒ�
			iString >> eqal >> pos.x >> pos.y >> pos.z;
		}
		else if (Token == "WIDTH")
		{// "WIDTH"�ǂݎ�莞

			// �����ݒ�
			iString >> eqal >> fWidth;
		}
		else if (Token == "HEIGHT")
		{// "HEIGHT"�ǂݎ�莞

			// �����ݒ�
			iString >> eqal >> fHeight;
		}
		else if (Token == "ANCHORTYPE")
		{// "ANCHORTYPE"�ǂݎ�莞

			// ���_������ނ�ݒ�
			iString >> eqal >> nAnchorType;
		}
		else if (Token == "TEXTURE_PASS")
		{// "TEXTURE_PASS"�ǂݎ�莞

			size_t equalPos = line.find('=');

			if (equalPos != std::string::npos)
			{
				texturePath = line.substr(equalPos + 1);

				// �󔒏���
				texturePath.erase(0, texturePath.find_first_not_of(" \t"));
				texturePath.erase(texturePath.find_last_not_of(" \t") + 1);

				// �R�����g�폜
				size_t commentPos = texturePath.find('#');
				if (commentPos != std::string::npos)
				{
					texturePath = texturePath.substr(0, commentPos);
					texturePath.erase(texturePath.find_last_not_of(" \t") + 1);
				}

				// �N�H�[�e�[�V�����폜
				if (!texturePath.empty() && texturePath.front() == '"') 
				{
					texturePath.erase(0, 1); // �擪�� " ���폜
				}
				if (!texturePath.empty() && texturePath.back() == '"') 
				{
					texturePath.pop_back();  // ������ " ���폜
				}
			}
		}
		else if (Token == "END_SETUI")
		{// "END_SETUI"�ǂݎ�莞

			//// ������UI��������
			//CUi* pUi = CUi::Create(pos,fWidth, fHeight, texturePath.c_str(),nAnchorType);

			//// null����Ȃ�������
			//if (pUi != nullptr)
			//{
			//	// �z��ɒǉ�
			//	m_aUidata.push_back(pUi);
			//}

			break;
		}
	}
}