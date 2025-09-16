//=============================================
//
// �`���[�g���A���^�X�N���� [ tutotask.cpp ]
// Author: Asuma Nishio
//
//=============================================

//******************************
// �C���N���[�h�t�@�C���錾
//******************************
#include "tutotask.h"
#include "manager.h"
#include "player.h"
#include "tutorialui.h"
#include <fstream>
#include <iostream>
#include <sstream>

//******************************
// ���O���
//******************************
namespace TASKS
{
	constexpr const char* FILENAME = "data\\SceneText\\TutoUi.txt"; // �t�@�C����
}
//================================
// �R���X�g���N�^
//================================
CTutoTask::CTutoTask()
{
	// �l�̃N���A
	m_pTutoUi.clear();
	m_Info = {};
	m_pCurrentUi = nullptr;
	m_nCurrentIndex = NULL;
}
//================================
// �f�X�g���N�^
//================================
CTutoTask::~CTutoTask()
{
	// ����
}
//================================
// ����������
//================================
HRESULT CTutoTask::Init(void)
{
	// �l�̃N���A
	m_pTutoUi.clear();

	// �ǂݍ���
	Load();

	if (!m_pTutoUi.empty())
	{
		// �ŏ��ɕ\������UI�𐶐�
		CreateTaskUi(m_nCurrentIndex);
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CTutoTask::Uninit(void)
{
	// ���I�z����N���A
	m_pTutoUi.clear();
}
//================================
// �X�V����
//================================
void CTutoTask::Update(void)
{
	// null�Ȃ珈����ʂ��Ȃ�
	if (m_pCurrentUi == nullptr) return;

	// �t�F�[�h�A�E�g������
	if (m_pCurrentUi->IsFinished())
	{
		// null�ɂ���
		m_pCurrentUi = nullptr;

		// �C���f�b�N�X�ԍ������Z
		m_nCurrentIndex++;

		// �z��I�[�o�[���Ă��Ȃ����
		if (m_nCurrentIndex < (int)m_pTutoUi.size())
		{
			// �^�X�N����
			CreateTaskUi(m_nCurrentIndex);
		}
	}
}
//================================
// �ǂݍ��ݏ���
//================================
void CTutoTask::Load(void)
{
	// �w��t�@�C�����J��
	std::ifstream loadFile(TASKS::FILENAME);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!loadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", TASKS::FILENAME, MB_OK);

		return;
	}

	// ���[�J���ϐ�
	std::string line;
	int nNumFile = NULL;
	int nCnt = 0;

	// �z��̃N���A����
	m_pTutoUi.clear();

	// �ǂݍ��ݏI���܂ŉ�
	while (std::getline(loadFile, line))
	{
		// �t�@�C���̓ǂݍ��ރ��C����I��
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		if (token == "NUM_UI")
		{// "NUM_FILE"�ǂݎ�莞

			// "="�̎�
			std::string eq;

			// ���
			iss >> eq >> nNumFile;

			// �ő�T�C�Y��ݒ�
			m_pTutoUi.resize(nNumFile);
		}
		else if (token == "SET")
		{// SET�ǂݎ�莞
			while (std::getline(loadFile, line))
			{
				// �R�����g�X�L�b�v
				if (line.empty() || line[0] == '#') continue;

				std::istringstream subIss(line);
				std::string key;
				subIss >> key;

				if (key == "POS")
				{// POS�ǂݎ�莞

					// "="���i�[
					std::string eq;

					// ���W���i�[
					subIss >> eq
						>> m_pTutoUi[nCnt].pos.x
						>> m_pTutoUi[nCnt].pos.y
						>> m_pTutoUi[nCnt].pos.z;
				}
				else if (key == "WIDTH")
				{// "WIDTH"�ǂݎ�莞

					// "="���i�[
					std::string eq;

					// �������i�[
					subIss >> eq >> m_pTutoUi[nCnt].fWidth;
				}
				else if (key == "HEIGHT")
				{// "HEIGHT"�ǂݎ�莞

					// "="���i�[
					std::string eq;

					// �������i�[
					subIss >> eq >> m_pTutoUi[nCnt].fHeight;
				}
				else if (key == "TEXTURE")
				{// "TEXTURE"�ǂݎ�莞

					// "="���i�[
					std::string eq;

					// �t�@�C�������i�[
					subIss >> eq >> m_pTutoUi[nCnt].TexName;
				}
				else if (key == "STATE")
				{// "STATE"�ǂݎ�莞

					// "="���i�[
					std::string eq;

					// ��Ԃ��i�[
					subIss >> eq >> m_pTutoUi[nCnt].nState;
				}
				else if (key == "ENDSET")
				{
					// ����UI���ɍs��
					nCnt++;

					// while���𔲂���
					break;
				}
			}
		}
	}

	// �t�@�C�������
	loadFile.close();
}
//================================
// �^�X�N�i�s����
//================================
void CTutoTask::NextTask(void)
{
	// null����Ȃ�������
	if (m_pCurrentUi != nullptr)
	{
		// ��ԕύX
		m_pCurrentUi->SetState(CTutorialUi::STATE_EXIT);
	}
}
//================================
// ����UI��������
//================================
void CTutoTask::CreateTaskUi(int index)
{
	// ��O�`�F�b�N
	if (index < 0 || index >= (int)m_pTutoUi.size()) return;

	// �\���̏����Z�b�g
	const TASKINFO& data = m_pTutoUi[index];

	// null�Ȃ�
	if (m_pCurrentUi == nullptr)
	{
		// UI�𐶐�������
		m_pCurrentUi = CTutorialUi::Create(
			data.pos,		// ���W
			data.fWidth,	// ����
			data.fHeight,	// ����
			data.TexName.c_str(),	// �e�N�X�`����
			data.nState		// ���
		);
	}
}