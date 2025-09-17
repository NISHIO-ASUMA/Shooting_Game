//====================================
//
// �I�u�W�F�N�g���� [ object.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "manager.h"
#include "debugproc.h"
#include "shadowS.h"
#include "pausemanager.h"

//**********************
// �ÓI�����o�ϐ��錾
//**********************
int CObject::m_nNumAll = NULL;					// �I�u�W�F�N�g����
CObject* CObject::m_pTop[PRIORITY_MAX] = {};	// �擪�A�h���X
CObject* CObject::m_pCur[PRIORITY_MAX] = {};	// �Ō���A�h���X

//===============================
// �I�[�o�[���[�h�R���X�g���N�^
//===============================
CObject::CObject(int nPriority)
{
	m_Type = TYPE_NONE;					// �I�u�W�F�N�g��ނ�������
	m_nPriority = nPriority;			// �D��x���L�^
	m_isDeath = false;					// ���S�t���O�𖳌���

	m_pNext = nullptr;					// ���̃|�C���^��nullptr�ɏ�����
	m_pPrev = nullptr;					// �O�̃|�C���^��nullptr�ɏ�����

	m_pPrev = m_pCur[nPriority];		// ���݂̍Ō����O�|�C���^�ɐݒ�

	if (m_pCur[nPriority])
	{// ���łɍŌ��������Ȃ�

		m_pCur[nPriority]->m_pNext = this; // �������玩���ɂȂ���
	}
	else
	{// �擪�����Ȃ���Ύ������擪�ɂȂ�
		
		m_pTop[nPriority] = this;
	}

	m_pCur[nPriority] = this;			// �������Ō���Ƃ��ċL�^
	m_nNumAll++;						// �������J�E���g�A�b�v
}
//===============================
// �f�X�g���N�^
//===============================
CObject::~CObject()
{
	// ����
}
//===============================
// �I�u�W�F�N�g�S�������
//===============================
void CObject::ReleaseAll(void)
{
	// �D��ԍ�����
	for (int nPri = 0; nPri < PRIORITY_MAX; nPri++)
	{
		// �擪�̃A�h���X���擾����
		CObject* pObj = m_pTop[nPri];

		// �擾�ł�����
		while (pObj != nullptr)
		{
			// ���̃I�u�W�F�N�g��ۑ�����
			CObject* pNext = pObj->m_pNext;

			// �I�u�W�F�N�g�I������
			pObj->Uninit();

			// �O���������
			pObj->m_pNext = nullptr;
			pObj->m_pPrev = nullptr;

			// �I�u�W�F�N�g���̂������ō폜����
			delete pObj;

			// nullptr�ɂ���
			pObj = nullptr;

			// ���̃I�u�W�F�N�g�ɑ��
			pObj = pNext;
		}

		// �擪�̃|�C���^��nullptr�ɂ���
		m_pTop[nPri] = nullptr;

		// �Ō���̃|�C���^��nullptr�ɂ���
		m_pCur[nPri] = nullptr;
	}

	// ���������Z�b�g����
	m_nNumAll = NULL;
}
//===============================
// �I�u�W�F�N�g�̔j��
//===============================
void CObject::Release(void)
{
	// ���S�t���O��L��������̂�
	m_isDeath = true;
}
//===============================
// �I�u�W�F�N�g�S�X�V����
//===============================
void CObject::UpdateAll(void)
{
	// �D��ԍ�����
	for (int nPrio = 0; nPrio < PRIORITY_MAX; nPrio++)
	{
		// �擪�A�h���X,�D��ԍ����擾
		CObject* pObject = m_pTop[nPrio];

		// �擾�ł�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g�ۑ�
			CObject* pObjeNext = pObject->m_pNext;

			// �|�[�Y�I�u�W�F�N�g�݂̂��X�V
			if (CPauseManager::GetPause() == true)
			{
				if (pObject->GetObjType() == TYPE_PAUSE)
				{
					// �ΏۍX�V
					pObject->Update();
				}
			}
			else
			{
				// �S���̃I�u�W�F�N�g�p���X�V
				pObject->Update();
			}
			
			// ���̃I�u�W�F�N�g����
			pObject = pObjeNext;
		}
	}

	// ���S���Ă��邩�t���O�Ŕ��ʂ��Ώۂ̃I�u�W�F�N�g���폜
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		// �擪�A�h���X,�D��ԍ����擾
		CObject* pObject = m_pTop[nCnt];

		// �擾�ł�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g�ۑ�
			CObject* pObjeNext = pObject->m_pNext;

			// �t���O���L���̕���j������
			if (pObject->m_isDeath)
			{
				// �O�̃I�u�W�F�N�g�����݂���ꍇ�́A�����̎���O�̃I�u�W�F�N�g�ɐڑ�
				if (pObject->m_pPrev != nullptr)
				{
					pObject->m_pPrev->m_pNext = pObject->m_pNext;
				}
				else
				{
					// ���������X�g�̐擪�Ȃ�A�g�b�v�����̃I�u�W�F�N�g�ɍX�V
					m_pTop[nCnt] = pObject->m_pNext;
				}

				// ���̃I�u�W�F�N�g�����݂���ꍇ�́A�����̑O�����̃I�u�W�F�N�g�ɐڑ�
				if (pObject->m_pNext != nullptr)
				{
					pObject->m_pNext->m_pPrev = pObject->m_pPrev;
				}
				else
				{
					// ���������X�g�̍Ō���Ȃ�A�Ō����O�̃I�u�W�F�N�g�ɍX�V
					m_pCur[nCnt] = pObject->m_pPrev;
				}

				// �O���������
				pObject->m_pNext = nullptr;
				pObject->m_pPrev = nullptr;

				// �������Z
				m_nNumAll--;

				// �I�u�W�F�N�g���g�j��
				delete pObject;
			}

			// ���̃I�u�W�F�N�g����
			pObject = pObjeNext;
		}
	}
}
//===============================
// �I�u�W�F�N�g�S�`�揈��
//===============================
void CObject::DrawAll(void)
{
	// �J�����̎擾
	CCamera* pCamera = CManager::GetCamera();

	// �J�����̃Z�b�g
	pCamera->SetCamera();

	// �D��ԍ�����
	for (int nPrio = 0; nPrio < PRIORITY_MAX; nPrio++)
	{
		// �擪�A�h���X,�D��ԍ����擾
		CObject* pObject = m_pTop[nPrio];

		// �擾�ł�����
		while (pObject != nullptr)
		{
			// ���̃I�u�W�F�N�g�ۑ�
			CObject* pObjeNext = pObject->m_pNext;

			if (!pObject->m_isDeath)
			{
				// �I�u�W�F�N�g�`��
				pObject->Draw();
			}

			// ���̃I�u�W�F�N�g����
			pObject = pObjeNext;
		}
	}

	// �f�o�b�O�t�H���g
	CDebugproc::Print("���݂̃I�u�W�F�N�g�� : %d", m_nNumAll);
	CDebugproc::Draw(0, 60);
}