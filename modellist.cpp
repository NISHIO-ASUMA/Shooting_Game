//=========================================
//
// ���f���t�@�C�����X�g [ modellist.cpp ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "modellist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "manager.h"

//****************************
// �ÓI�����o�ϐ��錾
//****************************
std::vector<CModelList::MODELINFO> CModelList::m_ModelInfo = {}; // ���I���X�g

//======================
// �R���X�g���N�^
//======================
CModelList::CModelList()
{
	// 
}
//======================
// �f�X�g���N�^
//======================
CModelList::~CModelList()
{
	// ����
}
//=========================
// ���f�����ǂݍ��ݏ���
//=========================
void CModelList::Load(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �w��t�@�C�����J��
	std::ifstream loadFile(MODELLIST);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", MODELLIST, MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumFile = NULL;
	int nCnt = 0;

	// �z��̃N���A����
	m_ModelInfo.clear();

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_MODELFILE")
		{// "NUM_FILE"�ǂݎ�莞

			// "="�̎�
			std::string eq;

			// ���
			iss >> eq >> nNumFile;

			// 
			m_ModelInfo.resize(nNumFile);
		}
		else if (token == "FILENAME")
		{// "FILENAME"�ǂݎ�莞

			// �t�@�C����
			std::string eq, filepath;

			iss >> eq >> filepath;

			// ������擾
			strncpy_s(m_ModelInfo[nCnt].FileName, filepath.c_str(), sizeof(m_ModelInfo[nCnt].FileName) - 1);

			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(m_ModelInfo[nCnt].FileName,
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&m_ModelInfo[nCnt].pBuffMat,
				NULL,
				&m_ModelInfo[nCnt].dwNumMat,
				&m_ModelInfo[nCnt].pMesh);

			// �}�e���A���f�[�^�ւ̃|�C���^
			D3DXMATERIAL* pMat = nullptr;

			// �}�e���A���f�[�^�ւ̃|�C���^���擾
			pMat = (D3DXMATERIAL*)m_ModelInfo[nCnt].pBuffMat->GetBufferPointer();

			// �e�N�X�`���C���f�b�N�X�z��
			m_ModelInfo[nCnt].pTexture.resize(m_ModelInfo[nCnt].dwNumMat);

			// �}�e���A����������
			for (int nCntMat = 0; nCntMat < (int)m_ModelInfo[nCnt].dwNumMat; nCntMat++)
			{
				// �e�N�X�`�����ǂݍ��߂���
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���|�C���^�擾
					CTexture* pTexture = CManager::GetTexture();

					// �e�N�X�`���Z�b�g
					int texID = pTexture->Register(pMat[nCntMat].pTextureFilename);

					// �e�N�X�`�������i�[
					m_ModelInfo[nCnt].pTexture[nCntMat] = texID;
				}
				else
				{
					// �e�N�X�`���Ȃ�
					m_ModelInfo[nCnt].pTexture[nCntMat] = -1;
				}
			}

			// �C���N�������g
			nCnt++;
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//======================
// �j��
//======================
void CModelList::UnLoad(void)
{
	for (auto iter = m_ModelInfo.begin(); iter != m_ModelInfo.end(); iter++)
	{
		if ((*iter).pMesh != nullptr)
		{
			(*iter).pMesh->Release();
			(*iter).pMesh = nullptr;
		}
		if ((*iter).pBuffMat != nullptr)
		{
			(*iter).pBuffMat->Release();
			(*iter).pBuffMat = nullptr;
		}

		(*iter).pTexture.clear();

		if ((*iter).FileName != NULL)
		{
			ZeroMemory(&((*iter).FileName), sizeof((*iter).FileName));
		}

		if ((*iter).dwNumMat != NULL)
		{
			(*iter).dwNumMat = 0;
		}
	}

	// �z��N���A
	m_ModelInfo.clear();
}