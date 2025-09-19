//====================================================
//
// �V�[���t�@�C���ǂݍ��ݏ��� [ sceneloader.cpp ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "sceneloader.h"
#include "meshdome.h"
#include "meshfield.h"
#include "meshimpact.h"
#include "block.h"
#include "player.h"
#include "playerlifegage.h"
#include "bosslifegage.h"
#include "charge.h"
#include "ui.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

//=================================
// �R���X�g���N�^
//=================================
CSceneLoader::CSceneLoader()
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CSceneLoader::~CSceneLoader()
{
	// ����
}
//=================================
// ��������
//=================================
void CSceneLoader::SplitLoad(int nIdx)
{
	// �w��t�@�C�����J��
	std::ifstream loadFile(m_aFileList[nIdx]);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", m_aFileList[nIdx], MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;

	// �ǂݍ��񂾖��O
	std::string objName, motionPath, filePath, createType,TexPath;

	// �ǂݍ��ݏ��i�[
	D3DXVECTOR3 pos = VECTOR3_NULL;
	D3DXVECTOR3 rot = VECTOR3_NULL;
	int life = 0;
	int index = -1, type = -1, category = -1;
	int nFlashFrame = 0;
	int nUse = 0;
	float radius = 0.0f;
	float size = 0.0f;
	float width = 0.0f;
	float height = 0.0f;

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �R�����g��΂�
		if (line.empty() || line[0] == '#') continue;

		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "OBJNAME")
		{// "FILENAME"�ǂݎ�莞

			// �ϐ��̏�����
			objName.clear(); 
			motionPath.clear(); 
			filePath.clear(); 
			createType.clear();
			TexPath.clear();

			pos = VECTOR3_NULL;
			rot = VECTOR3_NULL;
			life = nFlashFrame = nUse = 0;
			radius = size = width = height = 0.0f;
			index = type = category = -1;

			// "="���i�[
			std::string eq;

			// OBJNAME��ǂݎ��
			iss >> eq >> objName;
		}
		else if (token == "POS")
		{// ���W���
			// "="���i�[
			std::string eq;

			// �ǂݎ�������W�����Z�b�g
			iss >> eq >> pos.x >> pos.y >> pos.z;
		}
		else if (token == "ROT")
		{// �p�x���
			// "="���i�[
			std::string eq;

			// �ǂݎ�����p�x�����Z�b�g
			iss >> eq >> rot.x >> rot.y >> rot.z;
		}
		else if (token == "LIFE")
		{// �̗̓p�����[�^�[���
			// "="���i�[
			std::string eq;

			// �ǂݎ���������Z�b�g
			iss >> eq >> life;
		}
		else if (token == "INDEX")
		{// �C���f�b�N�X���
			// "="���i�[
			std::string eq;

			// �ǂݎ�������ʔԍ������Z�b�g
			iss >> eq >> index;
		}
		else if (token == "MOTIONPASS")
		{// ���[�V�����e�L�X�g�p�X���
			// "="���i�[
			std::string eq;

			// �ǂݎ�����e�L�X�g�t�@�C�������Z�b�g
			iss >> eq >> motionPath;
		}
		else if (token == "XFILEPASS")
		{// X�t�@�C�����
			// "="���i�[
			std::string eq;

			// �ǂݍ���X�t�@�C�������Z�b�g
			iss >> eq >> filePath;
		}
		else if (token == "TEXNAME")
		{// �e�N�X�`���p�X���
			// "="���i�[
			std::string eq;

			// �ǂݍ��񂾃e�N�X�`�������Z�b�g
			iss >> eq >> TexPath;
		}
		else if (token == "TYPE")
		{// ��ޏ��
			// "="���i�[
			std::string eq;

			// �ǂݍ��񂾎�ޏ����Z�b�g
			iss >> eq >> type;
		}
		else if (token == "RADIUS")
		{// ���a���
			// "="���i�[
			std::string eq;

			// �ǂݎ�������a�����Z�b�g
			iss >> eq >> radius;
		}
		else if (token == "SIZE")
		{// �傫�����
			// "="���i�[
			std::string eq;

			// �ǂݎ�����傫�������Z�b�g
			iss >> eq >> size;
		}
		else if (token == "CREATETYPE")
		{// �J�e�S���[��ޏ��
			// "="���i�[
			std::string eq;

			// �ǂݎ�����J�e�S���[�����Z�b�g
			iss >> eq >> createType;
		}
		else if (token == "WIDTH")
		{// �������
			// "="���i�[
			std::string eq;

			// �ǂݎ�������������Z�b�g
			iss >> eq >> width;
		}
		else if (token == "HEIGHT")
		{// �������
			// "="���i�[
			std::string eq;

			// �ǂݎ�������������Z�b�g
			iss >> eq >> height;
		}
		else if (token == "CATEGORY")
		{// �J�e�S���[�̓�����
			// "="���i�[
			std::string eq;

			// �ǂݎ����������Z�b�g
			iss >> eq >> category;
		}
		else if (token == "STARTFRAME")
		{// �t���[�����
			// "="���i�[
			std::string eq;

			// �ǂݎ�����l���Z�b�g
			iss >> eq >> nFlashFrame;
		}
		else if (token == "USE")
		{// �_�ł��ǂ���
			// "="���i�[
			std::string eq;

			// �ǂݎ�����l���Z�b�g
			iss >> eq >> nUse;
		}
		else if (token == "ENDSET")
		{// �ŏI�ǂݎ��
			// �e�퐶��
			if (objName == "PLAYER")
			{
				// �Q�[���v���C���[
				CPlayer::Create(pos, rot, life, index, motionPath.c_str());

				// �p�X�̃N���A
				motionPath.clear();
			}
			else if (objName == "MESH")
			{
				if (type == 0) CMeshDome::Create(pos, radius); 	// ���b�V���h�[��
				else if (type == 1) CMeshField::Create(pos, radius); // ���b�V���t�B�[���h
			}
			else if (objName == "BLOCK")
			{
				// �u���b�N
				CBlock::Create(filePath.c_str(), pos, rot, size,type);

				// �p�X�̃N���A
				filePath.clear();
			}
			else if (objName == "UI")
			{// UI���
				if (createType == "PLAYER")
				{
					// �̗̓Q�[�W
					CPlayerLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "BOSS")
				{
					// �̗̓Q�[�W
					CBossLifeGage::Create(pos, width, height, category);
				}
				else if (createType == "LASER")
				{
					// ���[�U�[�Q�[�W
					CCharge::Create(pos, width, height, category);
				}
				else if (createType == "BACEUI")
				{
					// UI����
					CUi::Create(pos, nFlashFrame,width,height, TexPath.c_str(),nUse);

					// �p�X�̃N���A
					TexPath.clear();
				}
			}
		}
	}

	// �t�@�C�������
	loadFile.close();
}