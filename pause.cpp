//=====================================
//
// �|�[�Y���� [ pause.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "pause.h"
#include "manager.h"
#include "texture.h"
#include "pausemanager.h"

//================================
// �R���X�g���N�^
//================================
CPause::CPause(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTexture = NULL;
	m_nPauseType = NULL;
}
//================================
// �f�X�g���N�^
//================================
CPause::~CPause()
{
	// ����
}
//================================
// ��������
//================================
CPause* CPause::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, D3DXCOLOR col,int nType)
{
	// �C���X�^���X����
	CPause* pPause = new CPause;

	// nullptr��������
	if (pPause == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pPause->Init()))
	{
		return nullptr;
	}

	// 2D�I�u�W�F�N�g�ݒ�
	pPause->SetPos(pos);
	pPause->SetSize(fWidth, fHeight);
	pPause->SetCol(col);
	pPause->SetType(nType);
	pPause->SetTexture();
	pPause->SetAnchor(ANCHORTYPE_CENTER);

	// �������ꂽ�|�C���^��Ԃ�
	return pPause;
}
//================================
// ����������
//================================
HRESULT CPause::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(TYPE_PAUSE);

	// �I�u�W�F�N�g�̏�����
	CObject2D::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CPause::Uninit(void)
{
	// �I�u�W�F�N�g�̔j��
	CObject2D::Uninit();
}
//================================
// �X�V����
//================================
void CPause::Update(void)
{
	// �I�u�W�F�N�g�̍X�V����
	CObject2D::Update();
}
//================================
// �`�揈��
//================================
void CPause::Draw(void)
{
	// �|�[�Y���L���Ȃ�
	if (CPauseManager::GetPause())
	{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// �e�N�X�`���擾
		CTexture* pTexture = CManager::GetTexture();

		// null�������炱���ŏ����I��
		if (pTexture == nullptr) return;

		// �e�N�X�`���Z�b�g
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// �I�u�W�F�N�g�̕`�揈��
		CObject2D::Draw();
	}
}
//================================
// �e�N�X�`������
//================================
void CPause::SetTexture(void)
{
	// �e�N�X�`���|�C���^���}�l�[�W���[����擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// ��ނɂ���ăe�N�X�`�����蓖�Ă�؂�ւ���
	switch (m_nPauseType)
	{
	case MENU_BACK: // �����̔w�i
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\PauseBack.png"); 		// �e�N�X�`�����蓖��
		break;

	case MENU_RETRY: // ���g���C�I����
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\pausemenu_retry.png"); 		// �e�N�X�`�����蓖��
		break;

	case MENU_CONTINUE: // �R���e�j���[�I����
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\pausemenu_continue.png"); 	// �e�N�X�`�����蓖��
		break;

	case MENU_QUIT: // �N�C�b�g�I����
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\pausemenu_quit.png"); 		// �e�N�X�`�����蓖��
		break;

	default:
		m_nIdxTexture = -1;
		break;
	}
}