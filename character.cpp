//==========================================================
//
// �L�����N�^�[�p�����[�^�[�ݒ�֐� [ charactor.cpp ]
// Author : Asuma Nishio
//
//===========================================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "character.h"
#include "manager.h"
#include "camera.h"
#include "input.h"

//==================================
// �R���X�g���N�^
//==================================
CCharacter::CCharacter()
{
    // �l�̃N���A
    m_fMove = 0.0f;
    m_nAnimCount2D = 0;
    m_nAnimPattern2D = 0;
    m_nLife = 0;
    m_nMaxLife = 0;
}
//==================================
// �f�X�g���N�^
//==================================
CCharacter::~CCharacter()
{
    // ����
}
//==================================
// ����������
//==================================
HRESULT CCharacter::Init(void)
{
    // �e�N���X�̏�����
    CObject2D::Init();

    // �����o�ϐ��̏�����
    m_nLife = 10;
    m_fMove = 3.0f;

    return S_OK;;
}
//==================================
// �I������
//==================================
void CCharacter::Uninit(void)
{
    // �I������
    CObject2D::Uninit();
}
//==================================
// �X�V����
//==================================
void CCharacter::Update(void)
{
    // ����
}
//==================================
// �ړ��ʊ֌W
//==================================
void CCharacter::CharactorMove(float fMove)
{
    // �ړ��ʐݒ�
    m_fMove = fMove;
}
//==================================
// 2D�A�j���[�V��������
//==================================
void CCharacter::SetAnim2D(int nMaxPattern,int nAnimCount,float TexU,float TexV)
{
    // �A�j���[�V�����J�E���^�[�����Z
    m_nAnimCount2D++;

    // �J�E���g��������傫���Ȃ�����
    if (m_nAnimCount2D >= nAnimCount)
    {
        m_nAnimCount2D = 0;		// �J�E���^�[�������l�ɖ߂�

        m_nAnimPattern2D++;		// �p�^�[���i���o�[���X�V

        // �e�N�X�`�����W�X�V
       //  SetUV(m_nAnimPattern2D * TexU, TexU + m_nAnimPattern2D * TexU, TexV); // U,U1,V1���W
    }

    // �p�^�[���i���o�[���ő�l���傫���Ȃ�����
    if (m_nAnimPattern2D > nMaxPattern)
    {
        m_nAnimPattern2D = 0;			// �p�^�[���i���o�[�������l�ɖ߂�
    }
}

//==================================
// �I�[�o�[���[�h�R���X�g���N�^
//==================================
CCharactor3D::CCharactor3D(int nPriority) : CObject(nPriority)
{
    // �l�̃N���A
    m_move = VECTOR3_NULL;
    m_rotDest = VECTOR3_NULL;
    m_nLife = NULL;
    m_state = STATE_NONE;
}
//==================================
// �f�X�g���N�^
//==================================
CCharactor3D::~CCharactor3D()
{
    // ����
}
//==================================
// ����������
//==================================
HRESULT CCharactor3D::Init(void)
{
    return S_OK;
}
//==================================
// �I������
//==================================
void CCharactor3D::Uninit(void)
{
    // �I�u�W�F�N�g�̔j��
    CObject::Release();
}
//==================================
// �X�V����
//==================================
void CCharactor3D::Update(void)
{
    // ����
}
