//=======================================
//
// �X�e���V���V���h�E���� [ shadowS.h ]
// Author: Asuma Nishio
//
//=======================================

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "shadowS.h"
#include "Manager.h"

//==================================
// �I�[�o�[���[�h�R���X�g���N�^
//==================================
CShadowS::CShadowS(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_pVtx = {};
}
//==================================
// �f�X�g���N�^
//==================================
CShadowS::~CShadowS()
{
	// ����
}
//==================================
// ����������
//==================================
HRESULT CShadowS::Init()
{
	// �e�N���X�̏���������
	CObjectX::Init();

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̍쐬
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtx,
		NULL);

	// ���_���̃|�C���^
	VERTEX_2D* pVtx;

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtx->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f,			0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,			SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�(1.0f�ŌŒ�)
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	
	// ���_�J���[�̐ݒ� ( ���|���S�� )
	pVtx[0].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[1].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[2].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);
	pVtx[3].col = D3DXCOLOR(0.0f,0.0f,0.0f,0.5f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@�̃A�����b�N
	m_pVtx->Unlock();

	// ���������ʂ�Ԃ�
	return S_OK;
}
//==================================
// �I������
//==================================
void CShadowS::Uninit(void)
{
	// �e�N���X�̏I������
	CObjectX::Uninit();
}
//==================================
// �X�V����
//==================================
void CShadowS::Update(void)
{
}
//==================================
// �`�揈��
//==================================
void CShadowS::Draw(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

//*****************************************************:
	// �X�e���V���e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	// Z�o�b�t�@�ւ̏������݂𖳌�������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �J���[�o�b�t�@�ւ̏������݂𖳌�������
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�[�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP); // �������i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT); // �X�e���V���e�X�g���i,Z�o�b�t�@�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); // �X�e���V���e�X�g�s���i

	// �\�ʂ��J�����O����(�\�ʂ�`�悵�Ȃ�)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

	// �e���f����`�悷��
	CObjectX::Draw();

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("1"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x01);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�[�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL); // �C�R�[���ɐݒ�

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT); // �������i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP); // �X�e���V���e�X�g���i,Z�o�b�t�@�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP); // �X�e���V���e�X�g�s���i

	// ���ʂ��J�����O���� (����`�悵�Ȃ�)
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �e���f����`��
	CObjectX::Draw();
	
	// �J���[��L��������
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);

	// �X�e���V���o�b�t�@�̎Q�ƒl��ݒ�("2"�ɂ���)
	pDevice->SetRenderState(D3DRS_STENCILREF, 0x02);

	// �X�e���V���o�b�t�@�̔�r�p�����[�^�[�ݒ�
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL); // �C�R�[���ɐݒ�

	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCRSAT); // �������i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCRSAT); // �X�e���V���e�X�g���i,Z�o�b�t�@�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_INCRSAT); // �X�e���V���e�X�g�s���i

//*****************************************************:

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtx, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`����߂�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	
//*******************************************************

	// �X�e���V���e�X�g�𖳌����ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);

	// Z�o�b�t�@�ւ̏������݂�L��������
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �J�����O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �J���[�o�b�t�@�������݂�L��������
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
}
//==================================
// ��������
//==================================
CShadowS* CShadowS::Create(const char* pFileName, D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	// �C���X�^���X����
	CShadowS* pShadowS = new CShadowS;

	// �I�u�W�F�N�gX�ݒ�
	pShadowS->SetFilePass(pFileName);
	pShadowS->SetPos(pos);
	pShadowS->SetRot(rot);

	// ���������s��
	if (FAILED(pShadowS->Init()))
	{
		// �|�C���^�̔j��
		delete pShadowS;

		// nullptr������
		pShadowS = nullptr;

		// ���s���ʂ�������
		return nullptr;
	}

	// �������ꂽ�|�C���^��Ԃ�
	return pShadowS;
}