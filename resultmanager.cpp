//==============================================
//
// ���U���g�V�[���Ǘ����� [ resultmanager.cpp ]
// Author: Asuma Nishio
// 
//==============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "resultmanager.h"
#include "manager.h"
#include "sound.h"
#include "input.h"
#include "title.h"
#include "resultui.h"
#include "resultscore.h"
#include "ui.h"
#include "ranking.h"

//=================================
// �R���X�g���N�^
//=================================
CResultManager::CResultManager()
{
	// �l�̃N���A
	m_isKeyDown = false;
	m_nGameScore = NULL;
	m_nLastTime = NULL;

	for (int nCnt = 0; nCnt < SCORELISTNUM; nCnt++)
	{
		m_pResultScore[nCnt] = nullptr;
	}
}
//=================================
// �f�X�g���N�^
//=================================
CResultManager::~CResultManager()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CResultManager::Init(void)
{	
	// UI����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "data\\TEXTURE\\resultback.jpg", false);

	// �f�[�^�̓ǂݍ���
	Load();

	// �X�R�A�𐶐�����
	m_pResultScore[0] = CResultScore::Create(D3DXVECTOR3(1120.0f, 260.0f, 0.0f), 300.0f, 60.0f,0);
	m_pResultScore[1] = CResultScore::Create(D3DXVECTOR3(1120.0f, 415.0f, 0.0f), 300.0f, 60.0f,1);
	m_pResultScore[2] = CResultScore::Create(D3DXVECTOR3(1120.0f, 600.0f, 0.0f), 300.0f, 60.0f,2);

	// �����X�R�A
	m_pResultScore[0]->SetScore(m_nGameScore);

	// �^�C���X�R�A
	m_pResultScore[1]->SetTimeScore(m_nLastTime);
	int nScore = m_pResultScore[1]->MathTimescore();
	m_pResultScore[1]->SetTimeScore(nScore);

	// �ŏI�X�R�A
	m_pResultScore[2]->SetLastScore(m_nGameScore, nScore);


	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_RESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CResultManager::Uninit(void)
{
	// null�`�F�b�N
}
//=================================
// �X�V����
//=================================
void CResultManager::Update(void)
{
	// ���̓f�o�C�X���擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pJyoPad = CManager::GetJoyPad();

	// �擾���s��
	if (pInput == nullptr) return;
	if (pJyoPad == nullptr) return;

	// �J�������擾
	CCamera* pCamera = CManager::GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// ����L�[�������ꂽ
	if ((pInput->GetTrigger(DIK_RETURN) || pJyoPad->GetTrigger(pJyoPad->JOYKEY_A)))
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �t���O�L����
			m_isKeyDown = true;

			// �X�R�A�������o��
			m_pResultScore[2]->Save();

			// �V�[���J��
			pFade->SetFade(new CRanking());

			// �J����������
			pCamera->Init();

			// �J�����̐ݒ������������
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);
			pCamera->SetKey(false);

			return;

		}
	}
}
//=================================
// �X�V����
//=================================
void CResultManager::Load(void)
{
	// �ǂݎ�����l���i�[���郁���o�ϐ�
	m_nGameScore = 0;
	m_nLastTime = 0;

	//==============================
	// GameScore.txt
	//==============================
	{
		std::ifstream file("data\\Loader\\GameScore.txt");

		if (file.is_open())
		{
			file >> m_nGameScore;   // ���l1��ǂݎ��
			file.close();
		}
		else
		{
			MessageBox(NULL, "GameScore.txt ���J���܂���ł���", "�G���[", MB_OK);
		}
	}

	//==============================
	// LastTime.txt
	//==============================
	{
		std::ifstream file("data\\Loader\\LastTime.txt");
		if (file.is_open())
		{
			file >> m_nLastTime;    // ���l1��ǂݎ��
			file.close();
		}
		else
		{
			MessageBox(NULL, "LastTime.txt ���J���܂���ł���", "�G���[", MB_OK);
		}
	}
}
