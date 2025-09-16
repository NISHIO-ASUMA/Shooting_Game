//====================================
//
// ���C�g���� [ light.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "light.h"
#include "manager.h"

//=================================
// �R���X�g���N�^
//=================================
CLight::CLight()
{
	// �l�̃N���A
	for (int nCnt = 0; nCnt < NUMLIGHT; nCnt++)
	{
		m_aLight[nCnt] = {};
		m_vecDir[nCnt] = {};
	}
}
//=================================
// �f�X�g���N�^
//=================================
CLight::~CLight()
{
	// ����
}
//=================================
// ���C�g�̏���������
//=================================
HRESULT CLight::Init(void)
{
	// �f�o�C�X�|�C���^��錾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���C�g�̃N���A����( �[���������[�֐� )
	ZeroMemory(&m_aLight, sizeof(m_aLight));

	// ���C�g�̎�ނ�ݒ�
	for (int nCnt = 0; nCnt < NUMLIGHT; nCnt++)
	{
		// ���s����
		m_aLight[nCnt].Type = D3DLIGHT_DIRECTIONAL;	

		// ���C�g�̊g�U��
		m_aLight[nCnt].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	// ���C�g�̕����ݒ�
	m_vecDir[0] = D3DXVECTOR3(0.25f, -0.84f, -0.43f);
	m_vecDir[1] = D3DXVECTOR3(-0.61f, 0.10f, 0.44f);
	m_vecDir[2] = D3DXVECTOR3(1.0f, -0.52f, 0.41f);

	// ���K������
	for (int nCnt1 = 0; nCnt1 < NUMLIGHT; nCnt1++)
	{	
		// �x�N�g���̑傫����1�ɂ���
		D3DXVec3Normalize(&m_vecDir[nCnt1], &m_vecDir[nCnt1]); 

		m_aLight[nCnt1].Direction = m_vecDir[nCnt1];

		// ���C�g�̐ݒ�
		pDevice->SetLight(nCnt1, &m_aLight[nCnt1]);

		// ���C�g��L����
		pDevice->LightEnable(nCnt1, TRUE);
	}

	return S_OK;
}
//=================================
// ���C�g�̏I������
//=================================
void CLight::Uninit(void)
{
	// ����
}
//=================================
// ���C�g�̍X�V����
//=================================
void CLight::Update(void)
{
	// ����
}