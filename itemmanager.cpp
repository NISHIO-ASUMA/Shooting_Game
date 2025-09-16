//============================================
//
// �A�C�e���Ǘ����� [ itemmanager.cpp ]
// Author : Asuma Nishio
//
//============================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "itemmanager.h"
#include "gamemanager.h"
#include "time.h"
#include "item.h"

//=================================
// �R���X�g���N�^
//=================================
CItemManager::CItemManager()
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CItemManager::~CItemManager()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CItemManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CItemManager::Uninit(void)
{
	// �e��I������
}
//=================================
// �X�V����
//=================================
void CItemManager::Update(void)
{
	// �^�C�}�[�N���X�擾
	CTime* pTime = CGameManager::GetTime();

	// null�Ȃ�
	if (pTime == nullptr) return;

	// �^�C�}�[���擾
	int NowTime = pTime->GetAllTime();

	// �ŏI�o�����Ԃ�ێ�
	static int lastSpawnTime = -1;

	// 7�b���Ƃɐ���
	if (NowTime % 7 == 0 && NowTime != lastSpawnTime)
	{
		// �����_������
		int nActivePos = rand() % NUMPOINT;
		int nTypeItem = rand() % CItem::TYPE_MAX;

		// �A�C�e������
		CItem::Create(m_ActivePointPos[nActivePos], VECTOR3_NULL, nTypeItem);

		// ���Ԃ���
		lastSpawnTime = NowTime;
	}
}
