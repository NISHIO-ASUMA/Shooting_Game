//========================================
//
// ハンドエフェクト処理 [ handeffect.cpp ]
// Author: Asuma Nishio
//
//========================================

//**********************
// インクルードファイル
//**********************
#include "handeffect.h"
#include "manager.h"
#include "texture.h"

//==============================
// オーバーロードコンストラクタ
//==============================
CHandEffect::CHandEffect(int nPriority) : CBillboard(nPriority)
{
	// 値のクリア
	m_nIdxTexture = NULL;
	m_nLife = NULL;
	m_fRadius = NULL;
	m_move = VECTOR3_NULL;

}
//==============================
// デストラクタ
//==============================
CHandEffect::~CHandEffect()
{

}
//==============================
// 生成処理
//==============================
CHandEffect* CHandEffect::Create(D3DXVECTOR3 pos, D3DXCOLOR col, D3DXVECTOR3 move, int nLife, float fRadius)
{
	// エフェクトポインタ
	CHandEffect* pEffect = new CHandEffect;

	// nullptrだったら
	if (pEffect == nullptr) return nullptr;

	// テクスチャセット
	pEffect->SetTexture();

	// 初期化に失敗したら
	if (FAILED(pEffect->Init()))
	{
		return nullptr;
	}

	// 3Dオブジェクトセット
	pEffect->SetSize(fRadius, fRadius);
	pEffect->SetPos(pos);
	pEffect->SetCol(col);

	// メンバ変数に代入
	pEffect->m_fRadius = fRadius;
	pEffect->m_move = move;
	pEffect->m_nLife = nLife;

	// エフェクトポインタを返す
	return pEffect;
}
//==============================
// 初期化処理
//==============================
HRESULT CHandEffect::Init(void)
{
	// 親クラスの初期化
	CBillboard::Init();

	return S_OK;
}
//==============================
// 終了処理
//==============================
void CHandEffect::Uninit(void)
{
	// 親クラスの終了
	CBillboard::Uninit();
}
//==============================
// 更新処理
//==============================
void CHandEffect::Update(void)
{
	// 座標,カラー取得
	D3DXVECTOR3 Effectpos = GetPos();

	//カラーの設定
	D3DXCOLOR col = GetCol();

	// オブジェクト更新
	CBillboard::Update();

	// 移動量の更新
	Effectpos += m_move;

	// 半径をデクリメント
	m_fRadius -= 0.015f;

	// α値を減少
	col.a -= 0.005f;

	// 座標をセットする
	SetPos(Effectpos);

	// 色
	SetCol(col);

	if (m_fRadius <= 0.0f)
	{
		m_fRadius = 0.0f;
	}

	// サイズセット
	SetSize(m_fRadius, m_fRadius);

	// 体力を減らす
	m_nLife--;

	// 0以下の時
	if (m_nLife <= 0)
	{
		// 削除する
		Uninit();
	}
}
//==============================
// 描画処理
//==============================
void CHandEffect::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャセット
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// αブレンディングの加算合成
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// αテストを有効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// Zテストを適用
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ビルボード描画
	CBillboard::Draw();

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// αブレンディングを戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Zテストを戻す
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}
//==============================
// テクスチャ割り当て処理
//==============================
void CHandEffect::SetTexture(void)
{
	// テクスチャポインタ取得
	CTexture* pTexture = CManager::GetTexture();

	// テクスチャを登録する
	m_nIdxTexture = pTexture->Register("data\\TEXTURE\\handeffect.jpg");
}