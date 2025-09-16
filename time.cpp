//====================================
//
// �^�C������ [ time.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "time.h"
#include "manager.h"

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CTime::CTime(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_pos = VECTOR3_NULL;
	m_fHeight = NULL;
	m_fWidth = NULL;
	m_nAllTime = NULL;
	m_nCurrentTime = NULL;
	m_nIdxTexture = NULL;
	m_nDecTime = NULL;

	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		m_pNumber[nCnt] = nullptr;
	}
}
//===============================
// �f�X�g���N�^
//===============================
CTime::~CTime()
{
	// ����
}
//===============================
// ��������
//===============================
CTime* CTime::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �^�C���N���X�̃C���X�^���X����
	CTime* pTime = new CTime;

	// nullptr��������
	if (pTime == nullptr) return nullptr;

	// �����o�ϐ��ɃZ�b�g
	pTime->m_fHeight = fHeight;
	pTime->m_fWidth = fWidth;
	pTime->m_pos = pos;

	// ���������s��
	if (FAILED(pTime->Init()))
	{
		// nullptr���
		return nullptr;
	}

	// ���ʂ�Ԃ�
	return pTime;
}
//===============================
// ����������
//===============================
HRESULT CTime::Init(void)
{
	// �����o�ϐ��̏�����
	m_nAllTime = NUMTIME;
	m_nCurrentTime = NULL;

	// �����v�Z
	float fTexPos = m_fWidth / DIGIT_TIME;

	// ��������
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �C���X�^���X����
		m_pNumber[nCnt] = new CNumber;

		// �i���o�[�ϐ��̏�����
		m_pNumber[nCnt]->SetPos(m_pos);
		m_pNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
		m_pNumber[nCnt]->SetSize(fTexPos, m_fHeight);

	}

	// �e�N�X�`���Z�b�g
	SetTexture();

	// ���ʂ�Ԃ�
	return S_OK;
}
//===============================
// �I������
//===============================
void CTime::Uninit(void)
{
	// �g�������j��
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_pNumber[nCnt] != nullptr)
		{
			// �I������
			m_pNumber[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pNumber[nCnt];

			// null������
			m_pNumber[nCnt] = nullptr;
		}
	}

	// �I�u�W�F�N�g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CTime::Update(void)
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g�� �܂��� �A�j���[�V�������Ȃ�~�߂�
	if (pCamera->GetMode() == CCamera::MODE_ANIM) return;
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// �J�E���g�����Z
	m_nCurrentTime++;

	// 1�t���[���o�ߌ�
	if (m_nCurrentTime >= CARVETIME)
	{
		// �����Ԃ����炷
		m_nAllTime--;

		// 0�ȉ��Ȃ�
		if (m_nAllTime <= 0) m_nAllTime = 0;

		// �J�E���^�[������������
		m_nCurrentTime = 0;

		// �������Ă��������Ԃ����Z
		m_nDecTime++;
	}

	// �ő厞�Ԃ��i�[
	int time = m_nAllTime;

	// ��̈ʂ���S�̈ʂ܂ŏ��ɕ���
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �����v�Z
		int digit = time % DIVIDE;
		time /= DIVIDE;

		// �i���o�[�X�V�ƌ��ݒ�
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Update();
			m_pNumber[nCnt]->SetDigit(digit);
		}
	}
}
//===============================
// �`�揈��
//===============================
void CTime::Draw(void)
{
	// �A�j���[�V�������͕`�悵�Ȃ�
	if (CManager::GetCamera()->GetMode() == CCamera::MODE_ANIM)
	{
		return;
	}

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �������`��
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �e�N�X�`���ݒ�
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

		// �^�C�}�[�`��
		m_pNumber[nCnt]->Draw();
	}
}
//===============================
// �^�C�}�[�f�[�^�ۑ�����
//===============================
void CTime::Save(void)
{
	// �J���t�@�C�����`
	std::ofstream File("data\\Loader\\LastTime.txt");

	// ��O����
	if (!File.is_open())
	{
		MessageBox(NULL, "�ۑ��t�@�C�����J���܂���ł���", "�G���[", MB_OK);

		return;
	}

	// ���l���o�͂���
	File << m_nDecTime;

	// �t�@�C�������
	File.close();
}
//===============================
// �e�N�X�`���Z�b�g
//===============================
void CTime::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\score001.png");
}
