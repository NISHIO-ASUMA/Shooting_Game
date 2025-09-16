//==========================================
//
// ランキングスコア処理 [ rankingscore.cpp ]
// Author: Asuma Nishio
//
//==========================================

//****************************
// インクルードファイル
//****************************
#include "rankingscore.h"
#include "manager.h"
#include "texture.h"
#include "number.h"
#include <algorithm>

//===============================
// オーバーロードコンストラクタ
//===============================
CRankingScore::CRankingScore(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_nIdxTex = NULL;
	m_pos = VECTOR3_NULL;

	for (int nCntData = 0; nCntData < RANKING_MAX; nCntData++)
	{
		// スコアを格納
		m_aRankScore[nCntData] = NULL;

		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			// ナンバーポインタ
			m_apNumber[nCntData][nCnt] = nullptr;
		}
	}
}
//===============================
// デストラクタ
//===============================
CRankingScore::~CRankingScore()
{
	// 無し
}
//===============================
// 生成処理
//===============================
CRankingScore* CRankingScore::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	// インスタンス生成
	CRankingScore* pRankScore = new CRankingScore;
	if (pRankScore == nullptr) return nullptr;

	// オブジェクト
	pRankScore->m_pos = pos; // 目的の座標
	pRankScore->m_fWidth = fWidth;
	pRankScore->m_fHeight = fHeight;

	// 初期化失敗時
	if (FAILED(pRankScore->Init()))
	{
		return nullptr;
	}

	// 生成されたポインタを返す
	return pRankScore;
}
//===============================
// 初期化処理
//===============================
HRESULT CRankingScore::Init(void)
{
	// スコアをロード
	Load();

	// 横幅計算
	float fTexPos = m_fWidth / RANKSCOREDIGIT;

	for (int nRank = 0; nRank < RANKING_MAX; nRank++)
	{
		// 桁数分
		for (int nDigit = 0; nDigit < RANKSCOREDIGIT; nDigit++)
		{
			// インスタンス生成
			m_apNumber[nRank][nDigit] = new CNumber;

			// Y座標をずらす
			float yOffset = m_pos.y + (m_fHeight + 60.0f) * nRank;

			// 初期化処理
			m_apNumber[nRank][nDigit]->Init
			(
				D3DXVECTOR3(m_pos.x - (fTexPos * 2.0f * nDigit), yOffset, 0.0f),
				fTexPos,
				m_fHeight
			);

			// サイズ設定
			m_apNumber[nRank][nDigit]->SetSize(fTexPos, m_fHeight);
		}
	}

	// テクスチャセット
	SetTexture();

	return S_OK;
}
//===============================
// 終了処理
//===============================
void CRankingScore::Uninit(void)
{
	// 使っている桁数分の破棄
	for (int nRankData = 0; nRankData < RANKING_MAX; nRankData++)
	{
		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			if (m_apNumber[nRankData][nCnt] != nullptr)
			{
				// ナンバーの破棄
				m_apNumber[nRankData][nCnt]->Uninit();
				delete m_apNumber[nRankData][nCnt];
				m_apNumber[nRankData][nCnt] = nullptr;
			}
		}
	}

	// 自身の破棄
	CObject::Release();
}
//===============================
// 更新処理
//===============================
void CRankingScore::Update(void)
{
	// スコアの桁数更新
	for (int rank = 0; rank < RANKING_MAX; rank++)
	{
		int score = m_aRankScore[rank];

		for (int digit = 0; digit < RANKSCOREDIGIT; digit++)
		{
			int num = score % 10;  // 1桁取り出す
			score /= 10;

			m_apNumber[rank][digit]->SetDigit(num);
		}
	}
}
//===============================
// 描画処理
//===============================
void CRankingScore::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// 使っている桁数分の描画
	for (int nRankData = 0; nRankData < RANKING_MAX; nRankData++)
	{
		for (int nCnt = 0; nCnt < RANKSCOREDIGIT; nCnt++)
		{
			// テクスチャセット
			pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

			// ナンバー描画
			m_apNumber[nRankData][nCnt]->Draw();
		}
	}
}
//===============================
// 読み込み処理
//===============================
void CRankingScore::Load(void)
{
	std::ifstream LoadFile("data\\Loader\\RankScore.txt");

	if (LoadFile.is_open())
	{
		for (int nCnt = 0; nCnt < RANKING_MAX; nCnt++)
		{
			if (!(LoadFile >> m_aRankScore[nCnt]))
			{
				m_aRankScore[nCnt] = 0; // 足りなかったら0点
			}
		}

		// ファイルを閉じる
		LoadFile.close();

		// 降順にソート
		std::sort(m_aRankScore, m_aRankScore + RANKING_MAX, std::greater<int>());
	}
	else
	{
		MessageBox(NULL, "RankScore.txt が開けませんでした", "エラー", MB_OK);
	}
}
//===============================
// テクスチャ割り当て処理
//===============================
void CRankingScore::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャ割り当て
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\ResultScore.png");
}
