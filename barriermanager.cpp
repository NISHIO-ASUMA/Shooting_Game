//=====================================================
//
// �o���A�I�u�W�F�N�g�̊Ǘ����� [ barriermanager.cpp ]
// Author : Asuma Nishio
//
//=====================================================

//*********************************
// �C���N���[�h�t�@�C��
//*********************************
#include "barriermanager.h"
#include "barrierdurability.h"

//============================
// �R���X�g���N�^
//============================
CBarrierManager::CBarrierManager()
{
	// �l�̃N���A
	m_nBarrierNum = NULL;

	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		m_pBarrierObj[nCnt] = nullptr;
	}
}
//============================
// �f�X�g���N�^
//============================
CBarrierManager::~CBarrierManager()
{
	// ����
}
//============================
// ����������
//============================
HRESULT CBarrierManager::Init(void)
{
	// ���������ʂ�Ԃ�
	return S_OK;
}
//============================
// �I������
//============================
void CBarrierManager::Uninit(void)
{
	// ����
}
//============================
// �X�V����
//============================
void CBarrierManager::Update(void)
{
	// ����
}
//============================
// �o���A���Z����
//============================
void CBarrierManager::AddBarrier(int nValue, D3DXVECTOR3 playerPos,float fRadius)
{
	// ����l�ȏ�Ȃ�
	if (m_nBarrierNum >= MAX_GUARD)
	{
		// �ő�l�ɐݒ�
		m_nBarrierNum = MAX_GUARD;

		return;
	}

	// ���Z����
	m_nBarrierNum += nValue;

	// �o���A����
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		if (nCnt < m_nBarrierNum)
		{
			// �܂���������Ă��Ȃ��ꍇ�̂ݍ쐬
			if (m_pBarrierObj[nCnt] == nullptr)
			{
				// �p�x���v�Z����
				float angle = (float)nCnt / m_nBarrierNum * D3DX_PI * 2.0f;

				// �o���A���W��ݒ肷��
				D3DXVECTOR3 barrierPos;

				barrierPos.x = playerPos.x + cosf(angle) * fRadius;
				barrierPos.y = playerPos.y;
				barrierPos.z = playerPos.z + sinf(angle) * fRadius;

				// �o���A�I�u�W�F�N�g�𐶐�
				m_pBarrierObj[nCnt] = CBarrierDurability::Create(
					barrierPos,
					VECTOR3_NULL,
					"data\\MODEL\\STAGEOBJ\\Difence000.x");

				// �C���f�b�N�X�Z�b�g
				m_pBarrierObj[nCnt]->SetIdx(nCnt);
			}
		}
		else
		{
			// �s�v�ɂȂ����o���A�͍폜
			if (m_pBarrierObj[nCnt] != nullptr)
			{
				// �I������
				m_pBarrierObj[nCnt]->Uninit();

				// null������
				m_pBarrierObj[nCnt] = nullptr;
			}
		}
	}
}
//============================
// �o���A���Z����
//============================
void CBarrierManager::DamageBarrier(int nValue)
{
	// �ϋv�l�����炷
	m_nBarrierNum -= nValue;

	// 0�ȉ��Ȃ�
	if (m_nBarrierNum < 0) m_nBarrierNum = 0; // �ŏ�����

	  // �s�v�ɂȂ����o���A���폜
	for (int nCnt = 0; nCnt < MAX_GUARD; nCnt++)
	{
		// �o���A�����傫���Ƃ�
		if (nCnt >= m_nBarrierNum)
		{
			// null�`�F�b�N
			if (m_pBarrierObj[nCnt] != nullptr)
			{
				// �I������
				m_pBarrierObj[nCnt]->Uninit();

				// null������
				m_pBarrierObj[nCnt] = nullptr;
			}
		}
	}
}