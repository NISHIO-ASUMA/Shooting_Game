//=========================================
//
// �J�����쐬�V�[������ [ cameramode.h ]
// Author: Asuma Nishio
//
//=========================================

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "cameramode.h"
#include "tutorialboss.h"
#include "meshfield.h"
#include "meshdome.h"
#include "block.h"

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CCameraMode::CCameraMode() : CScene(CScene::MODE_CAMERAEDIT)
{
	// �l�̃N���A
}
//==============================
// �f�X�g���N�^
//==============================
CCameraMode::~CCameraMode()
{

}
//==============================
// ��������
//==============================
CCameraMode* CCameraMode::Create(void)
{
	// �C���X�^���X����
	CCameraMode* pCameraMode = new CCameraMode;
	if (pCameraMode == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pCameraMode->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pCameraMode;
}
//==============================
// ����������
//==============================
HRESULT CCameraMode::Init(void)
{
	// �{�X����
	CTutorialBoss::Create(D3DXVECTOR3(0.0f, -600.0f, 0.0f));

	// �t�B�[���h����
	CMeshField::Create(D3DXVECTOR3(0.0f, -95.0f, 0.0f), 2000.0f);

	// ��������
	CMeshDome::Create(D3DXVECTOR3(0.0f, 50.0f, 0.0f), 1200.0f);
	CMeshDome::Create(D3DXVECTOR3(0.0f, -70.0f, 0.0f), 890.0f);

	// �u���b�N����
	CBlock::Create("data\\MODEL\\STAGEOBJ\\Field000.x", D3DXVECTOR3(0.0f, -90.0f, 0.0f), VECTOR3_NULL, 80.0f, 0);

	return S_OK;
}
//==============================
// �I������
//==============================
void CCameraMode::Uninit(void)
{
	// ����
}
//==============================
// �X�V����
//==============================
void CCameraMode::Update(void)
{
	// ����
}
//==============================
// �`�揈��
//==============================
void CCameraMode::Draw(void)
{
	// ����
}