//=====================================
//
// �|�[�Y�Ǘ����� [ pausemanager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "pausemanager.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "title.h"
#include "game.h"

//***************************
// ���O���
//***************************
namespace PAUSEMANAGEINFO
{
	inline const D3DXVECTOR3 BACEPOS = { 200.0f,180.0f,0.0f }; // ��_���W

	constexpr int FLASHFLAME = 60;				// �_�ŊԊu
	constexpr float BACEWIDTH = 180.0f;			// ��̉���
	constexpr float BACEHEIGHT = 40.0f;			// ��̍���
	constexpr float UPPERWIDTH = 180.0f;		// �g�債������
	constexpr float UPPERHEIGHT = 50.0f;		// �g�債������
	constexpr float SPACEHEIGHT = 160.0f;		// �|���S�����m�̊Ԋu

};

//***************************
// �ÓI�����o�ϐ��錾
//***************************
bool CPauseManager::m_isPause = false; // �|�[�Y�t���O

//==================================
// �R���X�g���N�^
//==================================
CPauseManager::CPauseManager()
{
	// �l�̃N���A
	m_nSelectIdx = NULL;
	m_isPause = false;

	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		m_pPause[nCnt] = nullptr;
	}
}
//==================================
// �f�X�g���N�^
//==================================
CPauseManager::~CPauseManager()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CPauseManager::Init(void)
{
	// �����Z���N�g�ԍ��ݒ�
	m_nSelectIdx = CPause::MENU_RETRY;

	// ����W��ݒ�
	D3DXVECTOR3 Bacepos = PAUSEMANAGEINFO::BACEPOS;
	
	// �|�[�Y����
	for (int nPause = 0; nPause < SELECT_MAX; nPause++)
	{
		// ���W�Z�b�g
		D3DXVECTOR3 pos = Bacepos;

		// �������󂯂�
		pos.y += nPause * PAUSEMANAGEINFO::SPACEHEIGHT;

		// �|�[�YUI�𐶐� 
		if (nPause == CPause::MENU_BACK)
		{
			// �w�i����
			m_pPause[nPause] = CPause::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f,0.0f), SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, COLOR_WHITE, nPause);
		}
		else
		{
			// �I��p�|���S���̐���
			m_pPause[nPause] = CPause::Create(pos, PAUSEMANAGEINFO::BACEWIDTH, PAUSEMANAGEINFO::BACEHEIGHT, COLOR_WHITE, nPause);
		}
	}

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CPauseManager::Uninit(void)
{
	// ����
}
//==================================
// �X�V����
//==================================
void CPauseManager::Update(void)
{
	// �|�[�Y������Ȃ�������
	if (!m_isPause)	return;

	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// null�`�F�b�N
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return;

	// �I���C���f�b�N�X�͈�
	const int SELECT_BEGIN = 1;
	const int SELECT_END = SELECT_MAX - 1;

	// ��L�[����
	if (pKey->GetTrigger(DIK_UP) || pKey->GetTrigger(DIK_W) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_UP))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nSelectIdx--;

		// �ŏ��l�ȉ��Ȃ�ŏ��l�ɐݒ�
		if (m_nSelectIdx < SELECT_BEGIN)
			m_nSelectIdx = SELECT_END;
	}

	// ���L�[����
	if (pKey->GetTrigger(DIK_DOWN) || pKey->GetTrigger(DIK_S) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_DOWN))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(pSound->SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nSelectIdx++;

		// �ő�l�ȏ�Ȃ�ő�l�ɐݒ�
		if (m_nSelectIdx > SELECT_END)
			m_nSelectIdx = SELECT_BEGIN;
	}

	// �t�F�[�h�擾
	CFade* pFade = CManager::GetFade();

	// null��������
	if (pFade == nullptr) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// null��������
	if (pCamera == nullptr) return;

	// �I������Ă��郁�j���[�̃|���S���J���[��ύX
	for (int nCnt = 0; nCnt < SELECT_MAX; nCnt++)
	{
		// �w�i�͕ς��Ȃ�
		if (nCnt == CPause::MENU_BACK) continue;

		// null����Ȃ�������
		if (m_pPause[nCnt] != nullptr)
		{
			// �J���[�ύX
			if (nCnt == m_nSelectIdx)
			{
				m_pPause[nCnt]->SetFlash(NULL, PAUSEMANAGEINFO::FLASHFLAME,COLOR_YERROW);			// �_�ŏ���
				m_pPause[nCnt]->SetSize(PAUSEMANAGEINFO::UPPERWIDTH, PAUSEMANAGEINFO::UPPERHEIGHT); // �����傫������
			}
			else
			{
				m_pPause[nCnt]->SetCol(COLOR_WHITE);												// ��
				m_pPause[nCnt]->SetSize(PAUSEMANAGEINFO::BACEWIDTH, PAUSEMANAGEINFO::BACEHEIGHT);	// ���̃T�C�Y
			}
		}
	}

	// Enter�L�[ or B�{�^������
	if (pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_B))
	{
		// �T�E���h�Đ�
		pSound->PlaySound(pSound->SOUND_LABEL_RETURN);

		switch (m_nSelectIdx)
		{
		case CPause::MENU_BACK:	// �w�i
			break;

		case CPause::MENU_RETRY:	// ���g���C��
			if (pFade != nullptr) pFade->SetFade(new CGame());	// �Q�[���V�[���ɑJ��
			SetEnablePause(false);	// �|�[�Y�I��
			pCamera->SetAnim(false); // �A�j���[�V�����N��
			break;

		case CPause::MENU_CONTINUE:	// �R���e�j���[��
			SetEnablePause(false);	// �|�[�Y�I��
			break;

		case CPause::MENU_QUIT:		// �ޏo��
			if (pFade != nullptr) pFade->SetFade(new CTitle(true));	// �^�C�g���V�[���ɑJ��
			SetEnablePause(false);	// �|�[�Y�I��

			// �J�����̐ݒ������������
			pCamera->SetFinishRotation(false);
			pCamera->SetIsRotation(false);
			pCamera->SetKey(false);

			break;
		}
	}
}
//===========================
// �|�[�Y���ǂ���
//===========================
void CPauseManager::SetEnablePause(void)
{
	// P�L�[ or Start �������ꂽ
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_P) ||
		CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START))
	{
		if (CManager::GetCamera()->GetShake() == false)
		{
			// �t���O�ύX
			m_isPause = m_isPause ? false : true;
		}
	}
}