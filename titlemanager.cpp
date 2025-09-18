//==========================================
//
// �^�C�g���Ǘ����� [ titlemanager.cpp ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "titlemanager.h"
#include "titleui.h"
#include "manager.h"
#include "game.h"
#include "tutorial.h"
#include "input.h"
#include "block.h"
#include "meshfield.h"
#include "meshdome.h"
#include "titleplayer.h"
#include "ui.h"
#include "sound.h"
#include "titlelogo.h"
#include "edit.h"
#include "pausemanager.h"
#include "pointui.h"
#include "sceneloader.h"
#include "cameramode.h"

//*************************
// ���O���
//*************************
namespace TITLEMANAGERINFO
{
	const D3DXVECTOR3 BacePos = { 210.0f, 520.0f, 0.0f };	// ����W
	constexpr int FLASHCOUNT = 10;	// �_�ŊԊu
};

//============================
// �R���X�g���N�^
//============================
CTitleManager::CTitleManager(bool isCreate) : m_isFirstuiCreate(isCreate)
{
	// �l�̃N���A
	m_nIdx = NULL;
	m_Info = {};

	for (int nCnt = 0; nCnt < TITLEINFO::TITLE_MENU; nCnt++)
	{
		m_pTitleui[nCnt] = nullptr;
	}
	m_pPointUi = nullptr;
	m_pUi = nullptr;
	m_isuiCreate = false;
}
//============================
// �f�X�g���N�^
//============================
CTitleManager::~CTitleManager()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CTitleManager::Init(void)
{	
	// �V�[���e�L�X�g�ǂݍ���
	CSceneLoader::SplitLoad(0);

	// ���̃V�[��������߂��Ă����Ƃ�
	if (!m_isFirstuiCreate) 
	{
		// �^�C�g����ui�𐶐�
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// ���̊Ԋu���󂯂�
			D3DXVECTOR3 pos = TITLEMANAGERINFO::BacePos;

			pos.x += nCnt * m_Info.INTERVAL;

			// ui�𐶐�
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// �t���O��L����
		m_isuiCreate = true;
	}

	// �^�C�g���v���C���[�𐶐�
	CTitlePlayer::Create(D3DXVECTOR3(-40.0f,0.0f,-550.0f),VECTOR3_NULL, 0, "data\\MOTION\\Player\\TitlePlayer100.txt");
	CTitlePlayer::Create(D3DXVECTOR3(40.0f,0.0f,-550.0f), VECTOR3_NULL, 1, "data\\MOTION\\Player\\TitlePlayer200.txt");

	// �^�C�g�����S����
	CTitleLogo::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 200.0f, 0.0f), 365.0f, 100.0f);

	// ����UI����
	m_pUi = CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 650.0f, 0.0f),30, 200.0f, 60.0f, "data\\TEXTURE\\Enterkey.png", true);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	// pSound->PlaySound(CSound::SOUND_LABEL_TITLE_BGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CTitleManager::Uninit(void)
{
	// ����
}
//============================
// �X�V����
//============================
void CTitleManager::Update(void)
{
	// ���̓f�o�C�X�擾
	CInputKeyboard* pKey = CManager::GetInputKeyboard();
	CJoyPad* pJoyPad = CManager::GetJoyPad();

	// �擾���s��
	if (pKey == nullptr) return;
	if (pJoyPad == nullptr) return;

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();

	// null��������
	if (pSound == nullptr) return;

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �擾���s��
	if (pCamera == nullptr) return;

	// �L�[���͎� ���� ui����������Ă��Ȃ�������
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && !m_isuiCreate)
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_RETURN);

		// �_�Œ�~
		m_pUi->SetUseFall(false,CUi::STATE_FALL);

		// UI����
		CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 660.0f, 0.0f), 0, 520.0f,55.0f, "data\\TEXTURE\\title_menuselect.png", false);

		// �^�C�g����ui�𐶐�
		for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
		{
			// ���̊Ԋu���󂯂�
			D3DXVECTOR3 pos = TITLEMANAGERINFO::BacePos;
			pos.x += nCnt * m_Info.INTERVAL;

			// ui�𐶐�
			m_pTitleui[nCnt] = CTitleUi::Create(pos, COLOR_WHITE, m_Info.UIWIDTH, m_Info.UIHEIGHT, nCnt);
		}

		// null�Ȃ�
		if (!m_pPointUi)
		{
			// �ŏ��͑I�𒆂�UI�ʒu
			D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos(); 

			// �I�����j���[�̏�ɐ���
			pos.y -= m_Info.SELECTPOS;

			// ���UI����
			m_pPointUi = CPointUi::Create(pos);
		}

		// �t���O��L����
		m_isuiCreate = true;
	}

	// ���L�[����
	if (pJoyPad->GetTrigger(pJoyPad->JOYKEY_LEFT) || pKey->GetTrigger(DIK_A) && m_isuiCreate)
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nIdx--;

		// �ŏ��l�ȉ��Ȃ�ŏ��l�ɐݒ�
		if (m_nIdx < m_Info.SELECT_START)
			m_nIdx = m_Info.SELECT_END;
	}

	// ���L�[����
	if (pJoyPad->GetTrigger(pJoyPad->JOYKEY_RIGHT) || pKey->GetTrigger(DIK_D) && m_isuiCreate)
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_SELECT);

		// �C���f�b�N�X�ԍ������Z
		m_nIdx++;

		// �ő�l�ȏ�Ȃ�ő�l�ɐݒ�
		if (m_nIdx > m_Info.SELECT_END)
			m_nIdx = m_Info.SELECT_START;
	}

	// �t�F�[�h�擾
	CFade* pFade = CManager::GetFade();

	// null��������
	if (pFade == nullptr) return;

	// �I������Ă��郁�j���[�̃|���S���J���[��ύX
	for (int nCnt = 0; nCnt < m_Info.TITLE_MENU; nCnt++)
	{
		// null����Ȃ�������
		if (m_pTitleui[nCnt] != nullptr)
		{
			// �J���[�ύX
			if (nCnt == m_nIdx)
			{// �I������Ă������
				// �_�ŊJ�n
				m_pTitleui[nCnt]->SetFlash(NULL, TITLEMANAGERINFO::FLASHCOUNT, COLOR_WHITE);
				
				// �����傫������
				m_pTitleui[nCnt]->SetSize(m_Info.SPREADWIDTH, m_Info.SPREADHEIGHT);
			}
			else
			{// �I�����ꂽ���Ȃ�����
				// �J���[�Z�b�g
				m_pTitleui[nCnt]->SetCol(COLOR_WHITE);

				// �����̃T�C�Y
				m_pTitleui[nCnt]->SetSize(m_Info.UIWIDTH, m_Info.UIHEIGHT);
			}
		}
	}

	// null����Ȃ�������
	if (m_pPointUi && m_pTitleui[m_nIdx])
	{
		// ���W��h��
		D3DXVECTOR3 pos = m_pTitleui[m_nIdx]->GetPos();

		// ��ɃZ�b�g
		pos.y -= m_Info.SELECTPOS;

		// ���W�����킹��
		m_pPointUi->SetPos(pos);
	}

	// Enter�L�[ or Start�{�^��
	if ((pKey->GetTrigger(DIK_RETURN) || pJoyPad->GetTrigger(pJoyPad->JOYKEY_START)) && pCamera->GetIsRotation() && pCamera->GetKeyFlag())
	{
		// �T�E���h�Đ�
		pSound->PlaySound(CSound::SOUND_LABEL_RETURN);

		switch (m_nIdx)
		{
		case CTitleUi::MENU_GAME:		// �Q�[�����[�h
			if (pFade != nullptr) 
				pFade->SetFade(new CGame());	// �Q�[���V�[���ɑJ��
				pCamera->SetAnim(false);		// �A�j���[�V�����N��
			break;

		case CTitleUi::MENU_TUTORIAL:	// �`���[�g���A�����[�h
			if (pFade != nullptr) pFade->SetFade(new CTutorial());	// �`���[�g���A���V�[���ɑJ��
			break;

		case CTitleUi::MENU_EXIT:	// �I�����j���[
			PostQuitMessage(0);
			break;

		default:
			break;
		}
	}

#ifdef _DEBUG

	// F2�L�[
	if ((pKey->GetTrigger(DIK_F9)))
	{
		// �ҏW���
		if (pFade != nullptr) pFade->SetFade(new CEdit());
	}

	if (pKey->GetTrigger(DIK_F6))
	{
		CFade* pFade = CManager::GetFade();
		if (pFade != nullptr) pFade->SetFade(new CCameraMode());
		return;
	}

#endif // _DEBUG

}