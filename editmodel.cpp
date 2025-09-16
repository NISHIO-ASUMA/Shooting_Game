//======================================
//
// 編集用モデル処理 [ edimodel.cpp ]
// Author: Asuma Nishio
//
//======================================

//**********************
// インクルードファイル
//**********************
#include "editmodel.h"
#include "manager.h"
#include "modellist.h"
#include "editmanager.h"

//=============================
// コンストラクタ
//=============================
CEditModel::CEditModel(int nPriority) : CObject(nPriority)
{
	// 値のクリア
	m_pos = VECTOR3_NULL;
	m_rot = VECTOR3_NULL;
	m_mtxworld = {};
	m_nIdxObj = NULL;
}
//=============================
// デストラクタ
//=============================
CEditModel::~CEditModel()
{
	// 無し
}
//=============================
// 生成
//=============================
CEditModel* CEditModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// インスタンス生成	
	CEditModel* pEdit = new CEditModel;

	// nullなら
	if (pEdit == nullptr) return nullptr;

	// 初期化失敗時
	if (FAILED(pEdit->Init()))
	{
		return nullptr;
	}

	// 生成されるポインタを返す
	return pEdit;
}
//=============================
// 初期化処理
//=============================
HRESULT CEditModel::Init(void)
{
	// メンバ変数の初期化
	m_nIdxObj = 0;

	// 初期化結果
	return S_OK;
}
//=============================
// 終了処理
//=============================
void CEditModel::Uninit(void)
{
	// 自身の破棄
	CObject::Release();
}
//=============================
// 更新処理
//=============================
void CEditModel::Update(void)
{

}
//=============================
// 描画処理
//=============================
void CEditModel::Draw(void)
{
#if 0
	// リスト取得
	CModelList* pModelList = CEditManager::GetList();

	// 配置したモデルのインデックスを取得
	int nIdx = m_nIdxObj;

	// 範囲チェック
	auto modelInfoVec = pModelList->GetInfo();

	if (nIdx < 0 || nIdx >= (int)modelInfoVec.size()) return;

	// モデル情報を取得
	CModelList::MODELINFO& info = modelInfoVec[nIdx];

	// デバイスポインタを宣言
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 計算用のマトリックスを宣言
	D3DXMATRIX mtxRot, mtxTrans;

	// 現在のマテリアルを保存
	D3DMATERIAL9 matDef;

	// マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxworld);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// 現在のマトリックスの取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)info.pBuffMat->GetBufferPointer();

	// マテリアル数だけ回す
	for (int nCntMat = 0; nCntMat < (int)info.dwNumMat; nCntMat++)
	{
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// マテリアル設定
		pDevice->SetMaterial(&Col.MatD3D);

		// モデル(パーツ)の描画
		info.pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを戻す
	pDevice->SetMaterial(&matDef);
#endif
}
