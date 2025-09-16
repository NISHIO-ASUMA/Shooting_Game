//===============================================
//
// �V�[���h�֐� [ barrierdurability.cpp ]
// Author : Asuma Nishio
//
//===============================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "barrierdurability.h"
#include "manager.h"
#include "texture.h"
#include "template.h"
#include "player.h"
#include "gamemanager.h"
#include "particle.h"

//*********************************
// ���O���
//*********************************
namespace BARRIERINFO
{
	constexpr float COLLISIOLANGE = 100.0f; // �R���W�����T�C�Y
	constexpr float VALUEROT = 0.03f;	// ���Z�p�x
	constexpr float DISTANCE = 50.0f;	// ����
};

//=======================================
// �I�[�o�[���[�h�R���X�g���N�^
//=======================================
CBarrierDurability::CBarrierDurability(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_nIdx = NULL;
}
//=======================================
// �f�X�g���N�^
//=======================================
CBarrierDurability::~CBarrierDurability()
{
	// ����
}
//=======================================
// ��������
//=======================================
CBarrierDurability* CBarrierDurability::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot,const char * pFilename)
{
	// �C���X�^���X����
	CBarrierDurability* pbarrier = new CBarrierDurability;

	// null�Ȃ�
	if (pbarrier == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pbarrier->SetFilePass(pFilename);
	pbarrier->SetPos(pos);
	pbarrier->SetRot(rot);

	// ���������s��
	if (FAILED(pbarrier->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pbarrier;
}
//=======================================
// ����������
//=======================================
HRESULT CBarrierDurability::Init(void)
{
	// �e�N���X�̏���������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ނ�ݒ�
	SetObjType(CObject::TYPE_BARRIER);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=======================================
// �I������
//=======================================
void CBarrierDurability::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//=========================================
// �X�V����
//=========================================
void CBarrierDurability::Update(void)
{
	// �v���C���[���擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	if (!pPlayer) return;

	// ��]�p�x���X�V
	static float fValueAngle = NULL;

	fValueAngle += BARRIERINFO::VALUEROT;

	// �������v�Z
	float fDistance = BARRIERINFO::DISTANCE;
	float DestPosY = pPlayer->GetPos().y + BARRIERINFO::DISTANCE;

	// �o���A���Ƃ̊p�x�I�t�Z�b�g
	float angleOffset = (2.0f * D3DX_PI / CGameManager::GetBarrier()->GetNumBarrier()) * m_nIdx;
	float currentAngle = fValueAngle + angleOffset;

	// ���W���v�Z
	float DestPosX = pPlayer->GetPos().x + cosf(currentAngle) * fDistance;
	float DestPosZ = pPlayer->GetPos().z + sinf(currentAngle) * fDistance;

	// �I�u�W�F�N�g�̍��W�ɃZ�b�g
	SetPos(D3DXVECTOR3(DestPosX, DestPosY, DestPosZ));

	// �I�u�W�F�N�g�̓������v���C���[��������������
	D3DXVECTOR3 VecToPlayer = pPlayer->GetPos() - CObjectX::GetPos();
	float fAngleY = atan2f(VecToPlayer.x, VecToPlayer.z);

	// ���݊p�x���擾
	D3DXVECTOR3 rot = GetRot();

	// ���K��
	rot.y = NormalAngle(fAngleY);

	// �I�u�W�F�N�g�̊p�x�ɃZ�b�g
	SetRot(rot);
}
//=======================================
// �`�揈��
//=======================================
void CBarrierDurability::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}

//=======================================
// �o���A�I�u�W�F�N�g�̓����蔻��֐�
//=======================================
bool CBarrierDurability::Collision(D3DXVECTOR3* DestPos)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �R���W������������̒������v�Z
	D3DXVECTOR3 CollisionPos = NowPos - *DestPos;

	// �����̒������Z�o
	float fRange = D3DXVec3Length(&CollisionPos);

	// �q�b�g���a�����������l�ɂȂ�����
	if (fRange <= BARRIERINFO::COLLISIOLANGE)
	{
		// �T�E���h�̃|�C���^���擾
		CSound* pSound = CManager::GetSound();

		// null�`�F�b�N
		if (pSound != nullptr)
		{
			// �T�E���h�Đ�
			pSound->PlaySound(CSound::SOUND_LABEL_ITEM);
		}

		// �o���A�}�l�[�W�����擾
		CBarrierManager* pBarrierMgr = CGameManager::GetBarrier();

		// null����Ȃ�������
		if (pBarrierMgr != nullptr)
		{
			// �o���A���Z
			pBarrierMgr->DamageBarrier(1);

			// �p�[�e�B�N������
			CParticle::Create(D3DXVECTOR3(DestPos->x, 20.0f, DestPos->z),COLOR_GREEN, 100, 100, 200, 100);
		}

		// �q�b�g�����Ԃ�
		return true;
	}

	// �������ĂȂ��Ƃ�
	return false;
}