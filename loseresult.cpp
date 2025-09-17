//============================================
//
// �������U���g�V�[������ [ loseresult.cpp ]
// Author: Asuma Nishio
// 
//============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "loseresult.h"
#include "manager.h"
#include "ui.h"
#include "title.h"
#include "sound.h"

//===============================
// �R���X�g���N�^
//===============================
CLoseResult::CLoseResult() : CScene(CScene::MODE_LOSERESULT)
{
	// �l�̃N���A
}
//===============================
// �f�X�g���N�^
//===============================
CLoseResult::~CLoseResult()
{
	// ����
}
//===============================
// ��������
//===============================
CLoseResult* CLoseResult::Create(void)
{
	// �C���X�^���X����
	CLoseResult* pLoseresult = new CLoseResult;
	if (pLoseresult == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pLoseresult->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pLoseresult;
}
//===============================
// ����������
//===============================
HRESULT CLoseResult::Init(void)
{
	// UI����
	CUi::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), 0, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, "data\\TEXTURE\\LoseResult.jpg",false);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();
	if (pSound == nullptr) return E_FAIL;

	// �T�E���h�Đ�
	pSound->PlaySound(CSound::SOUND_LABEL_LOSERESULTBGM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CLoseResult::Uninit(void)
{
	// ����
}
//===============================
// �X�V����
//===============================
void CLoseResult::Update(void)
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();
	if (pCamera == nullptr) return;

	// �L�[���͂Ń^�C�g���ɖ߂�
	if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN) || CManager::GetJoyPad()->GetTrigger(CManager::GetJoyPad()->JOYKEY_START)))
	{
		// �|�C���^�擾
		CFade* pFade = CManager::GetFade();

		// null����Ȃ��Ƃ�
		if (pFade != nullptr)
		{
			// �V�[���J��
			pFade->SetFade(new CTitle(true));

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
//===============================
// �`�揈��
//===============================
void CLoseResult::Draw(void)
{
	// ����
}