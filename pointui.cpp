//=====================================
//
// �I���|�C���gUI���� [ pointui.h ]
// Author: Asuma Nishio
//
//=====================================

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include "pointui.h"
#include "manager.h"
#include "texture.h"

//*****************************
// ���O���
//*****************************
namespace POINTINFO
{
	constexpr float POINTWIDTH = 30.0f;	// ����
	constexpr float POINTHEIGHT = 40.0f;// ����
};

//==============================
// �I�[�o�[���[�h�R���X�g���N�^
//==============================
CPointUi::CPointUi(int nPriority) : CObject2D(nPriority)
{
	// �l�̃N���A
	m_nIdxTex = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CPointUi::~CPointUi()
{
	// ����
}
//==============================
// ��������
//==============================
CPointUi* CPointUi::Create(D3DXVECTOR3 pos)
{
	// �C���X�^���X����
	CPointUi* pPoint = new CPointUi;
	if (pPoint == nullptr) return nullptr;

	// ���������s��
	if (FAILED(pPoint->Init()))
	{
		return nullptr;
	}

	// �I�u�W�F�N�g�ݒ�
	pPoint->SetPos(pos);
	pPoint->SetSize(POINTINFO::POINTWIDTH, POINTINFO::POINTHEIGHT);
	pPoint->SetAnchor(CObject2D::ANCHORTYPE_CENTER);
	pPoint->SetTexture();

	// �������ꂽ�|�C���^��Ԃ�
	return pPoint;
}
//==============================
// ����������
//==============================
HRESULT CPointUi::Init(void)
{
	// �e�N���X�̏���������
	CObject2D::Init();

	// ����������
	return S_OK;
}
//==============================
// �I������
//==============================
void CPointUi::Uninit(void)
{
	// �e�N���X�̏I������
	CObject2D::Uninit();
}
//==============================
// �X�V����
//==============================
void CPointUi::Update(void)
{
	// �e�N���X�̍X�V����
	CObject2D::Update();
}
//==============================
// �`�揈��
//==============================
void CPointUi::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// �e�N�X�`���Z�b�g
	pDevice->SetTexture(0, pTexture->GetAddress(m_nIdxTex));

	// �e�N���X�̕`�揈��
	CObject2D::Draw();
}
//==============================
// �e�N�X�`�����蓖�ď���
//==============================
void CPointUi::SetTexture(void)
{
	// �e�N�X�`���擾
	CTexture* pTexture = CManager::GetTexture();

	// null�������炱���ŏ����I��
	if (pTexture == nullptr) return;

	// ���蓖��
	m_nIdxTex = pTexture->Register("data\\TEXTURE\\PointUi.png");
}
