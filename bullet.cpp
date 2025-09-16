//====================================
//
// �e�̏��� [ bullet.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "bullet.h"
#include "manager.h"
#include "enemy.h"
#include "player.h"
#include "effect.h"
#include "boss.h"
#include "particle.h"
#include "gamemanager.h"
#include "effectlaser.h"
#include "charge.h"

//*****************************
// �ÓI�����o�ϐ��錾
//*****************************
CBullet::BTYPE CBullet::m_Type = CBullet::BTYPE_PLAYER; // ���

//*******************************
// �萔�錾
//*******************************
namespace BULLETINFO
{
	constexpr int BULLET_DAMAGE = 1;		// �e�̃_���[�W
	constexpr int ACTIVEEFFECTNUM = 3;		// �o���G�t�F�N�g������
	constexpr int LASER_DAMAGE = 3;			// ���[�U�[�e�̃_���[�W

	constexpr float BULLET_SIZE = 30.0f;	// �e�̃T�C�Y
	constexpr float BULLET_LASER = 30.0f;   // ���[�U�[��
	constexpr float BULLET_NORMAL = 10.0f;	// �ʏ�e�̕�
	constexpr float BULLET_SPEED = 15.0f;	// �i�ޑ��x

	const D3DXVECTOR3 DestPos = { 0.0f,10.0f,0.0f };	// �G�t�F�N�g�o�����W
}

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CBullet::CBullet(int nPriority) : CBillboard(nPriority)
{
	// �l�̃N���A
	m_nLife = NULL;
	m_nIdxTexture = NULL;
	m_move = VECTOR3_NULL;
	m_OldPos = VECTOR3_NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CBullet::~CBullet()
{
	// ����
}
//===============================
// �e�̐���
//===============================
CBullet* CBullet::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, BTYPE nType, const float fWidth, const float fHeight,const int nLife)
{
	// �e�̃C���X�^���X����
	CBullet* pBullet = new CBullet;

	// �C���X�^���X�̐����Ɏ��s������
	if (pBullet == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pBullet->SetTexture(nType);
	pBullet->SetPos(pos);
	pBullet->SetType(nType);
	pBullet->SetSize(fWidth, fHeight);
	pBullet->m_nLife = nLife;

	// �������Ɏ��s������
	if (FAILED(pBullet->Init(rot)))
	{
		// nullptr��Ԃ�
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pBullet;
}
//===============================
// �e�̎�ރZ�b�g
//===============================
void CBullet::SetType(BTYPE type)
{
	// ��ސݒ�
	m_Type = type;
}
//===============================
// ��ނ��Ƃ̃e�N�X�`���Z�b�g
//===============================
void CBullet::SetTexture(BTYPE type)
{
	// �e�N�X�`���|�C���^�擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ݒ�
	switch (type)
	{
	case BTYPE_PLAYER:
		m_nIdxTexture = pTexture->Register("data\\TEXTURE\\bullet002.png");
		break;

	default:
		break;
	}
}
//===============================
// �e�̏�����
//===============================
HRESULT CBullet::Init(D3DXVECTOR3 rot)
{
	// �e�N���X�̏�����
	CBillboard::Init();

	// �I�u�W�F�N�g�̎�ނ�ݒ肷��
	SetObjType(TYPE_BULLET);

	// �ړ��ʂ��v�Z
	m_move = D3DXVECTOR3(rot.x * BULLETINFO::BULLET_SPEED, rot.y,rot.z * BULLETINFO::BULLET_SPEED);

	// �T�E���h�擾
	CSound* pSound = CManager::GetSound();
	
	// �����ɃT�E���h�̃^�C�v
	switch (m_Type)
	{
	case CBullet::BTYPE_PLAYER:
		pSound->PlaySound(CSound::SOUND_LABEL_BULLET);
		break;

	case CBullet::BTYPE_LASER:
		pSound->PlaySound(CSound::SOUND_LABEL_LASER);
		break;

	default:
		break;
	}

	return S_OK;
}
//===============================
// �e�̏I��
//===============================
void CBullet::Uninit(void)
{
	// �e�N���X�̔j��
	CBillboard::Uninit();
}
//===============================
// �e�̍X�V
//===============================
void CBullet::Update(void)
{
	// �e�̍��W���擾
	D3DXVECTOR3 BulletPos = GetPos();

	// ���������X�Ɍ��炷
	m_nLife--;
	
	// �ߋ��̍��W��ێ�����
	m_OldPos = BulletPos;

	for (int nCnt = 0; nCnt < BULLETINFO::ACTIVEEFFECTNUM; nCnt++)
	{
		// ����
		D3DXVECTOR3 VecMove = m_OldPos - BulletPos;

		// ����
		float fRate = static_cast<float>(nCnt) / BULLETINFO::ACTIVEEFFECTNUM;

		// �ŏI�ړ���
		D3DXVECTOR3 DestMove = m_OldPos + VecMove * fRate;

		switch (m_Type)
		{
		case BTYPE_PLAYER:
			// �ʏ�G�t�F�N�g
			CEffect::Create(DestMove, COLOR_PURPLE, VECTOR3_NULL, m_nLife, BULLETINFO::BULLET_NORMAL);
			break;

		case BTYPE::BTYPE_LASER:
			// ���[�U�[�G�t�F�N�g����
			 CEffectLaser::Create(DestMove, BULLETINFO::DestPos, LASER, VECTOR3_NULL, m_nLife, BULLETINFO::BULLET_LASER);
			break;

		default:
			break;
		}

	}

	// �ʒu���X�V
	BulletPos += m_move;

	// ���W���X�V
	SetPos(BulletPos);

	// �G�Ƃ̓����蔻��
	bool isHit = Collision(BulletPos);

	// �̗͂�0�ȉ� ���� �G�ɓ������Ă��Ȃ�������
	if (m_nLife <= 0 && !isHit)
	{
		// ���g�p���
		Uninit();
	}
}
//===============================
// �e�̕`��
//===============================
void CBullet::Draw(void)
{
#ifdef _DEBUG
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// �e�N�X�`���ǂݍ���
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTexture));

	// �I�u�W�F�N�g�̕`��
	CBillboard::Draw();
#endif
}
//====================================
// �����蔻�菈�� ( ���� : �e�̍��W )
//====================================
bool CBullet::Collision(D3DXVECTOR3 pos)
{
	// �{�X�擾
	CBoss* pBoss = CGameManager::GetBoss();

	if (pBoss != nullptr)
	{
		// �v���C���[�̒e
		if (GetType() == BTYPE_PLAYER)
		{
			// �{�X�̍��W,�T�C�Y�擾
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// 
			D3DXVECTOR3 testPos = pos;
			testPos.y = BossPos.y; 

			D3DXVECTOR3 diff = BossPos - testPos;
			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// �{�X�ƒe�̔��a�̍��v
			float fBulletRadius = BULLETINFO::BULLET_SIZE;
			float fHitRadius = fBossSize + fBulletRadius;
			float fLength = fHitRadius * fHitRadius;

			if (fDistanceSq <= fLength)
			{
				// �p�[�e�B�N������
				CParticle::Create(D3DXVECTOR3(pos.x, pos.y, pos.z),
					LASER,
					35, 150, 100, 200);

				// �e�̍��W��n��
				pBoss->Hit(BULLETINFO::BULLET_DAMAGE, pos);

				// �e������
				CBullet::Uninit();

				// �Q�[�W�l�����Z����
				CCharge::AddCharge(1.0f);

				// �������������Ԃ�
				return true;
			}
		}

		// ���[�U�[�e
		if (GetType() == BTYPE_LASER)
		{
			// �{�X�̍��W,�T�C�Y�擾
			D3DXVECTOR3 BossPos = pBoss->GetPos();
			float fBossSize = pBoss->GetSize();

			// ���W��ݒ�
			D3DXVECTOR3 TargetPos = pos;
			TargetPos.y = BossPos.y;

			// �������v�Z
			D3DXVECTOR3 diff = BossPos - TargetPos;

			// �����̒������擾
			float fDistanceSq = D3DXVec3LengthSq(&diff);

			// �{�X�ƒe�̔��a�̍��v
			float fBulletRadius = BULLETINFO::BULLET_SIZE;
			float fHitRadius = fBossSize + fBulletRadius;
			float fLength = fHitRadius * fHitRadius;

			// �����������ȉ��Ȃ�
			if (fDistanceSq <= fLength)
			{
				// �e�̍��W��n��
				pBoss->Hit(BULLETINFO::LASER_DAMAGE, pos);

				// �e������
				CBullet::Uninit();

				//  �Q�[�W�l�����Z
				CCharge::DecCharge(7.0f);

				// �������������Ԃ�
				return true;
			}
		}
	}

	// �ʏ펞
	return false;
}