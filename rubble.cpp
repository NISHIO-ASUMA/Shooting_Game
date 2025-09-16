//========================================
//
// ���I�I�u�W�F�N�g���� [ rubble.cpp ]
// Author : Asuma Nishio
//
//========================================

//**********************************
// �C���N���[�h�t�@�C��
//**********************************
#include "rubble.h"
#include "scene.h"
#include "manager.h"
#include "shadow.h"

//================================
// �I�[�o�[���[�h�R���X�g���N�^
//================================
CRubble::CRubble(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_Fallingspeed = VECTOR3_NULL;
}
//================================
// �f�X�g���N�^
//================================
CRubble::~CRubble()
{
	// ����
}
//================================
// ��������
//================================
CRubble* CRubble::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename)
{
	// �C���X�^���X����
	CRubble* pRubble = new CRubble;

	// ����null��������
	if (pRubble == nullptr) return nullptr;

	// �I�u�W�F�N�g�ݒ�
	pRubble->SetFilePass(pFilename);
	pRubble->SetPos(pos);
	pRubble->SetRot(rot);

	// ���������s��
	if (FAILED(pRubble->Init()))
	{
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pRubble;
}
//================================
// ����������
//================================
HRESULT CRubble::Init(void)
{
	// �e�N���X����������
	CObjectX::Init();

	// �I�u�W�F�N�g�̎�ޒ�`
	SetObjType(CObject::TYPE_RUBBLE);

	// �����l��ݒ�
	m_Fallingspeed = { 0.0f,3.0f,0.0f };

	// �e�I�u�W�F�N�g�𐶐�
	m_pShadow = CShadow::Create(VECTOR3_NULL, VECTOR3_NULL);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//================================
// �I������
//================================
void CRubble::Uninit(void)
{
	// �e�N���X�I������
	CObjectX::Uninit();
}
//================================
// �X�V����
//================================
void CRubble::Update(void)
{
	// ���݃V�[���擾
	CScene::MODE pMode = CManager::GetScene();

	// ���݂̍��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �Q�[���V�[���Ȃ�
	if (pMode == CScene::MODE_GAME)
	{
		// ���݂̍��W�ɑ΂��ďd�͒l�����Z����
		NowPos -= m_Fallingspeed;

		// ���ݍ��W���Z�b�g����
		SetPos(NowPos);
	}

	// �e�̍��W�ݒ�
	m_pShadow->UpdatePos(D3DXVECTOR3(NowPos.x,2.0f, NowPos.z));

	// ��ʉ�
	if (NowPos.y <= -15.0f)
	{
		// �I������
		Uninit();

		// �����ŉe������
		m_pShadow->Uninit();

		// �����ŏ�����Ԃ�
		return;
	}
}
//================================
// �`�揈��
//================================
void CRubble::Draw(void)
{
	// �e�N���X�̕`��
	CObjectX::Draw();
}
//====================================
// �����蔻�菈���֐� ( �����W�Ōv�Z )
//====================================
bool CRubble::Collision(D3DXVECTOR3 * DestPos)
{
	// ���ݍ��W���擾
	D3DXVECTOR3 NowPos = GetPos();

	// �v���C���[�Ƃ̋�������
	float fDisX = DestPos->x - NowPos.x;
	float fDisY = DestPos->y - NowPos.y;
	float fDisZ = DestPos->z - NowPos.z;

	// ���a��ݒ�
	float fRadius = 25.0f;

	// ���a�̃T�C�Y���v�Z
	float fradX = fRadius + 25.0f;
	float fradY = fRadius + 25.0f;
	float fradZ = fRadius + 25.0f;

	// �����Ɣ��a�̍��v���v�Z
	float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
	float fRadAll = (fradX + fradY + fradZ) * (fradX + fradY + fradZ);

	// ���a���ɓ����Ă�����
	if (fDissAll <= fRadAll)
	{
		// �R���W���������Ԃ�
		return true;
	}

	// ������Ȃ��Ƃ�
	return false;
}
