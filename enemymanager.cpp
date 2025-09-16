//=====================================
//
// �G�̊Ǘ����s�� [ enemymanager.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "enemymanager.h"
#include "input.h"
#include "debugproc.h"
#include "manager.h"

//**************************************
// �R���X�g���N�^
//**************************************
CEnemymanager::CEnemymanager()
{
	// �l�̃N���A
	m_nManagEnemy = 0;
}
//**************************************
// �f�X�g���N�^
//**************************************
CEnemymanager::~CEnemymanager()
{
	// ����
}
//**************************************
// ����
//**************************************
void CEnemymanager::Create(void)
{
	// �G�̐���
	//CEnemy::Create(D3DXVECTOR3(500.0f,300.0f,0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),CEnemy::ENEMYTYPE_FACE);
	//CEnemy::Create(D3DXVECTOR3(800.0f, 600.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);

}
//**************************************
// �I��
//**************************************
void CEnemymanager::Uninit(void)
{
	// ����
}
//**************************************
// �X�V
//**************************************
void CEnemymanager::Update(void)
{
	// �L�[�{�[�h�ւ̃|�C���^���擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// ���݂̓G�̑������擾
	m_nManagEnemy = CEnemy::GetEnemy();

	if (m_nManagEnemy <= 0 && pInput->GetTrigger(DIK_M))
	{
		//// �G�̐���
		//CEnemy::Create(D3DXVECTOR3(200.0f, 300.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_FACE);
		//CEnemy::Create(D3DXVECTOR3(400.0f, 500.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);
		//CEnemy::Create(D3DXVECTOR3(600.0f, 250.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_FACE);
		//CEnemy::Create(D3DXVECTOR3(800.0f, 100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CEnemy::ENEMYTYPE_GOLD);
	}
}
//**************************************
// �`��
//**************************************
void CEnemymanager::Draw(void)
{
	// // �f�o�b�O�t�H���g�̕`��
	// CDebugproc::Print("�G�̐� ( %d )", m_nManagEnemy);
	// 
	// // �`��
	// CDebugproc::Draw(0, 40);
}
