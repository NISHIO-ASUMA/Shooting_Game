//=============================================
//
// �u���b�N�S�̂̊Ǘ����s�� [ blockmanager.h ]
// Author: Asuma Nishio
//
//==============================================

//*******************************
// �C���N���[�h�t�@�C���錾
//*******************************
#include "blockManager.h"
#include "manager.h"
#include "json.hpp"

//*******************************
// �ÓI�����o�ϐ��錾
//*******************************
std::vector<CBlock*>CBlockManager::m_blocks = {}; // ���I�z��
int CBlockManager::m_nIdxCount = NULL;	// �C���f�b�N�X�J�E���g

//===============================
// �R���X�g���N�^
//===============================
CBlockManager::CBlockManager()
{
	// ����
}
//===============================
// �f�X�g���N�^
//===============================
CBlockManager::~CBlockManager()
{
	// ����
}
//===============================
// ������
//===============================
HRESULT CBlockManager::Init(const char* filename, D3DXVECTOR3 pos)
{
	// �z��������� (�T�C�Y��0�ɂ���)
	m_blocks.clear();

	return S_OK;
}
//===============================
// �I��
//===============================
void CBlockManager::Uninit(void)
{
	// �z�����ɂ��� (�T�C�Y��0�ɂ���)
	m_blocks.clear();
}
//===============================
// �X�V
//===============================
void CBlockManager::Update(void)
{
	// ����
}
//===============================
// ��������
//===============================
CBlock* CBlockManager::Create(const char* pfileName,D3DXVECTOR3 pos,D3DXVECTOR3 rot,float Size)
{
	// �C���X�^���X����
	CBlock* pNewBlock = CBlock::Create(pfileName,pos,rot,Size,0);

	// ������
	if (pNewBlock)
	{
		// �z��ɒǉ�
		m_blocks.push_back(pNewBlock);

		// �C���f�b�N�X
		m_nIdxCount++;

		// �������ꂽ�|�C���^��Ԃ�
		return pNewBlock;
	}
	else
	{
		// ���ɂ��Ȃ��|�C���^��Ԃ�
		return nullptr;
	}
}
