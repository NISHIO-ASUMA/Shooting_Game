//=====================================
//
// �}�l�[�W���[���� [ manager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "manager.h"
#include "title.h"
#include "game.h"
#include "tutorial.h"
#include "result.h"

//**************************
// �ÓI�����o�ϐ��錾
//**************************
CRenderer* CManager::m_pRenderer = nullptr;				// �����_���[�ւ̃|�C���^
CInputKeyboard* CManager::m_pInputKeyboard = nullptr;	// �L�[�{�[�h�ւ̃|�C���^
CJoyPad* CManager::m_pJoyPad = nullptr;					// �W���C�p�b�h�N���X�ւ̃|�C���^
CSound* CManager::m_pSound = nullptr;					// �T�E���h�ւ̃|�C���^
CInputMouse* CManager::m_pInputMouse = nullptr;			// �}�E�X�ւ̃|�C���^
CTexture* CManager::m_pTexture = nullptr;				// �e�N�X�`���N���X�ւ̃|�C���^
CCamera* CManager::m_pCamera = nullptr;					// �J�����N���X�ւ̃|�C���^
CLight* CManager::m_pLight = nullptr;					// ���C�g�N���X�ւ̃|�C���^
CScene* CManager::m_pScene = nullptr;					// �V�[���N���X�ւ̃|�C���^
CFade* CManager::m_pFade = nullptr;						// �t�F�[�h�N���X�ւ̃|�C���^
CCollision* CManager::m_pCollision = nullptr;			// �R���W�����N���X�ւ̃|�C���^

//===========================
// �R���X�g���N�^
//===========================
CManager::CManager()
{
	// ����
}
//===========================
// �f�X�g���N�^
//===========================
CManager::~CManager()
{
	// ����
}
//===========================
// �}�l�[�W���[�̏���������
//===========================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �L�[�{�[�h�I�u�W�F�N�g�̐�������
	m_pInputKeyboard = new CInputKeyboard;

	// �������Ɏ��s������
	if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
	{
		// -1��Ԃ�
		return -1;
	}

	// �W���C�p�b�h�I�u�W�F�N�g�̐�������
	m_pJoyPad = new CJoyPad;

	// �������Ɏ��s������
	if (FAILED(m_pJoyPad->Init(hInstance, hWnd)))
	{
		// -1��Ԃ�
		return -1;
	}

	// �}�E�X�I�u�W�F�N�g�̐�������
	m_pInputMouse = new CInputMouse;

	// �������Ɏ��s������
	if (FAILED(m_pInputMouse->Init(hInstance, hWnd)))
	{
		// -1��Ԃ�
		return -1;
	}

	// �T�E���h�̐�������
	m_pSound = new CSound;

	if (FAILED(m_pSound->Init(hWnd)))
	{
		// -1��Ԃ�
		return -1;
	}

	// �J��������
	m_pCamera = new CCamera;

	// �������Ɏ��s������
	if (FAILED(m_pCamera->Init()))
	{
		// -1��Ԃ�
		return -1;
	}

	// �����_���[�̐�������
	m_pRenderer = new CRenderer;

	// �������Ɏ��s������
	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{
		// -1��Ԃ�
		return -1;
	}

	// ���C�g����
	m_pLight = new CLight;

	// �������Ɏ��s������
	if (FAILED(m_pLight->Init()))
	{
		// -1��Ԃ�
		return -1;
	}

	// �R���W��������
	m_pCollision = new CCollision;

	// �t�F�[�h����
	m_pFade = new CFade;

	// ���������s��
	if (FAILED(m_pFade->Init()))
	{
		// -1��Ԃ�
		return -1;
	}

	// �e�N�X�`������
	m_pTexture = new CTexture;

	// �e�N�X�`���S�ǂݍ���
	m_pTexture->Load();

#ifdef _DEBUG
	// �V�[���Z�b�g
	m_pFade->SetFade(new CGame());
#else
	// �V�[���Z�b�g
	m_pFade->SetFade(new CTitle(true));

#endif // _DEBUG

	return S_OK;
}
//===========================
// �}�l�[�W���[�̏I������
//===========================
void CManager::Uninit(void)
{
	// �S�I�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	// �L�[�{�[�h�̔j��
	if (m_pInputKeyboard != nullptr)
	{
		// �L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();
		
		// �L�[�{�[�h�̔j��
		delete m_pInputKeyboard;

		// nullptr�ɂ���
		m_pInputKeyboard = nullptr;
	}

	// �Q�[���p�b�h�̔j��
	if (m_pJoyPad != nullptr)
	{
		// �W���C�p�b�h�̏I������
		m_pJoyPad->Uninit();
		
		// �W���C�p�b�h�̔j��
		delete m_pJoyPad;

		// nullptr�ɂ���
		m_pJoyPad = nullptr;
	}

	// �}�E�X�̔j��
	if (m_pInputMouse != nullptr)
	{
		// �}�E�X�̏I������
		m_pInputMouse->Uninit();

		// �}�E�X�̊�
		delete m_pInputMouse;

		// nullptr�ɂ���
		m_pInputMouse = nullptr;
	}

	// �T�E���h���̔j��
	if (m_pSound != nullptr)
	{
		// �T�E���h�̏I������
		m_pSound->Uninit();

		// �T�E���h�̔j��
		delete m_pSound;

		// nullptr�ɂ���
		m_pSound = nullptr;
	}

	// �J�����̔j��
	if (m_pCamera != nullptr)
	{
		// �I������
		m_pCamera->Uninit();

		// �j��
		delete m_pCamera;

		// nullptr�ɂ���
		m_pCamera = nullptr;
	}

	//  ���C�g�̔j��
	if (m_pLight != nullptr)
	{
		// �I������
		m_pLight->Uninit();

		// �j��
		delete m_pLight;

		// nullptr�ɂ���
		m_pLight = nullptr;
	}

	// �R���W�����N���X�̔j��
	if (m_pCollision != nullptr)
	{
		// �|�C���^�̔j��
		delete m_pCollision;

		// nullptr�ɂ���
		m_pCollision = nullptr;
	}

	// �e�N�X�`���j��
	if (m_pTexture != nullptr)
	{
		// ���ׂẴe�N�X�`���̔j��
		m_pTexture->UnLoad();

		// �|�C���^�̔j��
		delete m_pTexture;

		// nullptr���
		m_pTexture = nullptr;
	}

	// �t�F�[�h�̔j��
	if (m_pFade != nullptr)
	{
		// �I������
		m_pFade->Uninit();

		// �|�C���^�̔j��
		delete m_pFade;

		// nullptr�ɂ���
		m_pFade = nullptr;
	}

	// �V�[���̔j��
	if (m_pScene != nullptr)
	{
		// �I������
		m_pScene->Uninit();

		// �|�C���^�̔j��
		delete m_pScene;

		// nullptr�ɂ���
		m_pScene = nullptr;
	}

	// �����_���[�̔j��
	if (m_pRenderer != nullptr)
	{
		// �����_���[�̏I������
		m_pRenderer->Uninit();

		// �����_���[�̔j��
		delete m_pRenderer;

		// nullptr�ɂ���
		m_pRenderer = nullptr;
	}
}
//===========================
// �}�l�[�W���[�̍X�V����
//===========================
void CManager::Update()
{
	// �L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	// �W���C�p�b�h�̍X�V����
	m_pJoyPad->Update();

	// �}�E�X�̍X�V����
	m_pInputMouse->Update();

	// �W���C�p�b�h�U���̍X�V����
	m_pJoyPad->UpdateVibration();

	// �J�����X�V
	m_pCamera->Update();

	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// null�`�F�b�N
	if (m_pScene != nullptr)
	{
		// �V�[���̍X�V
		m_pScene->Update();
	}

	// �����_���[�̍X�V����
	m_pRenderer->Update();
}
//===========================
// �}�l�[�W���[�̕`�揈��
//===========================
void CManager::Draw(void)
{
	// �����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//===========================
// �V�[���̃Z�b�g
//===========================
void CManager::SetScene(CScene * pNewscene)
{
	// nullptr����Ȃ�
	if (m_pScene != nullptr)
	{
		// �I������
		m_pScene->Uninit();

		// �|�C���^�̔j��
		delete m_pScene;

		// nullptr�ɂ���
		m_pScene = nullptr;

		// null����Ȃ�
		if (m_pSound)
		{
			// �T�E���h�̒�~
			m_pSound->StopSound();
		}

		// �S�I�u�W�F�N�g�j��
		CObject::ReleaseAll();
	}

	// �����V�[��������������
	if (m_pScene == nullptr)
	{
		// �V�����V�[�����Z�b�g����
		m_pScene = pNewscene;

		// �V�[���̏�����
		if (FAILED(m_pScene->Init()))
		{
			// ���s��
			MessageBox(GetActiveWindow(), "�V�[�����������s", "��O�X���[", MB_OK);

			// �j��
			delete m_pScene;

			// nullptr���
			m_pScene = nullptr;
		}
	}
}
//===========================
// ���݃V�[���擾
//===========================
CScene::MODE CManager::GetScene(void)
{
	// nullptr����Ȃ�
	if (m_pScene)
		return m_pScene->GetScene(); // ���݃V�[��
	else
		return CScene::MODE_NONE;	 // �����Ȃ��V�[��
}