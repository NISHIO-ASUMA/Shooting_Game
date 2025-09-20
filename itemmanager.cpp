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

	// 20�b���Ƃɐ���
	if (NowTime % 20 == 0 && NowTime != lastSpawnTime)
	{
		// �o�����W�����_������
		int nActivePos = rand() % NUMPOINT;

		// �A�C�e���̏o��������8:2�ɂ���
		int nRand = rand() % 10;
		int nTypeItem = 0;

		if (nRand < 8)
		{// 80%�ŉ񕜃A�C�e��
			nTypeItem = CItem::TYPE_LIFE;
		}
		else
		{// �V�[���h�A�C�e��
			nTypeItem = CItem::TYPE_GUARD;
		}

		// �A�C�e������
		CItem::Create(m_ActivePointPos[nActivePos], VECTOR3_NULL, nTypeItem);

		// ���Ԃ���
		lastSpawnTime = NowTime;
	}
}