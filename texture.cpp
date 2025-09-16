//=====================================
//
// �e�N�X�`������ [ texture.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "texture.h"
#include "manager.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

//**********************
// �ÓI�����o�ϐ�
//**********************
int CTexture::m_nNumAll = NULL;	// �����Ǘ�

//===============================
// �R���X�g���N�^
//===============================
CTexture::CTexture()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		m_apTexture[nCnt] = nullptr;
	}
}
//===============================
// �f�X�g���N�^
//===============================
CTexture::~CTexture()
{
	// ����
}
//===============================
// �e�N�X�`���ǂݍ���
//===============================
HRESULT CTexture::Load(void)
{
#if 1
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���ׂẴe�N�X�`������
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// �t�@�C�����������Ȃ�X�L�b�v
		if (TexName[nCnt] == nullptr)
			continue;

		// �񋓌^�̕��ǂݍ���
		if (FAILED(D3DXCreateTextureFromFile(pDevice, TexName[nCnt], &m_apTexture[nCnt])))
		{
			// �x���\��
			MessageBox(NULL, "�e�N�X�`���p�X�����݂��܂���", TexName[nCnt], MB_OK);

			return E_FAIL;
		}

		// ���Z����
		m_nNumAll++;
	}
#endif

	// ���ʂ�Ԃ�
	return S_OK;

}
//===============================
// �e�N�X�`���j��
//===============================
void CTexture::UnLoad(void)
{
	// ���ׂẴe�N�X�`���̔j��
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		if (m_apTexture[nCnt] != nullptr)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = nullptr;
		}
	}
}
//===============================
// �e�N�X�`���ԍ���o�^����
//===============================
int CTexture::Register(const char* pFileName)
{
	for (int nCnt = 0; nCnt < NUM_TEXTURE; nCnt++)
	{
		// nullptr�`�F�b�N
		if (TexName[nCnt] != nullptr)
		{
			// �t�@�C���p�X������v���Ă�����
			if (strcmp(pFileName, TexName[nCnt]) == 0)
			{
				// �ԍ���Ԃ�
				return nCnt;
			}
		}
	}

	// �e�N�X�`�����Ȃ��ꍇ
	return -1;
}
//===============================
// �e�N�X�`���ԍ��擾
//===============================
LPDIRECT3DTEXTURE9 CTexture::GetAddress(int nIdx)
{
	// ��O����
	if (nIdx < 0 || nIdx >= NUM_TEXTURE) return nullptr;

	// �e�N�X�`���ԍ����擾
	return m_apTexture[nIdx];
}
//===============================
// �e�N�X�`���O���ǂݍ��ݏ���
//===============================
void CTexture::TextLoader(const char* pFileName)
{
	// �t�@�C���ݒ�
	std::ifstream file(pFileName);

	// �t�@�C����O�`�F�b�N
	if (!file)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", pFileName, MB_OK);
		// ���s���ʂ�Ԃ�
		return;
	}

	// ��s�ǂݍ���
	std::string line;

	int nIdx = 0;

	while (std::getline(file, line))
	{
		// �R�����g�s���s���X�L�b�v
		if (line.empty() || line[0] == '#')
			continue;

		// "FILENAME =" ��T��
		const std::string key = "FILENAME =";
		size_t pos = line.find(key);

		if (pos == std::string::npos)
			continue;

		// �_�u���N�H�[�g�ň͂܂ꂽ�����𒊏o
		size_t firstQuote = line.find('"', pos);
		size_t lastQuote = line.find_last_of('"');

		if (firstQuote != std::string::npos && lastQuote != std::string::npos && lastQuote > firstQuote)
		{
			std::string path = line.substr(firstQuote + 1, lastQuote - firstQuote - 1);

			if (nIdx < NUM_TEXTURE)
			{
				// strdup�ŃR�s�[���Ċi�[
				TexName[nIdx] = _strdup(path.c_str());

				// �C���f�b�N�X�ԍ������Z
				nIdx++;
			}
		}
	}

	// �t�@�C�������
	file.close();
}
