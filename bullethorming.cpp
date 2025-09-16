//======================================================
//
// �e�̃I�u�W�F�N�g�z�[�~���O���� [ bullethorming.cpp ]
// Author: Asuma Nishio
//
//======================================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "bullethorming.h"
#include "manager.h"
#include "player.h"
#include "playerstate.h"
#include "particle.h"
#include "barrierdurability.h"

//**************************
// �萔�錾
//**************************
namespace ConstHorming
{
	constexpr float MIN_RANGE = 3.0f;	// �ŏ�����
	constexpr float MOVESPEED = 5.0f;	// �Ǐ]�X�s�[�h
	constexpr float HITRANGE = 70.0f;	// �����蔻�苗��
	constexpr float MIN_UNDER = 50.0f;	// ��������
}

//==================================
// �R���X�g���N�^
//==================================
CBulletHorming::CBulletHorming(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_fRange = NULL;
	m_isHit = false;
}
//==================================
// �f�X�g���N�^
//==================================
CBulletHorming::~CBulletHorming()
{
	// ����
}
//==================================
// ��������
//==================================
CBulletHorming* CBulletHorming::Create(const char * pFileName,D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CBulletHorming* pBulletHorming = new CBulletHorming;

	// null�`�F�b�N
	if (pBulletHorming == nullptr)
		return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBulletHorming->SetFilePass(pFileName);
	pBulletHorming->SetPos(pos);

	// ���������s��
	if (FAILED(pBulletHorming->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pBulletHorming;
}
//==================================
// ����������
//==================================
HRESULT CBulletHorming::Init(void)
{
	// X�t�@�C���I�u�W�F�N�g����������
	CObjectX::Init();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CBulletHorming::Uninit(void)
{
	// X�t�@�C���I�u�W�F�N�g�I������
	CObjectX::Uninit();
}
//==================================
// �X�V����
//==================================
void CBulletHorming::Update(void)
{
	// ���݂̍��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;			// null�������珈�����Ƃ����Ȃ�

	// �����蔻�菈��
	CollisionAll();

	// ���W���擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	// �v���C���[�ƒe�̃x�N�g���𐶐�
	D3DXVECTOR3 VecPlayer = PlayerPos - NowPos;

	// �x�N�g���̒����擾
	float fLength = D3DXVec3Length(&VecPlayer);

	// ���ꂷ���Ă�����Ǐ]���Ȃ��悤�ɂ���
	m_fRange = ConstHorming::MIN_RANGE;

	// �Ǐ]���������菬�����Ȃ�����Ǐ]���Ȃ�
	if (fLength < m_fRange) return;

	// �x�N�g���𐳋K������
	D3DXVec3Normalize(&VecPlayer, &VecPlayer);

	// �e�̈ړ����x��ݒ肷��
	float fMove = ConstHorming::MOVESPEED;

	// �ړ��x�N�g�������Z
	NowPos += VecPlayer * fMove;

	// �n�ʈȉ��ɂȂ�Ȃ��悤�ɂ���
	if (NowPos.y <= PlayerPos.y + ConstHorming::MIN_UNDER)
	{
		// ���W����
		NowPos.y = PlayerPos.y + ConstHorming::MIN_UNDER;
	}

	// ���݂̍��W�ɃZ�b�g����
	SetPos(NowPos);
}
//==================================
// �`�揈��
//==================================
void CBulletHorming::Draw(void)
{
	// X�t�@�C���I�u�W�F�N�g�`�揈��
	CObjectX::Draw();
}
//==================================
// �S�����蔻�菈���֐�
//==================================
void CBulletHorming::CollisionAll(void)
{
	// ���݂̍��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (pPlayer == nullptr) return;			// null�������珈�����Ƃ����Ȃ�

	// ���W���擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	//===============================
	// �e���g�ƃv���C���[�̏Փ˔���
	//===============================
	if (Collision(PlayerPos))
	{
		if (!m_isHit)
		{
			// �_���[�W�ύX
			pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_DAMAGE);

			// �X�e�[�g�ύX
			pPlayer->ChangeState(new CPlayerStateDamage(1), CPlayerStateBase::ID_DAMAGE);

			// �p�[�e�B�N������
			CParticle::Create(D3DXVECTOR3(PlayerPos.x, 20.0f, PlayerPos.z), COLOR_GREEN, 100, 30, 60, 100);

			// �t���O��L����
			m_isHit = true;

			// �����Ŕ�����
			return;
		}
	}

	//===============================
	// �e���g�ƃo���A�Ƃ̏Փ˔���
	//===============================

	// �I�u�W�F�N�g�擾
	CObject* pObj = CObject::GetTop(static_cast<int>(CObject::PRIORITY::MODELOBJECT));

	// nullptr����Ȃ��Ƃ�
	while (pObj != nullptr)
	{
		// ���b�V���^�C�v���擾
		if (pObj->GetObjType() == CObject::TYPE_BARRIER)
		{
			// �o���A�ɃL���X�g
			CBarrierDurability* pBarrier = static_cast<CBarrierDurability*>(pObj);

			// �o���A���W
			D3DXVECTOR3 BarrierPos = pBarrier->GetPos();

			// �R���W��������
			if (pBarrier->Collision(&NowPos))
			{
				// �o���b�g����
				CBulletHorming::Uninit();

				// while�I��
				break;
			}
		}

		// ���̃I�u�W�F�N�g�����o����
		pObj = pObj->GetNext();
	}
}
//==================================
// �����蔻�菈��
//==================================
bool CBulletHorming::Collision(D3DXVECTOR3 DestPos)
{
	// �e�̌��݈ʒu���擾
	D3DXVECTOR3 BulletPos = GetPos();

	// �x�N�g�����v�Z
	D3DXVECTOR3 vec = DestPos - BulletPos;

	// ���������߂�
	float fDistance = D3DXVec3Length(&vec);

	// �q�b�g���蔼�a
	const float fHitRadius = ConstHorming::HITRANGE;

	// �������q�b�g���a�ȓ��Ȃ瓖����
	if (fDistance <= fHitRadius)
	{
		// �I�u�W�F�N�g������
		Uninit();

		// �����蔻���Ԃ�
		return true; 
	}

	return false; // ������Ȃ�
}