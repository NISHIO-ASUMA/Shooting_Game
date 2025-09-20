//===================================
//
// �A�C�e������ [ item.cpp ]
// Author: Asuma Nishio
//
//===================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "item.h"
#include "barrierdurability.h"
#include "template.h"
#include "sound.h"
#include "manager.h"
#include "barriermanager.h"
#include "gamemanager.h"
#include "player.h"
#include "parameter.h"
#include "particle.h"

//**************************
// ���O���
//**************************
namespace ITEMINFO
{
	constexpr int UPPER_HP = 2;		  // �̗͂̉��Z��
	constexpr float HITRANGE = 75.0f; // �����蔼�a�͈̔�
	constexpr float ROTVALUE = 0.03f; // ��]�p�̉��Z��
	constexpr const char* GUARDMODEL = "data\\MODEL\\STAGEOBJ\\Guard000.x";
	constexpr const char* LIFEMOODEL = "data\\MODEL\\STAGEOBJ\\Item_life.x";
};

//=================================
// �I�[�o�[���[�h�R���X�g���N�^
//=================================
CItem::CItem(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
}
//=================================
// �f�X�g���N�^
//=================================
CItem::~CItem()
{
	// ����
}
//=================================
// ��������
//=================================
CItem* CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	// �C���X�^���X����
	CItem* pItem = new CItem;

	// null�Ȃ�
	if (pItem == nullptr) return nullptr;

	// ��ސݒ�
	pItem->m_nType = nType;

	// �t�@�C�����Z�b�g
	switch (nType)
	{
	case TYPE_GUARD:	// �h��
		pItem->SetFilePass(ITEMINFO::GUARDMODEL);
		break;

	case TYPE_LIFE:		// ��
		pItem->SetFilePass(ITEMINFO::LIFEMOODEL);
		break;

	default:
		break;
	}

	pItem->SetPos(pos);
	pItem->SetRot(rot);

	// ���������s��
	if (FAILED(pItem->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^
	return pItem;
}
//=================================
// ����������
//=================================
HRESULT CItem::Init(void)
{
	// �e�N���X�̏���������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(TYPE_ITEM);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CItem::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//=================================
// �X�V����
//=================================
void CItem::Update(void)
{
	// ���݂̊p�x���擾
	D3DXVECTOR3 rot = GetRot();

	// ��]�p�����Z
	rot.y += ITEMINFO::ROTVALUE;

	// �p�x���K���֐�
	rot.y = NormalAngle(rot.y);

	// �p�x�Z�b�g
	SetRot(rot);
}
//=================================
// �`�揈��
//=================================
void CItem::Draw(void)
{
	// �e�N���X�̕`�揈��
	CObjectX::Draw();
}
//=================================
// �����蔻�菈��
//=================================
bool CItem::Collision(D3DXVECTOR3* pPos)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �R���W������������̒������v�Z
	D3DXVECTOR3 CollisionPos = NowPos - *pPos;

	// �����̒������Z�o
	float fRange = D3DXVec3Length(&CollisionPos);

	// �q�b�g���a�����������l�ɂȂ�����
	if (fRange <= ITEMINFO::HITRANGE)
	{
		// �T�E���h�̃|�C���^���擾
		CSound* pSound = CManager::GetSound();
		if (pSound == nullptr) return false;

		// �Ώۂ̃I�u�W�F�N�g����
		Uninit();
		
		// �p�[�e�B�N������
		CParticle::Create(D3DXVECTOR3(pPos->x, pPos->y + 10.0f, pPos->z), D3DCOLOR_RGBA(127, 255, 0, 255),100,200,200,120);

		switch (m_nType)
		{
		case TYPE_GUARD:
		{
			// �o���A�}�l�[�W�����擾
			CBarrierManager* pBarrierMgr = CGameManager::GetBarrier();

			// null����Ȃ�������
			if (pBarrierMgr != nullptr)
			{
				// �o���A���Z
				pBarrierMgr->AddBarrier(1, *pPos, 50.0f);
			}

			// �T�E���h�Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_ITEM);
		}
			break;

		case TYPE_LIFE:
		{
			// �v���C���[�擾
			CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);

			// null�Ȃ�
			if (pPlayer == nullptr) return false;

			// �p�����[�^�[�擾
			CParameter* pParam = pPlayer->GetParameter();
			int nHp = pParam->GetHp();

			// �̗͒l�����Z
			nHp += ITEMINFO::UPPER_HP;

			// �ő�l�I�[�o�[�̎�
			if (nHp >= pPlayer->GetParameter()->GetMaxHp())
			{
				nHp = pPlayer->GetParameter()->GetMaxHp();
			}

			// �Z�b�g
			pPlayer->GetParameter()->SetHp(nHp);

			// �T�E���h�Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_LIFE);

		}
		break;

		default:
			break;
		}

		// �q�b�g�����Ԃ�
		return true;
	}

	// �������ĂȂ��Ƃ�
	return false;
}
