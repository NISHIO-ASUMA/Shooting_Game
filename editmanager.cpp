//================================================
//
// �G�f�B�^�[�V�[���Ǘ����� [ editmanager.cpp ]
// Author : Asuma Nishio
//
//================================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "editmanager.h"
#include "manager.h"
#include "debugproc.h"
#include "camera.h"
#include "rubblemanager.h"
#include "rubble.h"
#include "editmodel.h"
#include "mapmanager.h"
#include "mapobject.h"
#include "template.h"
#include "shadow.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

//*******************************
// ���O���
//*******************************
namespace EDITINFO
{
	constexpr float MOVESPEED = 5.0f;
	constexpr float ROTVALUE = 0.03f;
	constexpr float VALUEHEIGHT = 5.0f;
};

//=============================
// �R���X�g���N�^
//=============================
CEditManager::CEditManager()
{
	m_pShadow = nullptr;
	m_pMapManager = nullptr;
}
//=============================
// �f�X�g���N�^
//=============================
CEditManager::~CEditManager()
{
	// ����
}
//=============================
// ����������
//=============================
HRESULT CEditManager::Init(void)
{
	// ���f�����X�g��ǂݍ���
	CModelList::Load();

	// �}�l�[�W���[����
	m_pMapManager = CMapManager::Craete();
	
	m_pShadow = CShadow::Create(VECTOR3_NULL, VECTOR3_NULL);

	// ���������ʂ�Ԃ�
	return S_OK;
}
//=============================
// �I������
//=============================
void CEditManager::Uninit(void)
{
	// �j��
	CModelList::UnLoad();
}
//=============================
// �X�V����
//=============================
void CEditManager::Update(void)
{
	// �J����
	CCamera* pCamera = CManager::GetCamera();

	// null�Ȃ�
	if (pCamera == nullptr) return;

	// �ړ�����
	if (CManager::GetInputKeyboard()->GetPress(DIK_A))
	{// A�L�[��������

		m_pos.x -= sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
		m_pos.z -= cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_D))
	{// D�L�[��������

		m_pos.x += sinf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
		m_pos.z += cosf(pCamera->GetRot().y + (D3DX_PI * 0.5f)) * EDITINFO::MOVESPEED;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_W))
	{// W�L�[��������

		m_pos.x += sinf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
		m_pos.z += cosf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;

	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_S))
	{// S�L�[��������

		m_pos.x -= sinf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
		m_pos.z -= cosf(pCamera->GetRot().y) * EDITINFO::MOVESPEED;
	}

	// �����ύX
	if (CManager::GetInputKeyboard()->GetPress(DIK_R))
	{
		m_pos.y += EDITINFO::VALUEHEIGHT;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_F))
	{
		m_pos.y -= EDITINFO::VALUEHEIGHT;
	}

	// �p�x�ύX ( Y )
	if (CManager::GetInputKeyboard()->GetPress(DIK_Y))
	{
		m_rot.y += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_H))
	{
		m_rot.y -= EDITINFO::ROTVALUE;
	}

	// �p�x�ύX ( X )
	if (CManager::GetInputKeyboard()->GetPress(DIK_U))
	{
		m_rot.x += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_J))
	{
		m_rot.x -= EDITINFO::ROTVALUE;
	}

	// �p�x�ύX ( Z )
	if (CManager::GetInputKeyboard()->GetPress(DIK_I))
	{
		m_rot.z += EDITINFO::ROTVALUE;
	}
	else if (CManager::GetInputKeyboard()->GetPress(DIK_K))
	{
		m_rot.z -= EDITINFO::ROTVALUE;
	}

	// ����������
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_TAB))
	{
		m_rot = VECTOR3_NULL;
	}

	// ��ރC���f�b�N�X�����Z ���Z
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_E) && m_nTypeIdx < 3)
	{
		m_nTypeIdx++;
	}
	else if (CManager::GetInputKeyboard()->GetTrigger(DIK_Q)&& m_nTypeIdx > 0)
	{
		m_nTypeIdx--;
	}

	// �p�x�𐳋K������
	if (m_rot.y > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.y -= D3DX_PI * 2.0f;
	}
	// �p�x�̐��K��
	if (m_rot.y < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_rot.y += D3DX_PI * 2.0f;
	}

	// �p�x�𐳋K������
	if (m_rot.x > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.x -= D3DX_PI * 2.0f;
	}
	// �p�x�̐��K��
	if (m_rot.x < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_rot.x += D3DX_PI * 2.0f;
	}

	// �p�x�𐳋K������
	if (m_rot.z > D3DX_PI)
	{// D3DX_PI���傫���Ȃ�����
		m_rot.z -= D3DX_PI * 2.0f;
	}
	// �p�x�̐��K��
	if (m_rot.z < -D3DX_PI)
	{// D3DX_PI��菬�����Ȃ�����
		m_rot.z += D3DX_PI * 2.0f;
	}

	// �L�[���͂ŕۑ�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F7))
	{
		// �ۑ��֐����s
		Save();
	}

	// �ۑ��p�X�؂�ւ�����
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F6))
	{
		m_nSavePassIdx = (m_nSavePassIdx + 1) % SAVEPASS_MAX;
	}

	// �L�[���͂Ő���
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_RETURN))
	{
		// ��������
		CMapObject* pMapObj = CMapObject::Create(m_pos, m_rot, m_nTypeIdx);

		// �z��ɒǉ�
		m_pMapManager->PushBack(pMapObj);

		// ���������Z
		m_nNumAll++;
	}

	m_pShadow->UpdatePos(D3DXVECTOR3(m_pos.x, 2.0f, m_pos.z));
}
//=============================
// �`�揈��
//=============================
void CEditManager::Draw(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �v�Z�p�̃}�g���b�N�X��錾
	D3DXMATRIX mtxRot, mtxTrans;

	// ���݂̃}�e���A����ۑ�
	D3DMATERIAL9 matDef;

	// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxworld);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxRot);
	
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxworld, &m_mtxworld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxworld);

	// ���݂̃}�g���b�N�X�̎擾
	pDevice->GetMaterial(&matDef);

	// ���f�����
	CModelList::MODELINFO Info = CModelList::GetInfo(m_nTypeIdx);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)Info.pBuffMat->GetBufferPointer();

	// �}�e���A����������
	for (int nCntMat = 0; nCntMat < (int)Info.dwNumMat; nCntMat++)
	{
		// �J���[
		D3DXMATERIAL Col = pMat[nCntMat];

		Col.MatD3D.Diffuse.a = 0.5f;

		// �}�e���A���ݒ�
		pDevice->SetMaterial(&Col.MatD3D);

		// �C���f�b�N�X�ɉ����ĕύX����
		if (Info.pTexture[nCntMat] != -1)
		{
			// �e�N�X�`���擾
			CTexture* pTexture = CManager::GetTexture();

			// �e�N�X�`���Z�b�g
			pDevice->SetTexture(0, pTexture->GetAddress(Info.pTexture[nCntMat]));
		}
		else
		{
			pDevice->SetTexture(0, NULL); // �e�N�X�`���Ȃ�
		}

		// ���f��(�p�[�c)�̕`��
		Info.pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	// �f�o�b�O�\��
	CDebugproc::Print("�I���I�u�W�F�N�g�̍��W { %.2f,%.2f,%.2f }", m_pos.x, m_pos.y, m_pos.z);
	CDebugproc::Draw(0, 140);

	// �f�o�b�O�\��
	CDebugproc::Print("�I���I�u�W�F�N�g�̊p�x { %.2f,%.2f,%.2f }", m_rot.x, m_rot.y, m_rot.z);
	CDebugproc::Draw(0, 160);

	// �f�o�b�O�\��
	CDebugproc::Print("Edit�I�u�W�F�N�g�̐� { %d }",m_nNumAll);
	CDebugproc::Draw(0, 180);

	// �f�o�b�O�\��
	CDebugproc::Print("�t�@�C���C���f�b�N�X { %d }", m_nSavePassIdx);
	CDebugproc::Draw(0, 200);

}


//=============================
// �ۑ�����
//=============================
void CEditManager::Save(void)
{
	// �J���t�@�C���ݒ�
	std::ofstream ofs(FILELIST[m_nSavePassIdx]);

	// ��O����
	if (!ofs.is_open())
	{
		MessageBox(NULL, "�ۑ��t�@�C�����J���܂���ł���", "�G���[", MB_OK);

		return;
	}

	// float�o�͂��Œ菬���_�`���ɂ���
	ofs << std::fixed << std::setprecision(2);

	ofs << "//==========================================================\n";
	ofs << "// \n";
	ofs << "// �Q�[�����ɏo�����銢�I�I�u�W�F�N�g [ "<< FILELIST[m_nSavePassIdx] << " ]\n";
	ofs << "// Author : Asuma Nishio\n";
	ofs << "// \n";
	ofs << "//==========================================================\n\n";

	ofs << "//==========================================================\n";
	ofs << "// �o������I�u�W�F�N�g�̐�\n";
	ofs << "//==========================================================\n";
	ofs << "NUM_RUBBLES = " << m_pMapManager->GetSize() << "\n\n";

	ofs << "//==========================================================\n";
	ofs << "// �e�I�u�W�F�N�g���\n";
	ofs << "//==========================================================\n\n";

	// �T�C�Y���ŉ�
	for (int nCnt = 0; nCnt < m_pMapManager->GetSize(); nCnt++)
	{
		// �I�u�W�F�N�g�̏��擾
		CMapObject* pObj = m_pMapManager->GetInfo(nCnt);

		// ����������
		if (!pObj) continue;

		// ���W,�p�x���擾
		D3DXVECTOR3 pos = pObj->GetPos();
		D3DXVECTOR3 rot = pObj->GetRot();

		// ���f���t�@�C���p�X���擾
		CModelList::MODELINFO info = CModelList::GetInfo(pObj->GetIdx());

		ofs << "------ [ " << nCnt << "�Ԗ� ] -------\n";
		ofs << "SETTING \n";
		ofs << "POS = " << pos.x << " " << pos.y << " " << pos.z << "   # ���W\n";
		ofs << "ROT = " << rot.x << " " << rot.y << " " << rot.z << "   # �p�x\n";
		ofs << "FILEPASS = " << info.FileName << "\t# X�t�@�C��\n";
		ofs << "END_SETTING\n\n";
	}

	// �t�@�C�������
	ofs.close();
}
//=============================
// �t�@�C���ēǂݍ��ݏ���
//=============================
void CEditManager::Reload(void)
{
	// �J���t�@�C���ݒ�
	std::ofstream ofs(FILELIST[m_nSavePassIdx]);

	// ��O����
	if (!ofs.is_open())
	{
		MessageBox(NULL, "�f�[�^�������Ă��܂���", "�G���[", MB_OK);

		return;
	}
}
