//=======================================
//
// ���U���g�X�R�A���� [ resultscore.h ]
// Author: Asuma Nishio
// 
//=======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "resultscore.h"
#include "manager.h"
#include "texture.h"

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

	m_fScale = 20.0f;		// �ŏ��͑傫��
	m_fTargetScale = 1.0f;	// �ʏ�T�C�Y
	m_fScaleSpeed = 0.7f;	// �k�����x

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
	}

	// �e�N�X�`���Z�b�g
	SetTexture();

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
	float ease = 0.2f; // ��Ԃ̒l
	m_pos.x += (m_DestPos.x - m_pos.x) * ease;
	m_pos.y += (m_DestPos.y - m_pos.y) * ease;

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
		// �e�N�X�`���Z�b�g
		pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

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
	int nScores[NUM_SAVESCORE] = { NULL };

	// �J�E���g�p
	int nCnt = 0;

	// �����̃X�R�A��ǂݍ���
	std::ifstream inFile("data\\Loader\\RankScore.txt");

	// �t�@�C�����J������
	if (inFile.is_open())
	{
		// �J�E���g���ő�l�ȉ�
		while (nCnt < NUM_SAVESCORE && inFile >> nScores[nCnt])
		{
			// �J�E���g��i�߂�
			nCnt++;
		}

		// �t�@�C�������
		inFile.close();
	}

	// ����̃X�R�A��ǉ�����
	if (nCnt < NUM_SAVESCORE)
	{
		// �z��Ɉꎞ�ۑ�
		nScores[nCnt++] = m_nLastScore;
	}
	else
	{
		// �Ō�ɓ����
		nScores[NUM_SAVESCORE - 1] = m_nLastScore;
	}

	// �o�u���\�[�g
	for (int nCntScore = 0; nCntScore < nCnt - 1; nCntScore++)
	{
		for (int nCnt1 = nCntScore + 1; nCnt1 < nCnt; nCnt1++)
		{
			if (nScores[nCntScore] < nScores[nCnt1])
			{
				// �l���������Ȃ����ւ�
				int nDestScore = nScores[nCntScore];
				nScores[nCntScore] = nScores[nCnt1];
				nScores[nCnt1] = nDestScore;
			}
		}
	}

	// ���5���ɍi��
	// �t�@�C���ɏ����o��
	std::ofstream outFile("data\\Loader\\RankScore.txt");

	// �J������
	if (outFile.is_open())
	{
		// �����o������
		for (int nCntScore = 0; nCntScore < NUM_SAVESCORE; nCntScore++)
		{
			outFile << nScores[nCntScore] << std::endl;
		}

		// �t�@�C�������
		outFile.close();
	}
	else
	{
		MessageBox(NULL, "RankScore.txt ���J���܂���ł���", "�G���[", MB_OK);
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
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\ResultScore.png");
}
//================================
// �N���A�^�C���̃X�R�A���v�Z
//================================
int CResultScore::MathTimescore(void)
{
	// �ǂݍ��񂾒l
	float fValue = (float)m_nTimeScore;

	// ����0�Ȃ�
	if (m_nTimeScore == 0)
	{
		// 0��Ԃ�
		return 0;
	}

	// ����l
	const float fMaxReadValue = 120.0f;

	// �ő�X�R�A
	const int nMaxTimeScore = 50000;

	// �䗦���Z�o
	float fRatio = 1.0f - (fValue / fMaxReadValue);

	// �͈͕␳
	if (fRatio < 0.0f) fRatio = 0.0f;
	if (fRatio > 1.0f) fRatio = 1.0f;

	// �X�R�A�v�Z
	int nMathscore = (int)(nMaxTimeScore * fRatio);

	return nMathscore;
}
