//=========================================
//
// サブプレイヤー処理 [ subplayer.h ]
// Author: Asuma Nishio
//
//=========================================

//**********************
// インクルードファイル
//**********************
#include "subplayer.h"

//=================================
// コンストラクタ
//=================================
CSubPlayer::CSubPlayer(int nPriority) : CObject(nPriority)
{

}
//=================================
// デストラクタ
//=================================
CSubPlayer::~CSubPlayer()
{

}
//=================================
// 生成処理
//=================================
CSubPlayer* CSubPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife)
{
	// インスタンス生成
	CSubPlayer* pSubPlayer = new CSubPlayer;
	if (pSubPlayer == nullptr) return nullptr;


	return pSubPlayer;
}
//=================================
// 初期化処理
//=================================
HRESULT CSubPlayer::Init(void)
{
	return S_OK;
}
//=================================
// 終了処理
//=================================
void CSubPlayer::Uninit(void)
{

}
//=================================
// 更新処理
//=================================
void CSubPlayer::Update(void)
{

}
//=================================
// 描画処理
//=================================
void CSubPlayer::Draw(void)
{

}
