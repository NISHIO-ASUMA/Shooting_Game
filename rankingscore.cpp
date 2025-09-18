//==========================================
//
// �����L���O�X�R�A���� [ rankingscore.cpp ]
// Author: Asuma Nishio
//
//==========================================

//****************************
// �C���N���[�h�t�@�C��
//****************************
#include "rankingscore.h"
#include "manager.h"
#include "texture.h"
#include "number.h"
#include <algorithm>

//******************************
// �ÓI�����o�ϐ�
//******************************
int CRankingScore::m_nNewRankingScore = -1; // ������

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
	m_pos = VECTOR3_NULL;

	for (int nCntData = 0; nCntData < RANKING_MAX; nCntData++)
	{
		// �X�R�A���i�[
		m_aRankScore[nCntData] = NULL;

		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			// �i���o�[�|�C���^
			m_apNumber[nCntData][nCnt] = nullptr;
		}
	}
}
//===============================
// �f�X�g���N�^
//===============================
CRankingScore::~CRankingScore()
{
	// ����
}
//===============================
// ��������
//===============================
CRankingScore* CRankingScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// �C���X�^���X����
	CRankingScore* pRankScore = new CRankingScore;
	if (pRankScore == nullptr) return nullptr;

	// �I�u�W�F�N�g
	pRankScore->m_pos = pos; // �ړI�̍��W
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight = fHeight;

	// ���������s��
	if (FAILED(pRankScore->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRankScore;
}
//===============================
// ����������
//===============================
HRESULT CRankingScore::Init(void)
{
	// �X�R�A�����[�h
	Load();

	// �����v�Z
	float fTexPos = m_fWidth / RANKSCOREDIGIT;

	for (int nRank = 0; nRank < RANKING_MAX; nRank++)
	{
		// ������
		for (int nDigit = 0; nDigit < RANKSCOREDIGIT; nDigit++)
		{
			// �C���X�^���X����
			m_apNumber[nRank][nDigit] = new CNumber;

			// Y���W�����炷
			float yOffset = m_pos.y + (m_fHeight + 60.0f) * nRank;

			// ����������
			m_apNumber[nRank][nDigit]->Init
			(
				D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nDigit), yOffset, 0.0f),
				fTexPos,
				m_fHeight
			);

			// �T�C�Y�ݒ�
			m_apNumber[nRank][nDigit]->SetSize(fTexPos, m_fHeight);

			// �e�N�X�`���ݒ�
			m_apNumber[nRank][nDigit]->SetTexture("score001.png");
		}
	}

	return S_OK;
}
//===============================
// �I������
//===============================
void CRankingScore::Uninit(void)
{
	// �g���Ă��錅�����̔j��
	for (int nRankData = 0; nRankData < RANKING_MAX; nRankData++)
	{
		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			if (m_apNumber[nRankData][nCnt] != nullptr)
			{
				// �i���o�[�̔j��
				m_apNumber[nRankData][nCnt]->Uninit();
				delete m_apNumber[nRankData][nCnt];
				m_apNumber[nRankData][nCnt] = nullptr;
			}
		}
	}

	// ���g�̔j��
	CObject::Release();
}
//===============================
// �X�V����
//===============================
void CRankingScore::Update(void)
{
	// �X�R�A�̌����X�V
	for (int rank = 0; rank < RANKING_MAX; rank++)
	{
		int score = m_aRankScore[rank];

		for (int digit = 0; digit < RANKSCOREDIGIT; digit++)
		{
			int num = score % 10;  // 1�����o��
			score /= 10;

			// ���X�V
			m_apNumber[rank][digit]->SetDigit(num);

			// �Y���X�R�A�������N�C�����Ă���
			if (rank == m_nNewRankingScore)
			{
				// �_�ŏ��������s
				// m_apNumber[rank][digit]->SetFlash(5,10,D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
			}
		}
	}
}
//===============================
// �`�揈��
//===============================
void CRankingScore::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �g���Ă��錅�����̕`��
	for (int nRankData = 0; nRankData < RANKING_MAX; nRankData++)
	{
		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			// �i���o�[�`��
			m_apNumber[nRankData][nCnt]->Draw();
		}
	}
}
//===============================
// �ǂݍ��ݏ���
//===============================
void CRankingScore::Load(void)
{
	// �J���t�@�C���ݒ�
	std::ifstream LoadFile("data\\Loader\\RankScore.txt");

	if (LoadFile.is_open())
	{
		// �X�R�A��5�����ǂݍ���
		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			if (!(LoadFile >> m_aRankScore[nCnt]))
			{
				m_aRankScore[nCnt] = 0; // ����Ȃ�������0�_
			}
		}

		// �t�@�C�������
		LoadFile.close();
	}
	else
	{
		MessageBox(NULL, "RankScore.txt ���J���܂���ł���", "�G���[", MB_OK);
	}
}
//===============================
// �e�N�X�`�����蓖�ď���
//===============================
void CRankingScore::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\num001.png");
}
