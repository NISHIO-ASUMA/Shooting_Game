//============================================
//
// プレイヤー体力処理 [ playerlifegage.cpp ]
// Author: Asuma Nishio
// 
// TODO : 振動処理入れる
//
//============================================

//**********************
// インクルードファイル
//**********************
#include "playerlifegage.h"
#include "player.h"
#include "parameter.h"
#include "manager.h"
#include "texture.h"
#include "object2D.h"

//*************************
// 定数宣言
//*************************
namespace PLAYERLIFEINFO
{
	constexpr float GAGE_HEIGHT = 45.0f; // ゲージの高さの固定
	constexpr float VALUELENGTH = 0.28f; // 長さの倍率
	constexpr float SHAKEFLOAT = 25.0f; // 振れ幅の初期値
	constexpr float DIGIT = 40.0f;		// 計算変数
	constexpr float RANDOMDIGIT = 100.0f; // ランダムの割る値
	constexpr int SHAKEVALUE = 40;	// 振動の値
	constexpr int RANDOM_MAX = 400; // 最大値
	constexpr int RANDOM_MIN = 100; // 最小値
};

//========================
// コンストラクタ
//========================
CPlayerLifeGage::CPlayerLifeGage(int nPriority) : CGage(nPriority)
{
	// 値のクリア
	m_pPlayer = nullptr;
	m_nLifeLength = NULL;
	m_gage = GAGE_FRAME;
	m_nMaxLifeLength = NULL;
	m_nMaxLife = NULL;
	m_isShake = false;
	m_nShakeTimer = NULL;
	m_fShakeAmplitude = NULL;
	m_fShakeOffset = NULL;
	m_basePos = VECTOR3_NULL;
}
//========================
// デストラクタ
//========================
CPlayerLifeGage::~CPlayerLifeGage()
{
	// 無し
}
//========================
// 初期化処理
//========================
HRESULT CPlayerLifeGage::Init(void)
{
	// 親クラスの初期化処理
	CObject2D::Init();

	// nullだったら
	if (m_pPlayer == nullptr)
	{
		// プレイヤー取得
		m_pPlayer = CPlayer::GetIdxPlayer(0);
	}

	// 取得できたら
	if (m_pPlayer != nullptr)
	{
		// パラメーター取得
		CParameter* pParam = m_pPlayer->GetParameter();

		// 現在の体力を取得する
		m_nMaxLifeLength = pParam->GetHp();

		// 最大値を保存しておく
		m_nMaxLife = pParam->GetHp();
	}

	// 初期化結果を返す
	return S_OK;
}
//========================
// 終了処理
//========================
void CPlayerLifeGage::Uninit(void)
{
	// 親クラスの終了処理
	CObject2D::Uninit();
}
//========================
// 更新処理
//========================
void CPlayerLifeGage::Update(void)
{
	// パラメーター取得
	CParameter* pParam = m_pPlayer->GetParameter();

	// nullじゃない かつ 種類がバーの時
	if (m_pPlayer != nullptr && m_gage == GAGE_BAR)
	{
		// 現在の体力を取得する
		m_nLifeLength = pParam->GetHp();

		// ゲージの長さ設定
		SetGageLength(m_nMaxLifeLength, m_nLifeLength, PLAYERLIFEINFO::VALUELENGTH, PLAYERLIFEINFO::GAGE_HEIGHT);
	}

	if (m_pPlayer != nullptr)
	{
		// ダメージを負ったフラグが有効時
		if (m_pPlayer->GetIsDamege() && !m_isShake)
		{
			// 振動ON
			m_isShake = true;

			// フレーム振動
			m_nShakeTimer = PLAYERLIFEINFO::SHAKEVALUE;

			// 振れ幅の初期値
			m_fShakeAmplitude = PLAYERLIFEINFO::SHAKEFLOAT;
		}

		if (m_isShake)
		{
			// 差分を計算
			float t = (PLAYERLIFEINFO::SHAKEVALUE - m_nShakeTimer) / PLAYERLIFEINFO::DIGIT;

			// 減衰量を計算
			float decay = (1.0f - t);

			// ランダム値を設定
			float randX = (rand() % PLAYERLIFEINFO::RANDOM_MAX - PLAYERLIFEINFO::RANDOM_MIN) / PLAYERLIFEINFO::RANDOMDIGIT;
			float randY = (rand() % PLAYERLIFEINFO::RANDOM_MAX - PLAYERLIFEINFO::RANDOM_MIN) / PLAYERLIFEINFO::RANDOMDIGIT;

			// 座標を計算
			float fOffsetX = randX * m_fShakeAmplitude * decay;
			float fOffsetY = randY * m_fShakeAmplitude * decay;

			// 座標にセット
			SetPos(m_basePos + D3DXVECTOR3(fOffsetX, fOffsetY, 0.0f));

			// 振動時間を減らす
			m_nShakeTimer--;

			if (m_nShakeTimer <= NULL)
			{
				// フラグを無効化
				m_isShake = false;
				m_nShakeTimer = NULL;

				// 判定を無効化
				m_pPlayer->SetIsDamege(false);

				// 基準座標へ戻す
				SetPos(m_basePos);
			}
		}
		else
		{
			// 基準座標に固定
			SetPos(m_basePos);
		}

		// 親クラスの更新処理
		CObject2D::Update();
	}
}
//========================
// 描画処理
//========================
void CPlayerLifeGage::Draw(void)
{
	// 親クラスの描画
	CObject2D::Draw();
}
//========================
// 生成処理
//========================
CPlayerLifeGage* CPlayerLifeGage::Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int gagetype, const char* pTexName)
{
	// インスタンス生成
	CPlayerLifeGage* pLifeGage = new CPlayerLifeGage;

	// nullだったら
	if (pLifeGage == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pLifeGage->Init()))
	{
		// nullを返す
		return nullptr;
	}

	// 2Dオブジェクト設定
	pLifeGage->SetPos(pos);
	pLifeGage->m_basePos = pos;
	pLifeGage->SetSize(fWidth, fHeight);
	pLifeGage->SetGage(gagetype);
	pLifeGage->SetTexture(pTexName);
	pLifeGage->SetAnchor(ANCHORTYPE_LEFTSIDE);

	// 生成されたポインタを返す
	return pLifeGage;
}
