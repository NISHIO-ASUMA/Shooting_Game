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
	m_nSecond = NULL;
	m_nMinute = NULL;
	m_nIdxTexture = NULL;
	m_nDecTime = NULL;
	m_nCount = NULL;

	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		m_pNumberMinute[nCnt] = nullptr;
		m_pNumberSecond[nCnt] = nullptr;
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

	// ��
	m_nMinute = m_nAllTime / CARVETIME;

	// �b�����炷
	m_nSecond = m_nAllTime % CARVETIME;

	// �����v�Z
	float fTexPos = m_fWidth / DIGIT_TIME;

	// ������
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �C���X�^���X����
		m_pNumberMinute[nCnt] = new CNumber;
		// �i���o�[�ϐ��̏�����
		m_pNumberMinute[nCnt]->SetPos(m_pos);
		m_pNumberMinute[nCnt]->Init(D3DXVECTOR3(m_pos.x + (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
		m_pNumberMinute[nCnt]->SetSize(fTexPos, m_fHeight);
		m_pNumberMinute[nCnt]->SetTexture("number003.png");
	}

	// ���炷�l
	m_pos.x += 150.0f;

	// �b����
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �C���X�^���X����
		m_pNumberSecond[nCnt] = new CNumber;

		// �i���o�[�ϐ��̏�����
		m_pNumberSecond[nCnt]->SetPos(m_pos);
		m_pNumberSecond[nCnt]->Init(D3DXVECTOR3(m_pos.x + (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);
		m_pNumberSecond[nCnt]->SetSize(fTexPos, m_fHeight);
		m_pNumberSecond[nCnt]->SetTexture("number003.png");
	}

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
		if (m_pNumberMinute[nCnt] != nullptr)
		{
			// �I������
			m_pNumberMinute[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pNumberMinute[nCnt];

			// null������
			m_pNumberMinute[nCnt] = nullptr;
		}

		// nullptr�`�F�b�N
		if (m_pNumberSecond[nCnt] != nullptr)
		{
			// �I������
			m_pNumberSecond[nCnt]->Uninit();

			// �|�C���^�̔j��
			delete m_pNumberSecond[nCnt];

			// null������
			m_pNumberSecond[nCnt] = nullptr;
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

	// �J�E���^�[�����Z
	m_nCount++;

	// 1�b�o�ߌ� ( �b���� )
	if (m_nCount >= CARVETIME)
	{
		// �J�E���^�[������������
		m_nCount = 0;

		// �S�̎��Ԃ����炷
		m_nAllTime--;

		// ��
		m_nMinute = m_nAllTime / CARVETIME;

		// �b�����炷
		m_nSecond = m_nAllTime % CARVETIME;

		// 0�ȉ��Ȃ�
		if (m_nAllTime <= 0) m_nAllTime = 0;

		// �������Ă��������Ԃ����Z
		m_nDecTime++;
	}

	// ���v�Z
	Second();
	Minute();
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
		// ���`��
		m_pNumberMinute[nCnt]->Draw();

		// �b�`��
		m_pNumberSecond[nCnt]->Draw();
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
// �b�v�Z
//===============================
void CTime::Second(void)
{
	int aData = 100;
	int aData2 = 10;

	// ���v�Z
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �����v�Z
		int aPosTexU = m_nMinute % aData / aData2;
		aData /= 10;
		aData2 /= 10;

		// ���̌������X�V����
		if (m_pNumberMinute[nCnt] != nullptr)
		{
			m_pNumberMinute[nCnt]->Update();
			m_pNumberMinute[nCnt]->SetDigit(aPosTexU);
		}
	}
}
//===============================
// ���v�Z
//===============================
void CTime::Minute(void)
{
	int aData = 100;
	int aData2 = 10;

	// �b�v�Z
	for (int nCnt = 0; nCnt < DIGIT_TIME; nCnt++)
	{
		// �����v�Z
		int aPosTexU = m_nSecond % aData / aData2;
		aData /= 10;
		aData2 /= 10;

		// �b�̌������X�V����
		if (m_pNumberSecond[nCnt] != nullptr)
		{
			m_pNumberSecond[nCnt]->Update();
			m_pNumberSecond[nCnt]->SetDigit(aPosTexU);
		}
	}
}