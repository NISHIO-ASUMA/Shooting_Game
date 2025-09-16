//=============================================
//
// �v���C���[��ԊǗ����� [ playerstate.cpp ]
// Author: Asuma Nishio
//
//=============================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "playerstate.h"
#include "state.h"
#include "manager.h"
#include "gamemanager.h"
#include "parameter.h"
#include "pausemanager.h"

//******************************
// �萔�錾
//******************************
namespace PLAYERSTATEINFO
{
	constexpr int DAMAGECOUNT = 40;	// �ő�X�e�[�g�J�E���g
}

//==================================
// �v���C���[��ԃR���X�g���N�^
//==================================
CPlayerStateBase::CPlayerStateBase()
{
	// �l�̃N���A
	m_pPlayer = nullptr;
	m_ID = ID_NEUTRAL;
}
//==================================
// �v���C���[��ԃf�X�g���N�^
//==================================
CPlayerStateBase::~CPlayerStateBase()
{
	// ����
}


//==================================
// �ҋ@��Ԏ��R���X�g���N�^
//==================================
CPlayerStateNeutral::CPlayerStateNeutral()
{
	// �Z�b�g
	SetID(ID_NEUTRAL);
}
//==================================
// �ҋ@��Ԏ��f�X�g���N�^
//==================================
CPlayerStateNeutral::~CPlayerStateNeutral()
{
	// ����
}
//==================================
// �ҋ@��ԊJ�n�֐�
//==================================
void CPlayerStateNeutral::OnStart()
{
	// ���O�����n�Ȃ�
	if (m_pPlayer->GetMotion()->GetMotionType() == CPlayer::PLAYERMOTION_LANDING)
	{
		// �j���[�g�������[�V�����ɐݒ�
		m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_NEUTRAL, false, 0, false);
	}
	else
	{
		// �j���[�g�������[�V�����ɐݒ�
		m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_NEUTRAL, true, 5, false);
	}
}
//==================================
// �ҋ@��ԍX�V�֐�
//==================================
void CPlayerStateNeutral::OnUpdate()
{
	// �L�[���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g���[�h �܂��� �A�j���[�V������ �Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;
	if (pCamera->GetMode() == CCamera::MODE_ANIM) return;

	// Damage���͈�ؓ��͂��󂯕t���Ȃ�
	if (m_pPlayer->GetStateMachine()->GetNowStateID() == ID_DAMAGE) return;

	// �ړ����͂�����Έړ���Ԃ�
	if ((m_pPlayer->isMoveInputKey(pInput) || m_pPlayer->isMovePadButton(pPad)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// ��ԕύX
		m_pPlayer->ChangeState(new CPlayerStateMove, ID_MOVE);

		// �����ŏ�����Ԃ�
		return;
	}

	// �U���L�[���͎�
	if ((pInput->GetPress(DIK_RETURN) || pPad->GetPress(CJoyPad::JOYKEY_X)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// �X�e�[�g�ύX
		m_pPlayer->ChangeState(new CPlayerStateAction, ID_ACTION);

		// �����ŏ�����Ԃ�
		return;
	}

	// Space�L�[ �������� Pad��A�L�[
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// �X�e�[�g�ύX
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// �����ŏ�����Ԃ�
		return;
	}
}
//==================================
// �ҋ@��Ԏ��I���֐�
//==================================
void CPlayerStateNeutral::OnExit()
{
	// ����
}


//==================================
// �R���X�g���N�^
//==================================
CPlayerStateAction::CPlayerStateAction()
{
	// �Z�b�g
	SetID(ID_ACTION);
}
//==================================
// �f�X�g���N�^
//==================================
CPlayerStateAction::~CPlayerStateAction()
{
	// ����
}
//==================================
// �U����ԊJ�n�֐�
//==================================
void CPlayerStateAction::OnStart()
{
	// �U�����[�V�����ɕύX
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_ACTION);
}
//==================================
// �U����ԍX�V�֐�
//==================================
void CPlayerStateAction::OnUpdate()
{
	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	// ���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad * pPad = CManager::GetJoyPad();

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g���[�h�Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// �d��
	m_pPlayer->GravityScal();

	// ����̈ʒu�擾
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// null��������
	if (!pModelWeapon) return;

	// �r�̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// �Q�[���V�[���Ȃ�
	if (nMode == CScene::MODE_GAME)
	{
		// �v���C���[�ƃ{�X�ԂŃx�N�g������
		D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

		// �U���X�V
		m_pPlayer->UpdateAction(pInput, mtxWorld, VecBoss, pPad);
	}
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// �v���C���[�ƒ��S�Ńx�N�g������
		D3DXVECTOR3 VecCenter = m_pPlayer->VecToCenter(m_pPlayer->GetPos());

		// �U���X�V
		m_pPlayer->UpdateAction(pInput, mtxWorld, VecCenter, pPad);
	}
}
//==================================
// �U����ԏI���֐�
//==================================
void CPlayerStateAction::OnExit()
{
	// ����
}


//==================================
// �ړ���ԃR���X�g���N�^
//==================================
CPlayerStateMove::CPlayerStateMove()
{
	// �Z�b�g
	SetID(ID_MOVE);
}
//==================================
// �ړ���ԃf�X�g���N�^
//==================================
CPlayerStateMove::~CPlayerStateMove()
{
	// ����
}
//==================================
// �ړ���ԊJ�n�֐�
//==================================
void CPlayerStateMove::OnStart()
{
	// ����
}
//==================================
// �ړ���ԍX�V�֐�
//==================================
void CPlayerStateMove::OnUpdate()
{
	// �L�[���͂��擾	
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g���[�h�Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();
	D3DXVECTOR3 MeshPos = VECTOR3_NULL;

	if (nMode == CScene::MODE_GAME)
	{
		// �V�����_�[���W�̎擾
		MeshPos = CGameManager::GetCylinder()->GetPos();
	}
	else
	{
		// �V�����_�[���W�̎擾
		MeshPos = VECTOR3_NULL;
	}

	// �ړ��������s
	m_pPlayer->UpdateMove(MeshPos, pInput, pPad);

	// �L�[���͂�����
	if (!m_pPlayer->isMoveInputKey(pInput) && !m_pPlayer->isMovePadButton(pPad)
		&& m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE)
	{
		// �j���[�g�����ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateNeutral, ID_NEUTRAL);

		// �����ŏ�����Ԃ�
		return;
	}

	// �W�����v�L�[���͎��ɃX�e�[�g�ύX
	if ((pInput->GetPress(DIK_SPACE) || pPad->GetPress(CJoyPad::JOYKEY_A)) &&
		m_pPlayer->GetNowMotion() != CPlayer::PLAYERMOTION_DAMAGE		   &&
		!m_pPlayer->IsJumping())
	{
		// �W�����v�ɑJ��
		m_pPlayer->ChangeState(new CPlayerStateJump, ID_JUMP);

		// �����ŏ�����Ԃ�
		return;
	}
}
//==================================
// �ړ���ԏI���֐�
//==================================
void CPlayerStateMove::OnExit()
{
	// ����
}

//==================================
// �_���[�W��ԃR���X�g���N�^
//==================================
CPlayerStateDamage::CPlayerStateDamage(int nDamage)
{
	// id�ύX
	SetID(ID_DAMAGE);

	// �l�̃N���A
	m_nStateCount = NULL;
	m_nDamage = nDamage;
}
//==================================
// �_���[�W��ԃf�X�g���N�^
//==================================
CPlayerStateDamage::~CPlayerStateDamage()
{
	// ����
}
//==================================
// �_���[�W��ԊJ�n�֐�
//==================================
void CPlayerStateDamage::OnStart()
{
	// ���[�V�����Z�b�g
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_DAMAGE, false, 0, false);

	// ��̖ڂ̃v���C���[�̎�
	if (m_pPlayer->GetPlayerIndex() == 0)
	{
		// �̗͂����炷
		m_pPlayer->HitDamage(m_nDamage);
	}

	// ��ԕύX
	m_nStateCount = PLAYERSTATEINFO::DAMAGECOUNT;

	// �p�b�h�擾
	CJoyPad* pJoyPad = CManager::GetJoyPad();
	if (pJoyPad == nullptr) return;

	// �U���J�n
	pJoyPad->SetVibration(53000, 53000, 600);

	// �J�����U��
	CManager::GetCamera()->ShakeCamera(40);

	// �����L����
	m_pPlayer->SetIsDamege(true);
}
//==================================
// �_���[�W��ԍX�V�֐�
//==================================
void CPlayerStateDamage::OnUpdate()
{
	// �󒆎�,�d�͓K�p
	m_pPlayer->GravityScal();

	// �ʒu�X�V
	m_pPlayer->AddMove();

	// ��ԊǗ��J�E���^�[���f�N�������g
	m_nStateCount--;

	if (m_nStateCount <= NULL)
	{
		// �J�E���g��ύX
		m_nStateCount = PLAYERSTATEINFO::DAMAGECOUNT;

		// ��ԕύX
		m_pPlayer->ChangeState(new CPlayerStateNeutral(), ID_NEUTRAL);

		return;
	}
}
//==================================
// �_���[�W��ԍX�V�֐�
//==================================
void CPlayerStateDamage::OnExit()
{
 	m_pPlayer->SetJump(false);
}


//==================================
// �W�����v��Ԏ��R���X�^���N�^
//==================================
CPlayerStateJump::CPlayerStateJump()
{
	// ID���Z�b�g
	SetID(ID_JUMP);
}
//==================================
// �W�����v��Ԏ��f�X�g���N�^
//==================================
CPlayerStateJump::~CPlayerStateJump()
{
	// ����
}
//==================================
// �W�����v��Ԏ��J�n�֐�
//==================================
void CPlayerStateJump::OnStart()
{
	// �W�����v�J�n
	m_pPlayer->StartJump();

	// �W�����v���[�V�����ɕύX
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_JUMP);
}
//==================================
// �W�����v��Ԏ��X�V�֐�
//==================================
void CPlayerStateJump::OnUpdate()
{
	// ���͏��̎擾
	CInputKeyboard* pInput = CManager::GetInputKeyboard();
	CJoyPad* pPad = CManager::GetJoyPad();

	// ����̈ʒu�擾
	CModel* pModelWeapon = m_pPlayer->GetModelPartType(CModel::PARTTYPE_WEAPON);

	// null��������
	if (!pModelWeapon) return;

	// �r�̃��[���h�}�g���b�N�X���擾
	D3DXMATRIX mtxWorld = pModelWeapon->GetMtxWorld();

	// �V�[���擾
	CScene::MODE nMode = CManager::GetScene();

	// �Q�[���V�[��
	if (nMode == CScene::MODE_GAME)
	{
		// �v���C���[�ƃ{�X�ԂŃx�N�g������
		D3DXVECTOR3 VecBoss = m_pPlayer->VecToBoss(m_pPlayer->GetPos());

		// �W�����v�X�V�֐�
		m_pPlayer->UpdateJumpAction(pInput, mtxWorld, VecBoss, pPad);
	}
	// �`���[�g���A���V�[��
	else if (nMode == CScene::MODE_TUTORIAL)
	{
		// ���S�x�N�g������
		D3DXVECTOR3 VecCenter = m_pPlayer->VecToCenter(m_pPlayer->GetPos());

		// �W�����v�X�V�֐�
		m_pPlayer->UpdateJumpAction(pInput, mtxWorld, VecCenter, pPad);
	}
}
//==================================
// �W�����v��Ԏ��I���֐�
//==================================
void CPlayerStateJump::OnExit()
{
	//// �W�����v�𖢎g�p
	//m_pPlayer->SetJump(false);

	//// ���n�𖢎g�p
	//m_pPlayer->SetLanding(true);

}

//==================================
// �K�[�h��Ԏ��R���X�^���N�^
//==================================
CPlayerStateGuard::CPlayerStateGuard()
{
	// ID���Z�b�g
	SetID(ID_GUARD);
}
//==================================
// �K�[�h��Ԏ��f�X�g���N�^
//==================================
CPlayerStateGuard::~CPlayerStateGuard()
{
	// ����
}
//==================================
// �K�[�h��Ԏ��J�n�֐�
//==================================
void CPlayerStateGuard::OnStart()
{
	// ���[�V�����ύX
	m_pPlayer->GetMotion()->SetMotion(CPlayer::PLAYERMOTION_GUARD);
}
//==================================
// �K�[�h��Ԏ��X�V�֐�
//==================================
void CPlayerStateGuard::OnUpdate()
{
	// �J�����擾
	CCamera* pCamera = CManager::GetCamera();

	// �C�x���g���[�h�Ȃ�
	if (pCamera->GetMode() == CCamera::MODE_EVENT) return;

	// �X�e�[�g�ύX
	m_pPlayer->ChangeState(new CPlayerStateNeutral(), ID_NEUTRAL);

	// �����ŏ�����Ԃ�
	return;
}
//==================================
// �K�[�h��Ԏ��I���֐�
//==================================
void CPlayerStateGuard::OnExit()
{
	// ����
}
