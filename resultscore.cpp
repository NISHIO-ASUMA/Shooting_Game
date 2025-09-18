//=======================================
//
// ���U���g�X�R�A���� [ resultscore.cpp ]
// Author: Asuma Nishio
// 
//=======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "resultscore.h"
#include "manager.h"
#include "texture.h"
#include "rankingscore.h"
#include <algorithm>

//**********************
// ���O���
//**********************
namespace RESULTSCOREINFO
{
	constexpr int MAXSCORE = 40000; // �ő�X�R�A
	constexpr float MAX_VALUESCORE = 120.0f; // �v�Z����
	const char* FILENAME = "data\\Loader\\RankScore.txt"; // �t�@�C���p�X
};

//================================
// �R���X�g���N�^
//================================
CResultScore::CResultScore(int nPriority) : CObject(nPriority)
{
	// �l�̃N���A
	m_nScore = NULL;
	m_nLastScore = NULL;
	m_nTimeScore = NULL;
	m_nIdxTexture = NULL;
	m_nDestLastScore = NULL;
	m_nDestTimeScore = NULL;
	m_nLastScore = NULL;

	m_fScale = NULL;		// �ŏ��͑傫��
	m_fTargetScale = NULL;	// �ʏ�T�C�Y
	m_fScaleSpeed = NULL;	// �k�����x

	m_pos = VECTOR3_NULL;
	m_DestPos = VECTOR3_NULL;

	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		m_apNumber[nCnt] = nullptr;
	}
}
//================================
// �f�X�g���N�^
//================================
CResultScore::~CResultScore()
{
	// ����
}
//================================
// ��������
//================================
CResultScore* CResultScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType)
{
	// �C���X�^���X����
	CResultScore* pResultScore = new CResultScore;
	if (pResultScore == nullptr) return nullptr;

	// ���W,�T�C�Y�ݒ�
	pResultScore->m_DestPos = pos; // �ړI�̍��W

	// ���ォ��X�^�[�g
	const float fOffsetX = -400.0f; // ��
	const float fOffsetY = -800.0f; // ��
	pResultScore->m_pos = pos + D3DXVECTOR3(fOffsetX, fOffsetY, 0.0f);

	pResultScore->m_fWidth = fWidth;
	pResultScore->m_fHeight = fHeight;
	pResultScore->m_nType = nType;

	// ���������s��
	if (FAILED(pResultScore->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pResultScore;
}
//================================
// ����������
//================================
HRESULT CResultScore::Init(void)
{
	// �����v�Z
	float fTexPos = m_fWidth / NUM_RESULTSCORE;

	// ������
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// �C���X�^���X����
		m_apNumber[nCnt] = new CNumber;

		// ���W�ݒ�
		m_apNumber[nCnt]->SetPos(m_pos);

		// ����������
		m_apNumber[nCnt]->Init(D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nCnt), m_pos.y, 0.0f), fTexPos, m_fHeight);

		// �i���o�[�ϐ��̃T�C�Y
		m_apNumber[nCnt]->SetSize(fTexPos, m_fHeight);

		m_apNumber[nCnt]->SetTexture("score001.png");
	}

	m_fScale = 20.0f;		// �ŏ��͑傫��
	m_fTargetScale = 1.0f;	// �ʏ�T�C�Y
	m_fScaleSpeed = 0.7f;	// �k�����x

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CResultScore::Uninit(void)
{
	// �g�������j��
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// nullptr�`�F�b�N
		if (m_apNumber[nCnt] != nullptr)
		{
			// �I��
			m_apNumber[nCnt]->Uninit();

			// �j��
			delete m_apNumber[nCnt];

			// �|�C���^������
			m_apNumber[nCnt] = nullptr;
		}
	}

	// ���g�̔j��
	CObject::Release();
}
//================================
// �X�V����
//================================
void CResultScore::Update(void)
{	
	// ���Z����
	if (m_fScale > m_fTargetScale)
	{
		// ����
		m_fScale -= m_fScaleSpeed;

		// ���������
		if (m_fScale < m_fTargetScale)
			m_fScale = m_fTargetScale;
	}	
	
	// ���W�̃C�[�W���O���
	float fEase = 0.2f; // ��Ԃ̒l
	m_pos.x += (m_DestPos.x - m_pos.x) * fEase;
	m_pos.y += (m_DestPos.y - m_pos.y) * fEase;

	// �X�R�A��ނɂ���Čv�Z��ς���
	switch (m_nType)
	{
	case SCORE_GAME:
	{
		// �X�R�A�i�[
		int nScore = m_nScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigit = nScore % NUM_RESULTDIGIT;

			nScore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigit);

			// ���W���X�V
			D3DXVECTOR3 Pos(
				m_pos.x - ((m_fWidth / NUM_RESULTSCORE) * 2.0f * nCntScore * m_fScale),
				m_pos.y,
				0.0f);
			m_apNumber[nCntScore]->SetPos(Pos);

			// �T�C�Y�X�V
			float fTexPos = (m_fWidth / NUM_RESULTSCORE) * m_fScale;
			float fHeight = m_fHeight * m_fScale;
			m_apNumber[nCntScore]->SetSize(fTexPos, fHeight);
		}
	}
	break;

	case SCORE_TIME:
	{
		// �^�C���p�̃X�R�A�i�[
		int nTimescore = m_nTimeScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigitTime = nTimescore % NUM_RESULTDIGIT;

			nTimescore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigitTime);


			// ���W���X�V
			D3DXVECTOR3 TimescorePos(
				m_pos.x - ((m_fWidth / NUM_RESULTSCORE) * 2.0f * nCntScore * m_fScale),
				m_pos.y,
				0.0f);
			m_apNumber[nCntScore]->SetPos(TimescorePos);

			// �T�C�Y�X�V
			float fTexPos = (m_fWidth / NUM_RESULTSCORE) * m_fScale;
			float fHeight = m_fHeight * m_fScale;
			m_apNumber[nCntScore]->SetSize(fTexPos, fHeight);
		}
	}
	break;

	case SCORE_LAST:
	{
		// �X�R�A�i�[
		int nLastScore = m_nLastScore;

		// ������
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++) // �E���珈��
		{
			// �������Ƃɕ�������l���v�Z
			int nDigitLast = nLastScore % NUM_RESULTDIGIT;

			nLastScore /= NUM_RESULTDIGIT;

			// �i���o�[�X�V
			m_apNumber[nCntScore]->Update();

			// ���X�V
			m_apNumber[nCntScore]->SetDigit(nDigitLast);

			// ���W���X�V
			D3DXVECTOR3 LastscorePos(
				m_pos.x - ((m_fWidth / NUM_RESULTSCORE) * 2.0f * nCntScore * m_fScale),
				m_pos.y,
				0.0f);
			m_apNumber[nCntScore]->SetPos(LastscorePos);

			// �T�C�Y�X�V
			float fTexPos = (m_fWidth / NUM_RESULTSCORE) * m_fScale;
			float fHeight = m_fHeight * m_fScale;
			m_apNumber[nCntScore]->SetSize(fTexPos, fHeight);

			// �J���[�X�V
			m_apNumber[nCntScore]->SetFlash(10,20,COLOR_RED);
		}
	}
	break;

	default:
		break;
	}
}
//================================
// �`�揈��
//================================
void CResultScore::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	CTexture* pTexture = CManager::GetTexture();

	// �g���Ă��錅�����̕`��
	for (int nCnt = 0; nCnt < NUM_RESULTSCORE; nCnt++)
	{
		// �i���o�[�`��
		m_apNumber[nCnt]->Draw();
	}
}
//================================
// �����o������
//================================
void CResultScore::Save(void)
{
	// �ő�5��
	int nScores[NUM_RESULTSCORE] = { NULL };

	// �ǂݍ��݌���
	int nCnt = NULL;

	// �t�@�C������ǂݍ���
	std::ifstream inFile(RESULTSCOREINFO::FILENAME);

	// �t�@�C�����J������
	if (inFile.is_open())
	{
		// 5�����ǂݍ���
		while (nCnt < NUM_RESULTSCORE && inFile >> nScores[nCnt])
		{
			nCnt++;
		}

		// �t�@�C�������
		inFile.close();
	}

	// ����̃X�R�A�������L���O�ɓ���邩����
	if (nCnt < NUM_RESULTSCORE)
	{
		nScores[nCnt++] = m_nLastScore;
	}
	else
	{
		// �ŏ��l��T��
		int nMinData = 0;

		// 1�Ԗڂ���
		for (int nScoreData = 1; nScoreData < NUM_RESULTSCORE; nScoreData++)
		{
			// �X�R�A�̒l���Ⴂ�Ȃ�
			if (nScores[nScoreData] < nScores[nMinData])
			{
				// �z��ԍ��ɑ��
				nMinData = nScoreData;
			}
		}

		// �V�X�R�A���ŏ��l���傫����΍����ւ�
		if (m_nLastScore > nScores[nMinData])
		{
			// �X�R�A���Z�b�g����
			nScores[nMinData] = m_nLastScore;
		}
	}

	// �t�@�C���ɏ����o��
	std::ofstream outFile(RESULTSCOREINFO::FILENAME);

	// �J������
	if (outFile.is_open())
	{
		// ��Ƀ\�[�g�����s
		std::sort(nScores, nScores + NUM_RESULTSCORE, std::greater<int>());

		// �\�[�g��ɏ����o��
		for (int nCntScore = 0; nCntScore < NUM_RESULTSCORE; nCntScore++)
		{
			outFile << nScores[nCntScore] << std::endl;
		}

		// �t�@�C�������
		outFile.close();
	}
	else
	{
		// ��O���b�Z�[�W
		MessageBox(NULL, "RankScore.txt ���J���܂���ł���", "�G���[", MB_OK);
	}

	for (int nCntSave = 0; nCntSave < NUM_RESULTSCORE; nCntSave++)
	{
		// �Y���X�R�A�ƈ�v���Ă�����
		if (nScores[nCntSave] == m_nLastScore)
		{
			// �ŏI�I�ȏ��ʂ��L�^
			CRankingScore::SetRankInScoreIdx(nCntSave);

			break;
		}
	}
}
//================================
// �e�N�X�`������
//================================
void CResultScore::SetTexture(void)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`�����蓖��
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\num001.png");
}
//================================
// �N���A�^�C���̃X�R�A���v�Z
//================================
int CResultScore::MathTimescore(void)
{
	// �ǂݍ��񂾒l
	float fValue = static_cast<float>(m_nTimeScore);

	// ����0�Ȃ� ( �ŏ��N���A�^�C���� )
	if (m_nTimeScore == 0)
	{
		// �ő�l��Ԃ�
		return RESULTSCOREINFO::MAXSCORE;
	}

	// �䗦���Z�o
	float fRatio = 1.0f - (fValue / RESULTSCOREINFO::MAX_VALUESCORE);

	// �͈͓��Ŋ������Z�o
	if (fRatio < 0.0f) fRatio = 0.0f;
	if (fRatio > 1.0f) fRatio = 1.0f;

	// �X�R�A�v�Z
	int nMathscore = (int)(RESULTSCOREINFO::MAXSCORE * fRatio);

	return nMathscore;
}