//===========================================
//
// �f�o�b�O�v���Z�X���� [ debubgproc.cpp ]
// Author: Asuma Nishio
//
//===========================================

//***********************
// �C���N���[�h�t�@�C��
//***********************
#include "debugproc.h"
#include <time.h>
#include <stdio.h>
#include "manager.h"

//***********************************
// �ÓI�����o�ϐ�
//***********************************
LPD3DXFONT CDebugproc::m_pFont = nullptr;  // �t�H���g�ւ̃|�C���^
char CDebugproc::m_aStr[MAX_WORD] = {};	   // ��������i�[����o�b�t�@
bool CDebugproc::m_isUse = false;		   // �g�p���Ă��邩

//===============================
// �R���X�g���N�^
//===============================
CDebugproc::CDebugproc()
{
	// ����
}
//===============================
// �f�X�g���N�^
//===============================
CDebugproc::~CDebugproc()
{
	// ����
}
//===============================
// �f�o�b�O�v���Z�X�̏���������
//===============================
HRESULT CDebugproc::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �f�o�b�O�\���p�̃t�H���g��ݒ�
	D3DXCreateFont(pDevice, FontSize, 0, 0, 0,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal", &m_pFont);

	// ������N���A
	memset(m_aStr, 0, sizeof(m_aStr));

	// �g�p��Ԏ�
	m_isUse = true;

	return S_OK;
}
//===============================
// �f�o�b�O�v���Z�X�̏I������
//===============================
void CDebugproc::Uninit(void)
{
	// NULL�`�F�b�N
	if (m_pFont != nullptr)
	{
		// ���
		m_pFont->Release();

		// nullptr�ɂ���
		m_pFont = nullptr;
	}
}
//===============================
// �f�o�b�O�v���Z�X�̍X�V����
//===============================
void CDebugproc::Update(void)
{
	// �L�[���͂ŕ\���ؑ�
	if (CManager::GetInputKeyboard()->GetTrigger(DIK_F1))
	{
		m_isUse = m_isUse ? false : true;
	}
}
//===============================
// �f�o�b�O�v���Z�X�̕`�揈��
//===============================
void CDebugproc::Draw(int PosX,int PosY)
{
#ifdef _DEBUG
	if (m_isUse)
	{
		// �E�B���h�E���N�g
		RECT rect = { PosX,PosY,SCREEN_WIDTH,SCREEN_HEIGHT };

		// �t�H���g�̐���
		m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 255));

		// �o�b�t�@�̃N���A
		memset(m_aStr, 0, sizeof(m_aStr));
	}
#endif
}
//===============================
// �t�H���g�`��֐�
//===============================
void CDebugproc::Print(const char* fmt, ...)
{
	// �ϐ��錾
	va_list list;

	// �`��J�n
	va_start(list, fmt);

	// �`��̎�ޕ���
	vsprintf_s(m_aStr, sizeof(m_aStr), fmt, list);

	// �I��
	va_end(list);

	// ������ɃR�s�[
	va_copy(list, m_aStr);
}