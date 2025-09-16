//======================================
//
// �t�F�[�h���� [ fade.cpp ]
// Author: Asuma Nishio
// 
//======================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "fade.h"
#include "manager.h"

//==============================
// �R���X�g���N�^
//==============================
CFade::CFade()
{
	// �l�̃N���A
	m_pVtx = nullptr;
	m_pScene = nullptr;
	m_col = COLOR_BLACK;
	m_fade = FADE_NONE;
}
//==============================
// �f�X�g���N�^
//==============================
CFade::~CFade()
{
	// ����
}
//==============================
// ����������
//==============================
HRESULT CFade::Init(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,SCREEN_HEIGHT,0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT,0.0f);

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 
	pVtx[1].rhw = 
	pVtx[2].rhw = 
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = 
	pVtx[1].col = 
	pVtx[2].col = 
	pVtx[3].col = m_col;

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N
	m_pVtx->Unlock();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==============================
// �I������
//==============================
void CFade::Uninit(void)
{
	// nullptr�`�F�b�N
	if (m_pVtx != nullptr)
	{
		m_pVtx->Release();
		m_pVtx = nullptr;
	}
}
//==============================
// �X�V����
//==============================
void CFade::Update(void)
{
	// ���_���̃|�C���^
	VERTEX_2D* pVtx = NULL;

	// �����Ȃ�������
	if (m_fade == FADE_NONE)
	{
		return;
	}

	// IN���
	if (m_fade == FADE_IN)
	{
		// �t�F�[�h�C�����
		m_col.a -= AlphaFade;

		if (m_col.a <= 0.0f)
		{
			m_col.a = 0.0f;
			m_fade = FADE_NONE;		// �������Ă��Ȃ����
		}
	}
	// OUT���
	else if (m_fade == FADE_OUT)
	{
		// �t�F�[�h�A�E�g���
		m_col.a += AlphaFade;

		if (m_col.a >= 1.0f)
		{
			m_col.a = 1.0f;
			m_fade = FADE_IN;

			// ���̃��[�h�ݒ�
			CManager::SetScene(m_pScene);

			// �����ŏ����Ԃ�
			return;
		}
	}

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(m_col);
	pVtx[1].col = D3DXCOLOR(m_col);
	pVtx[2].col = D3DXCOLOR(m_col);
	pVtx[3].col = D3DXCOLOR(m_col);

	// �A�����b�N
	m_pVtx->Unlock();
}
//==============================
// �`�揈��
//==============================
void CFade::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//==============================
// �ݒ菈��
//==============================
void CFade::SetFade(CScene * pNewScene)
{
	// �^�C�v��NONE���ᖳ��������
	if (m_fade != FADE_NONE)
	{
		// �V�����V�[���̔j��
		delete pNewScene;

		// nullptr�ɂ���
		pNewScene = nullptr;

		// �����ŏ�����Ԃ�
		return;
	}

	// ���݃V�[����null�ɂ���
	if (m_pScene != nullptr)
	{
		m_pScene = nullptr;
	}

	// nullptr�Ȃ̂ŐV�����V�[���𐶐�����
	if (m_pScene == nullptr)
	{
		// �V�[�����Z�b�g����
		m_pScene = pNewScene;

		// �t�F�[�h�A�E�g��Ԃ����
		m_fade = FADE_OUT;
	}
}
