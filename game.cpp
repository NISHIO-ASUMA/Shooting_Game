//=====================================
//
// ���C���Q�[������ [ game.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "game.h"
#include "manager.h"
#include "debugproc.h"
#include "title.h"
#include "result.h"
#include "loseresult.h"
#include "gamemanager.h"
#include "player.h"

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CPauseManager* CGame::m_pPausemanager = nullptr; // �|�[�Y�}�l�[�W���[�̃|�C���^

//==================================
// �R���X�g���N�^
//==================================
CGame::CGame() : CScene(CScene::MODE_GAME)
{
	// �l�̃N���A
	m_pGameManager = nullptr;
	m_nGametype = GAMESTATE_NONE;
	m_nStateCount = NULL;
}
//==================================
// �f�X�g���N�^
//==================================
CGame::~CGame()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CGame::Init(void)
{
	// �|�[�Y�}�l�[�W���[����
	m_pPausemanager = new CPauseManager;

	// null��������
	if (m_pPausemanager == nullptr)
	{
		return E_FAIL;
	}

	// �|�[�Y�}�l�[�W���[����������
	m_pPausemanager->Init();

	// �Q�[���}�l�[�W���[����
	m_pGameManager = new CGameManager;

	// null��������
	if (m_pGameManager == nullptr)
	{
		return E_FAIL;
	}

	// �Q�[���}�l�[�W���[����������
	m_pGameManager->Init();

	// �ʏ�i�s���
	m_nGametype = GAMESTATE_NORMAL;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CGame::Uninit(void)
{
	// null�`�F�b�N
	if (m_pPausemanager != nullptr)
	{
		// �I������
		m_pPausemanager->Uninit();

		// �|�C���^�̔j��
		delete m_pPausemanager;

		// nullptr�ɂ���
		m_pPausemanager = nullptr;
	}

	// null�`�F�b�N
	if (m_pGameManager != nullptr)
	{
		// �I������
		m_pGameManager->Uninit();

		// �|�C���^�̔j��
		delete m_pGameManager;

		// nullptr�ɂ���
		m_pGameManager = nullptr;
	}
}
//==================================
// �X�V����
//==================================
void CGame::Update(void)
{	
	// �|�[�Y�̃L�[���͔���
	m_pPausemanager->SetEnablePause();
	
	// �|�[�Y�̍X�V����
	m_pPausemanager->Update();
	
	// �t�F�[�h�擾
	CFade* pFade = CManager::GetFade();

	switch (m_nGametype)
	{
	case GAMESTATE_NORMAL://�ʏ���
		break;

	case GAMESTATE_END:
		m_nStateCount++;

		if (m_nStateCount >= 30)
		{
			// �J�E���^�[��������
			m_nStateCount = 0;
			
			// 1�b�o��
			m_nGametype = GAMESTATE_NONE;//�������Ă��Ȃ����

			// �t�F�[�h���擾�ł�����
			if (pFade != nullptr)
			{
				// ���U���g�V�[���ɑJ��
				pFade->SetFade(new CResult());

				// �����ŏ�����Ԃ�
				return;
			}
		}
		break;

	case GAMESTATE_LOSEEND:
		m_nStateCount++;

		if (m_nStateCount >= 30)
		{
			// �J�E���^�[��������
			m_nStateCount = 0;

			// 1�b�o��
			m_nGametype = GAMESTATE_NONE;//�������Ă��Ȃ����

			// �t�F�[�h���擾�ł�����
			if (pFade != nullptr)
			{
				// �������U���g�V�[���ɑJ��
				pFade->SetFade(new CLoseResult());

				// �����ŏ�����Ԃ�
				return;
			}
		}
		break;
	}

	// false�̎��ɍX�V
	if (m_pPausemanager->GetPause() == false)
	{
		// �Q�[���}�l�[�W���[�X�V
		m_pGameManager->Update();

		// �o�ߎ��Ԃ��擾
		int Numtime = m_pGameManager->GetTime()->GetAllTime();

		// �^�C�}�[��0�b�ȉ��Ȃ�
		if (Numtime <= 0)
		{
			// �������U���g�J��
			m_nGametype = GAMESTATE_LOSEEND;
			return;
		}

		// �{�X�擾
		CBoss* pBoss = CGameManager::GetBoss();

		// �{�X���S�t���O���L���Ȃ� TODO : ������animation�I�����Ă�����̃t���O�ݒ�
		if (pBoss->IsDaeth())
		{
#if 0
			// �J�����擾
			CCamera* pCamera = CManager::GetCamera();
			if (pCamera == nullptr) return;

			// �A�j���[�V�����Z�b�g
			pCamera->SetLoadPass(1);
			pCamera->SetCameraMode(CCamera::MODE_ANIM);

			// �I�����肪�L����������
			if (pCamera->GetAnim())
			{
				// ��ԕύX
				m_nGametype = GAMESTATE_END;
			}
#endif
			// ��ԕύX
			m_nGametype = GAMESTATE_END;
		}

		// �v���C���[�擾
		CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
		if (pPlayer == nullptr) return;

		if (pPlayer->IsDeath())
		{
			// ��ԕύX
			m_nGametype = GAMESTATE_LOSEEND;
		}
	}
}
//==================================
// �`�揈��
//==================================
void CGame::Draw(void)
{
	// ����
}
//==================================
// �R���X�g���N�^
//==================================
CGame* CGame::Create(void)
{	
	// �C���X�^���X����
	CGame* pGame = new CGame;

	// nullptr��������
	if (pGame == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pGame->Init()))
	{
		// �|�C���^��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pGame;
}