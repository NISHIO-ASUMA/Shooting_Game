//====================================
//
// �J�������� [ camera.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "camera.h"
#include "manager.h"
#include "input.h"
#include "player.h"
#include "debugproc.h"
#include "object.h"
#include "boss.h"
#include "gamemanager.h"
#include "titleplayer.h"
#include "template.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//**********************
// �萔�錾
//**********************
namespace CAMERAINFO
{
	constexpr float MAX_VIEWUP = 3.0f;			// �J�����̊p�x�����l
	constexpr float MAX_VIEWDOWN = 0.1f;		// �J�����̊p�x�����l
	constexpr float NorRot = D3DX_PI * 2.0f;	// ���K���l
	constexpr float CAMERABACKPOS = 450.0f;		// ����J����
	constexpr float SHAKEVALUE = 12.0f;			// �U���̒l
	constexpr float DIGITVALUE = 1.5f;		// ����l
	constexpr int RANDOMBASE = 2;			// �����_����l
}

//=================================
// �R���X�g���N�^
//=================================
CCamera::CCamera()
{
	// �l�̃N���A
	m_pCamera.mtxprojection = {};
	m_pCamera.mtxView = {};
	m_pCamera.posR = VECTOR3_NULL;
	m_pCamera.posV = VECTOR3_NULL;
	m_pCamera.rot = VECTOR3_NULL;
	m_pCamera.vecU = VECTOR3_NULL;
	m_pCamera.posRDest = VECTOR3_NULL;
	m_pCamera.fDistance = NULL;
	m_pCamera.nMode = MODE_NONE;
	m_pCamera.nUseKey = NULL;
	m_pCamera.nCntAnim = NULL;

	m_isRotation = false;
	m_isStopRotation = false;
	m_isSetPos = false;
	m_lastBossPos = VECTOR3_NULL;
	m_isShake = false;
	m_nShakeTime = NULL;
	m_isKey = false;
	m_isLoad = false;

	// �C�x���g�p
	m_event.isActive = false;
	m_event.endFrame = NULL;
	m_event.frame = NULL;
	m_event.startPosR = VECTOR3_NULL;
	m_event.startPosV = VECTOR3_NULL;
	m_event.targetPosR = VECTOR3_NULL;
	m_event.targetPosV = VECTOR3_NULL;

	// �A�j���[�V�����p
	m_pCamera.m_AnimData.isLoop = false;
	m_pCamera.m_AnimData.nNumKey = 20;

	// �L�[�\���̕ϐ��̃N���A
	for (int nCnt = 0; nCnt < NUMKEY; nCnt++)
	{
		m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance = 780.0f;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY = NULL;
		m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ = NULL;

		m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame = 40;
	}

	m_isAnimTime = false;
	m_nAnimNowKey = NULL;
	m_nFileIdx = NULL;
	m_isStopCurrentAnim = false;
	m_nAnimShakeFlame = NULL;
}
//=================================
// �f�X�g���N�^
//=================================
CCamera::~CCamera()
{
	// ����
}
//=================================
// ����������
//=================================
HRESULT CCamera::Init(void)
{
	// �����l��ݒ肷��
	m_pCamera.posV = D3DXVECTOR3(0.0f, 500.0f, -600.0f);		// �J�����̈ʒu
	m_pCamera.posR = VECTOR3_NULL;								// �J�����̌��Ă���ʒu
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				// ������x�N�g��
	m_pCamera.rot = D3DXVECTOR3(D3DX_PI * 0.55f, 0.0f, 0.0f);	// �p�x

	// �������v�Z
	float fRotx = m_pCamera.posV.x - m_pCamera.posR.x;
	float fRoty = m_pCamera.posV.y - m_pCamera.posR.y;
	float fRotz = m_pCamera.posV.z - m_pCamera.posR.z;

	// ���_���璍���_�܂ł̋���
	m_pCamera.fDistance = sqrtf((fRotx * fRotx) + (fRoty * fRoty) + (fRotz * fRotz));

	// ���[�h�̏�����
	m_pCamera.nMode = MODE_NONE;

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=================================
// �I������
//=================================
void CCamera::Uninit(void)
{
	// ����
}
//=================================
// �X�V����
//=================================
void CCamera::Update(void)
{
	// ���͏����擾
	CInputMouse* pMouse = CManager::GetMouse();
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// ���݃V�[���̎擾
	CScene::MODE pMode = CManager::GetScene();

	// �C�x���g�J�������[�h�Ȃ�
	if (m_pCamera.nMode == MODE_EVENT)
	{
		if (m_event.isActive)
		{
			m_event.frame++;

			float t = (float)m_event.frame / (float)m_event.endFrame;

			if (t > 1.0f) t = 1.0f;
			t = t * t * (3.0f - 2.0f * t);

			// ���`��ԂŖړI�ʒu�Ɉړ�
			D3DXVECTOR3 newPosV = Lerp(m_event.startPosV, m_event.targetPosV, t);
			D3DXVECTOR3 newPosR = Lerp(m_event.startPosR, m_event.targetPosR, t);

			// �V�F�C�N����
			if (m_isShake && m_nShakeTime > 0)
			{
				float fOffsetX = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;
				float fOffsetY = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;
				float fOffsetZ = ((rand() % CAMERAINFO::RANDOMBASE) / CAMERAINFO::DIGITVALUE - 1.0f) * CAMERAINFO::SHAKEVALUE;

				newPosV.x += fOffsetX;
				newPosV.y += fOffsetY;
				newPosV.z += fOffsetZ;

				m_nShakeTime--;

				if (m_nShakeTime <= 0)
					m_isShake = false;
			}

			m_pCamera.posV = newPosV;
			m_pCamera.posR = newPosR;

			if (m_event.frame >= m_event.endFrame)
			{
				m_event.isActive = false;

				m_pCamera.nMode = MODE_LOCKON;
			}

			// �p�x���K��
			if (m_pCamera.rot.y > D3DX_PI) m_pCamera.rot.y -= CAMERAINFO::NorRot;
			if (m_pCamera.rot.y < -D3DX_PI) m_pCamera.rot.y += CAMERAINFO::NorRot;

			return;
		}
	}

	// �^�C�g���Ȃ�
	if (pMode == CScene::MODE_TITLE)
	{
		// �^�C�g���J�����쐬
		TitleCamera();
	}
	else if (pMode == CScene::MODE_TUTORIAL)
	{
		// �`���[�g���A���J����
		TutorialCamera();
	}
	else if (pMode == CScene::MODE_GAME)
	{
#ifdef _DEBUG

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_B))
		{
			// ���b�N�I���ɂ���
			m_pCamera.nMode = MODE_LOCKON;
		}

		if (CManager::GetInputKeyboard()->GetTrigger(DIK_V))
		{
			// ���b�N�I���ɂ���
			m_pCamera.nMode = MODE_MOUSE;
		}

#endif // _DEBUG

	}
	else if (pMode == CScene::MODE_EDIT)
	{
		// ���b�N�I���ɂ���
		m_pCamera.nMode = MODE_MOUSE;
	}
	else if (pMode == CScene::MODE_CAMERAEDIT)
	{
		// �z�u���[�h�ɂ���
		m_pCamera.nMode = MODE_ANIM;

		// �}�E�X���_�ړ�
		CCamera::MouseView(pMouse);

		// �A�j���[�V�����Z�b�g
		CCamera::AnimCamera();
	}

	// �Q�[�����[�h ���� �A�j���[�V�������[�h�Ȃ�
	if (m_pCamera.nMode == MODE_ANIM && pMode == CScene::MODE_GAME)
	{
		if (!m_isLoad)
		{
			// �ǂݍ���
			Load(m_nFileIdx);
		}

		if (!m_isStopCurrentAnim)
		{
			// �A�j���[�V�����J�n
			UpdateAnimCamera();
		}
	}

	if (m_isShake)
	{
		UpdateShake();
	}

	if (m_pCamera.nMode != MODE_EVENT)
	{
		switch (m_pCamera.nMode)
		{
		case MODE_NONE:
			break;

		case MODE_PLAYER:
			// �v���C���[�Ǐ]
			PlayerFollow();
			break;

		case MODE_LOCKON:
			// �{�X�Ƀ��b�N�I��
			LockOn();
			break;

		case MODE_MOUSE:
			// �}�E�X���_�ړ�
			MouseView(pMouse);
			break;

		default:
			break;
		}
	}

	// �p�x�̐��K��
	if (m_pCamera.rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_pCamera.rot.y -= CAMERAINFO::NorRot;
	}

	// �p�x�̐��K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}

#ifdef _DEBUG

#endif // _DEBUG

}
//=================================
// �J�������Z�b�g
//=================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxView);

	// �Z�o���ꂽ���W����ɂ���
	D3DXVECTOR3 posVForView = m_pCamera.posV;

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_pCamera.mtxView,
		&posVForView,
		&m_pCamera.posR,
		&m_pCamera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_pCamera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_pCamera.mtxprojection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&m_pCamera.mtxprojection,
		D3DXToRadian(45.0f),
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
		10.0f,
		3000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_pCamera.mtxprojection);

	// �t�H���g�Z�b�g
	CDebugproc::Print("Camera : PosV [ %.2f, %.2f, %.2f ]\n", m_pCamera.posV.x, m_pCamera.posV.y, m_pCamera.posV.z);
	// �`��J�n
	CDebugproc::Draw(0, 20);

	CDebugproc::Print("Camera : Rot [ %.2f, %.2f, %.2f ]\n", m_pCamera.rot.x, m_pCamera.rot.y, m_pCamera.rot.z);
	CDebugproc::Draw(0, 40);


	CDebugproc::Print("�A�j���[�V�����L�[�ԍ� [ %d ]", m_nAnimNowKey);
	CDebugproc::Draw(0, 500);

#if 0
	if (m_pCamera.nMode == MODE_ANIM)
	{
		CDebugproc::Print("[ �A�j���[�V�����\���̏�� ]");
		CDebugproc::Draw(0, 60);

		CDebugproc::Print("�A�j���[�V�����L�[�� : [ %d / %d ] ",m_nAnimNowKey, m_pCamera.m_AnimData.nNumKey);
		CDebugproc::Draw(0, 80);

		CDebugproc::Print("�A�j���[�V�����J�������W [ %.2f, %.2f, %.2f ]",
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVX, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVY, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVZ);
		CDebugproc::Draw(0, 100);

		CDebugproc::Print("�A�j���[�V�����J�����p�x [ %.2f, %.2f, %.2f ]",
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotX, 
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotY,
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotZ);
		CDebugproc::Draw(0, 120);

		CDebugproc::Print("�A�j���[�V�����t���[�� [ %d ]", m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame);
		CDebugproc::Draw(0, 140);

		CDebugproc::Print("���ݕҏW���̔ԍ� [ %d ]",m_nAnimNowKey);
		CDebugproc::Draw(0, 160);

		CDebugproc::Print("���݃t�@�C���p�X [ %d ] ", m_nFileIdx);
		CDebugproc::Draw(0, 180);
	}
#endif
}
//======================================
// �}�E�X����̎��_�ړ�
//======================================
void CCamera::MouseView(CInputMouse * pMouse)
{
	// ���N���b�N
	if (pMouse->GetPress(CInputMouse::MOUSE_LEFT))
	{
		// �}�E�X�̈ړ��ʎ擾
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		// ���݂̊p�x���v�Z
		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�����̎��_�̏��
		m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// �E�N���b�N
	else if (pMouse->GetPress(CInputMouse::MOUSE_RIGHT))
	{
		D3DXVECTOR2 Move = pMouse->GetMouseVelocity();
		D3DXVECTOR2 MoveOld = pMouse->GetMouseOldVelocity();

		D3DXVECTOR2 fAngle = Move - MoveOld;

		// ��]�ʂ��X�V
		m_pCamera.rot.y += fAngle.x * 0.01f;
		m_pCamera.rot.x += fAngle.y * 0.01f;

		// ��]�ʂ𐧌�
		if (m_pCamera.rot.x > CAMERAINFO::MAX_VIEWUP)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}
		else if (m_pCamera.rot.x < CAMERAINFO::MAX_VIEWDOWN)
		{
			m_pCamera.rot.x -= fAngle.y * 0.01f;
		}

		// �J�������W���X�V
		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.y = m_pCamera.posV.y + cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;

	}

	// ���K��
	if (m_pCamera.rot.y < -D3DX_PI)
	{
		m_pCamera.rot.y += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.y > D3DX_PI)
	{
		m_pCamera.rot.y += -CAMERAINFO::NorRot;
	}
	if (m_pCamera.rot.x < -D3DX_PI)
	{
		m_pCamera.rot.x += CAMERAINFO::NorRot;
	}
	else if (m_pCamera.rot.x > D3DX_PI)
	{
		m_pCamera.rot.x += -CAMERAINFO::NorRot;
	}
}
//=================================
// ���b�N�I������
//=================================
void CCamera::LockOn(void)
{
	// �{�X�擾
	CBoss* pBoss = CGameManager::GetBoss();

	// �{�X�����݂���
	if (pBoss && !m_isSetPos)
	{
		// �ŏI���W��ۑ�
		m_lastBossPos = pBoss->GetPos();
		m_isSetPos = true;
	}
	
	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptr�`�F�b�N
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// �����ŏ�����Ԃ�
		return;
	}

	// MAIN�v���C���[���W,SUB�v���C���[���W,�{�X���W���擾
	D3DXVECTOR3 playerPos = pPlayer->GetPos();				// MAIN���W
	D3DXVECTOR3 SubPlayerPos = pPlayerSub->GetPos();		// SUB���W
	D3DXVECTOR3 bossPos = m_lastBossPos; //	�{�X���W

	// MAIN�v���C���[�����v�Z
	D3DXVECTOR3 VecToBoss = bossPos - playerPos;

	// �����͖���
	VecToBoss.y = NULL;

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&VecToBoss, &VecToBoss);

	// �{�X�ւ̊p�x���v�Z
	float fAngleToBoss = atan2f(VecToBoss.x, VecToBoss.z);

	// �v���C���[�̖ړI�p�ɐݒ肷��
	pPlayer->SetRotDest(D3DXVECTOR3(0.0f, fAngleToBoss, 0.0f));

	// SUB�v���C���[�̌����v�Z
	D3DXVECTOR3 VecSubToCenter = bossPos - SubPlayerPos;

	// �����͖���
	VecSubToCenter.y = NULL;

	// �x�N�g���𐳋K������
	D3DXVec3Normalize(&VecSubToCenter, &VecSubToCenter);

	// �{�X�ւ̊p�x���v�Z
	float fAngleSubToBoss = atan2f(-VecSubToCenter.x, -VecSubToCenter.z);

	// SUB�v���C���[�̖ړI�p�x��ݒ�
	pPlayerSub->SetRotDest(D3DXVECTOR3(0.0f, fAngleSubToBoss, 0.0f));

	// �J�����ʒu��MAIN�v���C���[�̌����
	D3DXVECTOR3 camOffset = -VecToBoss * CAMERAINFO::CAMERABACKPOS;

	// �������߂ɐݒ�
	camOffset.y = 170.0f;

	// �J�����̖ړI�ʒu
	D3DXVECTOR3 desiredPosV = playerPos + camOffset;

	// �^�[�Q�b�g���W��ݒ�
	D3DXVECTOR3 targetBoss = bossPos;
	targetBoss.y = playerPos.y + 105.0f;	// ���_�̏����������

	// �J�����ɓK�p����
	m_pCamera.posV += (desiredPosV - m_pCamera.posV) * 0.3f;
	m_pCamera.posR += (targetBoss - m_pCamera.posR) * 0.3f;

	// ���b�N�I����p�̃J�����p�x�𒲐�
	m_pCamera.rot.x = D3DX_PI * 0.08f;
}
//=================================
// �v���C���[�Ǐ]����
//=================================
void CCamera::PlayerFollow(void)
{
	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptr�`�F�b�N
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// �����ŏ�����Ԃ�
		return;
	}

	// �Ǐ]�J�����p�ɐݒ�
	m_pCamera.posRDest.x = pPlayer->GetPos().x + sinf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.y = pPlayer->GetPos().y + cosf(pPlayer->GetRotDest().y) * 1.0f;
	m_pCamera.posRDest.z = pPlayer->GetPos().z + cosf(pPlayer->GetRotDest().y) * 1.0f;

	m_pCamera.posR.x += ((m_pCamera.posRDest.x - m_pCamera.posR.x) * 0.3f);
	m_pCamera.posR.y += ((m_pCamera.posRDest.y - m_pCamera.posR.y) * 0.3f);
	m_pCamera.posR.z += ((m_pCamera.posRDest.z - m_pCamera.posR.z) * 0.3f);

	// �J�����̎��_�̏��
	m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
	m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
	m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
}
//=================================
// ��ɉ�]����J�����̏���
//=================================
void CCamera::Rotation(void)
{
	m_pCamera.posV.z = -500.0f;
	m_pCamera.posV.y = 800.0f;

	m_pCamera.rot.y += 0.005f; // �J�����̎��_�̏��
	m_pCamera.rot.x = D3DX_PI * 0.75f;
	m_pCamera.fDistance = 1000.0f;

	m_pCamera.posV.x = m_pCamera.posR.x - sinf(m_pCamera.rot.x) * sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
	m_pCamera.posV.y = m_pCamera.posR.y - cosf(m_pCamera.rot.x) * m_pCamera.fDistance;
	m_pCamera.posV.z = m_pCamera.posR.z - sinf(m_pCamera.rot.x) * cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
}
//=================================
// �^�C�g���J��������
//=================================
void CCamera::TitleCamera(void)
{
	// �^�C�g���J�����p�ɐݒ�
	m_pCamera.posV = D3DXVECTOR3(0.0f, 150.0f, -950.0f); // �J�����̈ʒu
	m_pCamera.posR = VECTOR3_NULL;						 // �J�����̌��Ă���ʒu
	m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 // ������x�N�g��
	m_pCamera.rot = VECTOR3_NULL;						 // �p�x

	if (!m_isRotation)
	{
		// Enter�L�[�@or Start�{�^������
		if ((CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START)))
		{
			// �t���O��L����
			m_isRotation = true;
		}
	}
	else if ((m_isRotation && CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN)) || (CManager::GetJoyPad()->GetTrigger(CJoyPad::JOYKEY_START)))
	{
		m_isKey = true;
	}
}
//=================================
// �`���[�g���A���J�����֐�
//=================================
void CCamera::TutorialCamera(void)
{
	if (!m_isSetPos)
	{
		// �ŏI���W��ۑ�
		m_lastBossPos = VECTOR3_NULL;
		m_isSetPos = true;
	}
	

	// �v���C���[�擾
	CPlayer* pPlayer = CPlayer::GetIdxPlayer(0);
	CPlayer* pPlayerSub = CPlayer::GetIdxPlayer(1);

	// nullptr�`�F�b�N
	if (pPlayer == nullptr || pPlayerSub == nullptr)
	{
		// �����ŏ�����Ԃ�
		return;
	}

	// 2�̂̃v���C���[�̍��W�擾
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();			// MAIN���W
	D3DXVECTOR3 SubPlayerPos = pPlayerSub->GetPos();	// SUB���W

	//�v���C���[�����v�Z
	D3DXVECTOR3 VecToCenter = VECTOR3_NULL - PlayerPos;

	// �����͖���
	VecToCenter.y = NULL;

	// �x�N�g���𐳋K��
	D3DXVec3Normalize(&VecToCenter, &VecToCenter);

	// ���S�ւ̊p�x
	float fAngleToCenter = atan2f(VecToCenter.x, VecToCenter.z);

	// �v���C���[�̖ړI�p�ɐݒ肷��
	pPlayer->SetRotDest(D3DXVECTOR3(0.0f, fAngleToCenter, 0.0f));

	// SUB�v���C���[�̌����v�Z
	D3DXVECTOR3 VecSubToCenter = VECTOR3_NULL - SubPlayerPos;

	// �����͖���
	VecSubToCenter.y = NULL;

	// �x�N�g���𐳋K������
	D3DXVec3Normalize(&VecSubToCenter, &VecSubToCenter);

	// ���S�ւ̊p�x
	float fAngleSubToCenter = atan2f(-VecSubToCenter.x, -VecSubToCenter.z);

	// SUB�v���C���[�̖ړI�p�x��ݒ�
	pPlayerSub->SetRotDest(D3DXVECTOR3(0.0f, fAngleSubToCenter, 0.0f));

	// �J�����ʒu��MAIN�v���C���[�̌����
	D3DXVECTOR3 BackCamera = -VecToCenter * CAMERAINFO::CAMERABACKPOS;

	// �������߂ɐݒ�
	BackCamera.y = 190.0f;

	// �J�����̖ړI�ʒu
	D3DXVECTOR3 DestPosV = PlayerPos + BackCamera;

	// �^�[�Q�b�g���W��ݒ�
	D3DXVECTOR3 TargetPos = VECTOR3_NULL;
	TargetPos.y = PlayerPos.y + 150.0f;  // ���_�̏����������

	// �J�����ɓK�p����
	m_pCamera.posV += (DestPosV - m_pCamera.posV) * 0.3f;
	m_pCamera.posR += (TargetPos - m_pCamera.posR) * 0.3f;

	// ���b�N�I����p�̃J�����p�x�𒲐�
	m_pCamera.rot.x = D3DX_PI * 0.08f;
}

//=================================
// �U���J�����֐�
//=================================
void CCamera::ShakeCamera(int WaveTime)
{
	if (WaveTime <= 0) return;

	m_isShake = true;
	m_nShakeTime = WaveTime;
	// m_isStopCurrentAnim = true;
}
//=================================
// �C�x���g�J�������J�n����֐�
//=================================
void CCamera::StartEventCamera(const D3DXVECTOR3& targetV, const D3DXVECTOR3& targetR, int endFrame)
{
	m_event.isActive = true;
	m_event.frame = 0;
	m_event.endFrame = endFrame;

	m_event.startPosV = m_pCamera.posV;
	m_event.startPosR = m_pCamera.posR;
	m_event.targetPosV = targetV;
	m_event.targetPosR = targetR;

	// �J�������[�h���C�x���g�ɐ؂�ւ�
	m_pCamera.nMode = MODE_EVENT;
}

//=================================
// �A�j���[�V�����z�u�֐�
//=================================
void CCamera::AnimCamera(void)
{
	// ��ړ�
	if (CManager::GetInputKeyboard()->GetPress(DIK_W) == true)
	{
		m_pCamera.posV.x += sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.z += cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// ���ړ�
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S) == true)
	{
		m_pCamera.posV.x -= sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.z -= cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// ���ړ�
	if (CManager::GetInputKeyboard()->GetPress(DIK_A) == true)
	{
		m_pCamera.posV.z += sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.x -= cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}
	// �E�ړ�
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D) == true)
	{
		m_pCamera.posV.z -= sinf(m_pCamera.rot.y) * 5.0f;
		m_pCamera.posV.x += cosf(m_pCamera.rot.y) * 5.0f;

		m_pCamera.posR.x = m_pCamera.posV.x + sinf(m_pCamera.rot.y) * m_pCamera.fDistance;
		m_pCamera.posR.z = m_pCamera.posV.z + cosf(m_pCamera.rot.y) * m_pCamera.fDistance;
	}

	// �t���[�����̕ύX
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_UP))
	{
		// ���Z
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_DOWN) && m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame > 1)
	{
		// ���Z
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame--;

		if (m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame <= 0)
		{
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame = 0;
		}
	}

	// �t���[�����̕ύX
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RIGHT))
	{
		// ���Z
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame += 10;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_LEFT) && m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame > 1)
	{
		// ���Z
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame -= 10;

		if (m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame <= 0)
		{
			m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame = 0;
		}
	}

	// �z�u�̓o�^
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{// ����z��ɒǉ�����
		// ���W
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVX = m_pCamera.posV.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVY = m_pCamera.posV.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVZ = m_pCamera.posV.z;

		// �����_���W
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRX = m_pCamera.posR.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRY = m_pCamera.posR.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRZ = m_pCamera.posR.z;

		// �p�x���
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotX = m_pCamera.rot.x;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotY = m_pCamera.rot.y;
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotZ = m_pCamera.rot.z;

		// ����
		m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fDistance = m_pCamera.fDistance;

		// �z������炷
		m_nAnimNowKey = (m_nAnimNowKey + 1) % m_pCamera.m_AnimData.nNumKey;
	}

	// �t�@�C���p�X�C���f�b�N�X�؂�ւ�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F9))
	{
		m_nFileIdx = (m_nFileIdx + 1) % ANIMFILENUM;
	}

	// �z�u�̏����o��
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// �ۑ��֐����s
		Save();
	}

	// �ǂݍ���
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F5))
	{
		Load(m_nFileIdx);
	}

	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		// �ꏊ���Z�b�g
		m_pCamera.posV = D3DXVECTOR3(0.0f, 150.0f, -950.0f); // �J�����̈ʒu
		m_pCamera.posR = VECTOR3_NULL;						 // �J�����̌��Ă���ʒu
		m_pCamera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		 // ������x�N�g��
		m_pCamera.rot = VECTOR3_NULL;						 // �p�x
	}
}

//=================================
// �ǂݍ��݊֐�
//=================================
void CCamera::Load(int nIdx)
{
	// �w��t�@�C�����J��
	std::ifstream LoadFile(ANIMFILE[nIdx]);

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!LoadFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", "data\\Loader\\CameraInfo.txt", MB_OK);

		return;
	}

	std::string token;

	int keyIndex = 0;

	while (LoadFile >> token)
	{
		if (token == "LOOP")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.isLoop;
		}
		else if (token == "NUM_ALLKEY")
		{
			LoadFile >> token; // "="

			// �g���L�[��
			LoadFile >> m_pCamera.nUseKey;

			// �z��ő吔�`�F�b�N
			if (m_pCamera.nUseKey > NUMKEY)
				m_pCamera.nUseKey = NUMKEY;
		}
		else if (token == "FRAME")
		{
			LoadFile >> token; // "="

			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].nAnimFrame;
		}
		else if (token == "POSV")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosVZ;
		}
		else if (token == "POSR")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fPosRZ;
		}
		else if (token == "ROT")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotX
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotY
				>> m_pCamera.m_AnimData.KeyInfo[keyIndex].fRotZ;
		}
		else if (token == "DISTANCE")
		{
			LoadFile >> token; // "="
			LoadFile >> m_pCamera.m_AnimData.KeyInfo[keyIndex].fDistance;
		}
		else if (token == "END_KEYSET")
		{
			// �L�[���Z
			keyIndex++;
		}
		else if (token == "END_ANIMCAMERA")
		{
			// �t�@�C���I��
			break;
		}
	}

	// �t�@�C������
	LoadFile.close();

	// �t���O�L����
	m_isLoad = true;
}
//=================================
// �����o���֐�
//=================================
void CCamera::Save(void)
{
	// �w��t�@�C�����J��
	std::ofstream outFile("data\\Loader\\CameraInfo.txt");

	// �����t�@�C�����J���Ȃ��ꍇ
	if (!outFile)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", "data\\Loader\\CameraInfo.txt", MB_OK);

		return;
	}

	// float�o�͂��Œ菬���_�`���ɂ���
	outFile << std::fixed << std::setprecision(2);

	outFile << "//==============================================================\n";
	outFile << "// \n";
	outFile << "// �J�����A�j���[�V�����e�L�X�g [ data\\Loader\\CameraInfo.txt ]\n";
	outFile << "// Author : Asuma Nishio\n";
	outFile << "// \n";
	outFile << "//==============================================================\n\n";

	outFile << "//==========================================================\n";
	outFile << "// �A�j���[�V�������\n";
	outFile << "//==========================================================\n\n";

	outFile << " LOOP = " << m_pCamera.m_AnimData.isLoop << "\n";	// ���[�v���
	outFile << " NUM_ALLKEY = " << m_nAnimNowKey << "\n\n";	// �ő�L�[��

	// �e�z��̃L�[���
	for (int nCnt = 0; nCnt < m_nAnimNowKey; nCnt++)
	{
		// �J�n
		outFile << "\tKEYSET\t\t# --- << KEY  " << nCnt << " / " << m_nAnimNowKey << " >> --- \n";

		// �L�[�t���[��
		outFile << "\t\tFRAME = " << m_pCamera.m_AnimData.KeyInfo[nCnt].nAnimFrame << "\n";

		// ���W
		outFile << "\t\tPOSV = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosVZ << "\n";

		// �����_���W
		outFile << "\t\tPOSR = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fPosRZ << "\n";

		// �p�x
		outFile << "\t\tROT = "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotX << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotY << " "
			<< m_pCamera.m_AnimData.KeyInfo[nCnt].fRotZ << "\n";

		// �J�����̋���
		outFile << "\t\tDISTANCE = " << m_pCamera.m_AnimData.KeyInfo[nCnt].fDistance << "\n";

		// �L�[�Z�b�g�I��
		outFile << "\tEND_KEYSET\n\n";
	}

	outFile << "END_ANIMCAMERA\n";

	// ����
	outFile.close();
}

//=================================
// �A�j���[�V�����X�V�֐�
//=================================
void CCamera::UpdateAnimCamera(void)
{
	int nextKey = 0;

	if (m_nAnimNowKey < m_pCamera.nUseKey - 1)
	{
		// ���̃L�[��ݒ�
		nextKey = (m_nAnimNowKey + 1) % m_pCamera.nUseKey;
	}

	// ���W�Z�b�g
	float fPosVX = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVX;
	float fPosVY = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVY;
	float fPosVZ = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosVZ;

	// �����_�Z�b�g
	float fPosRX = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRX;
	float fPosRY = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRY;
	float fPosRZ = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fPosRZ;

	// �p�x�Z�b�g
	float fRotX = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotX;
	float fRotY = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotY;
	float fRotZ = m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fRotZ;

	// ���̃L�\�Ƃ̍��������߂�
	float DiffPosVX = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosVX - fPosVX;
	float DiffPosVY = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosVY - fPosVY;
	float DiffPosVZ = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosVZ - fPosVZ;
	float DiffPosRX = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosRX - fPosRX;
	float DiffPosRY = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosRY - fPosRY;
	float DiffPosRZ = m_pCamera.m_AnimData.KeyInfo[nextKey].fPosRZ - fPosRZ;

	// ���̃L�\�Ƃ̍��������߂�
	float DiffRotX = m_pCamera.m_AnimData.KeyInfo[nextKey].fRotX - fRotX;
	float DiffRotY = m_pCamera.m_AnimData.KeyInfo[nextKey].fRotY - fRotY;
	float DiffRotZ = m_pCamera.m_AnimData.KeyInfo[nextKey].fRotZ - fRotZ;

	// �����̍��������߂�
	float DiffDictance = m_pCamera.m_AnimData.KeyInfo[nextKey].fDistance - m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].fDistance;

	// �p�x�̐��K��
	if (DiffRotX > D3DX_PI)
	{
		DiffRotX += -D3DX_PI * 2.0f;
	}
	else if (DiffRotX < -D3DX_PI)
	{
		DiffRotX += D3DX_PI * 2.0f;
	}

	if (DiffRotY > D3DX_PI)
	{
		DiffRotY += -D3DX_PI * 2.0f;
	}
	else if (DiffRotY < -D3DX_PI)
	{
		DiffRotY += D3DX_PI * 2.0f;
	}

	if (DiffRotZ > D3DX_PI)
	{
		DiffRotZ += -D3DX_PI * 2.0f;
	}
	else if (DiffRotZ < -D3DX_PI)
	{
		DiffRotZ += D3DX_PI * 2.0f;
	}

	// �������v�Z
	float fRateFrame = (float)m_pCamera.nCntAnim / (float)m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame;

	// ���݂̌������Z�o
	float fCurrentRotX = fRotX + DiffRotX * fRateFrame;
	float fCurrentRotY = fRotY + DiffRotY * fRateFrame;
	float fCurrentRotZ = fRotZ + DiffRotZ * fRateFrame;

	// ���_���X�V
	m_pCamera.posV.x = sinf(fCurrentRotY) + fPosVX + DiffPosVX * fRateFrame;
	m_pCamera.posV.y = cosf(fCurrentRotX) + fPosVY + DiffPosVY * fRateFrame;
	m_pCamera.posV.z = cosf(fCurrentRotY) + fPosVZ + DiffPosVZ * fRateFrame;

	// �����_���X�V
	m_pCamera.posR.x = m_pCamera.posV.x + sinf(fCurrentRotY);
	m_pCamera.posR.y = m_pCamera.posV.y + cosf(fCurrentRotX);
	m_pCamera.posR.z = m_pCamera.posV.z + cosf(fCurrentRotY);
	
	if (m_nAnimNowKey >= m_pCamera.nUseKey - 2)
	{
		m_nAnimNowKey = m_pCamera.nUseKey - 2;
	}

	// ����L�[�̎� �U�����J�n����
	if (m_nAnimNowKey == 4) // �L�[4�ɓ������u��
	{
		// �u���[�J�n
		CManager::GetRenderer()->SetBuller(true, 125);

		// �U���J�n
		m_nAnimShakeFlame = 120;
	}

	// �U������
	if (m_nAnimShakeFlame > 0)
	{
		// �o�ߊ���
		float fValue = static_cast<float>(m_nAnimShakeFlame) / 120.0f;

		// �t���[���o�߂ɉ����ĐU������߂�
		float fPower = 1.0f * fValue;

		// �����_���l
		float Rand = static_cast<float>(rand() % 40 - 20);

		// ���_�������_���ɗh�炷
		m_pCamera.posV.x += Rand * fPower;
		m_pCamera.posV.y += Rand * fPower;
		m_pCamera.posV.z += Rand * fPower;

		// �����_���h�炷
		m_pCamera.posR.x += Rand * fPower;
		m_pCamera.posR.y += Rand * fPower;
		m_pCamera.posR.z += Rand * fPower;

		// �t���[�������炷
		m_nAnimShakeFlame--;
	}

	// �Ō�̃L�[
	if (m_pCamera.m_AnimData.isLoop == false && m_nAnimNowKey >= m_pCamera.nUseKey - 2
		&& m_pCamera.nCntAnim >= m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame)
	{
		// ���[�h�ύX
		m_pCamera.nMode = MODE_LOCKON;

		m_nAnimNowKey = 0;
		m_pCamera.nCntAnim = 0;

		// �I������
		m_isAnimTime = true;
		m_isLoad = false;

		// �����I��
		return;
	}

	// �t���[�����ő�ɂȂ�����
	if (m_pCamera.nCntAnim >= m_pCamera.m_AnimData.KeyInfo[m_nAnimNowKey].nAnimFrame)
	{
		if (m_nAnimNowKey < m_pCamera.nUseKey - 2)
		{
			// �A�j���[�V�����J�E���g���ő�ɂȂ�����0�ɖ߂�
			m_nAnimNowKey++;
		}
		m_pCamera.nCntAnim = 0;
	}

	// �A�j���[�V�����J�E���g�����Z
	m_pCamera.nCntAnim++;
}
//=============================
// �U���X�V�֐�
//=============================
void CCamera::UpdateShake(void)
{
	// �V�F�C�N�K�p
	if (m_isShake && (!m_event.isActive))
	{
		if (m_nShakeTime > 0)
		{
			// �����_���I�t�Z�b�g
			float fOffset = static_cast<float>(rand() % 80) - 40.0f;

			// ���_������h�炷
			m_pCamera.posR.x += fOffset;
			m_pCamera.posR.y += fOffset;
			m_pCamera.posR.z += fOffset;

			m_nShakeTime--;

			if (m_nShakeTime <= 0)
			{
				m_isShake = false;
				m_nShakeTime = 0;
			}
		}
		else
		{
			m_isShake = false;
		}
	}
}