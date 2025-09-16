//=====================================
//
// �����_�����O���� [ renderer.cpp ]
// Author: Asuma Nishio
//
//=====================================

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include "renderer.h"
#include "object.h"
#include "object2D.h"
#include "manager.h"
#include "input.h"

//******************************************
// �ÓI�����o�ϐ��錾
//******************************************
CDebugproc* CRenderer::m_pDebug = nullptr;	// �f�o�b�O�v���Z�X�ւ̃|�C���^
int CRenderer::m_fps = 0;					// FPS�J�E���g

//===============================
// �R���X�g���N�^
//===============================
CRenderer::CRenderer()
{
	// �l�̃N���A
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pZBuffMT = nullptr;
	m_pRenderDef = nullptr;
	m_pZBuffDef = nullptr;
	m_isbuller = false;

	for (int nCnt = 0; nCnt < NUM_FEEDBACKPOLYGON; nCnt++)
	{
		m_apRenderMT[nCnt] = nullptr;
		m_apTextureMT[nCnt] = nullptr;
	}

	m_pVtxMT = nullptr;
	m_nBullerTime = NULL;
}
//===============================
// �f�X�g���N�^
//===============================
CRenderer::~CRenderer()
{
	// ����
}
//===============================
// �����_���[����������
//===============================
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	// �f�B�X�v���C���[�h
	D3DDISPLAYMODE d3ddm;			

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����̃p�����[�^�[��ݒ�
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));//�p�����[�^�[��0�N���A

	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// �Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;					// �o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;								// �o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// �f�v�X�o�b�t�@�Ƃ���16bit���g�p
	m_d3dpp.Windowed = bWindow;									// �E�C���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐���(�`�揈���ƒ��_�������n�[�h�E�F�A�ōs��)
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&m_d3dpp,
		&m_pD3DDevice)))
	{
		// Direct3D�f�o�C�X�̐���(�`�揈���̓n�[�h�E�F�A,���_������CPU�ōs��)
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			// Direct3D�f�o�C�X�̐���(�`�揈��,���_������CPU�ōs��)
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�`���[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#if 1
	// �}���`�^�[�Q�b�g�p�ϐ�
	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;

	for (int nTex = 0; nTex < NUM_FEEDBACKPOLYGON; nTex++)
	{
		// �����_�����O�^�[�Q�b�g�e�N�X�`������
		m_pD3DDevice->CreateTexture(SCREEN_WIDTH, SCREEN_HEIGHT, 1, D3DUSAGE_RENDERTARGET, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &m_apTextureMT[nTex], NULL);
	}

	for (int nCnt = 0; nCnt < NUM_FEEDBACKPOLYGON; nCnt++)
	{
		// �����_�����O�p�C���^�[�t�F�[�X�쐬 
		m_apTextureMT[nCnt]->GetSurfaceLevel(0, &m_apRenderMT[nCnt]);
	}

	// Z�o�b�t�@����
	m_pD3DDevice->CreateDepthStencilSurface(SCREEN_WIDTH, SCREEN_HEIGHT, D3DFMT_D24S8, D3DMULTISAMPLE_NONE, 0, TRUE, &m_pZBuffMT, NULL);

	// ���݂̃����_�����O�^�[�Q�b�g���擾
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);

	// ���݂�Z�o�b�t�@���擾
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);

	for (int nCnt = 0; nCnt < NUM_FEEDBACKPOLYGON; nCnt++)
	{
		// �����_�����O�^�[�Q�b�g��ݒ�
		m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[nCnt]);
	}

	// Z�o�b�t�@��ݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �e�N�X�`���̃N���A����
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �ݒ肵�������_�[�^�[�Q�b�g��߂�
	m_pD3DDevice->SetRenderTarget(0, pRenderDef);

	// �ݒ肵��Z�o�b�t�@��߂�
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);

	// �r���[�|�[�g�ݒ�
	m_viewportMT.X = NULL;
	m_viewportMT.Y = NULL;
	m_viewportMT.Height = SCREEN_HEIGHT;
	m_viewportMT.Width = SCREEN_WIDTH;
	m_viewportMT.MinZ = 0.0f;
	m_viewportMT.MaxZ = 1.0f;

	// �t�B�[�h�o�b�N�p�|���S������
	m_pD3DDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * NUM_FEEDBACKPOLYGON,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxMT,
		NULL);

	// ��,������ݒ�
	float fWidth = SCREEN_WIDTH * 0.5f;
	float fHeight = SCREEN_HEIGHT * 0.5f;

	// ���_���W�̐ݒ�
	VERTEX_2D* pVtx = {};

	// ���_�o�b�t�@�����b�N��,���_���ւ̃|�C���^���擾
	m_pVtxMT->Lock(0, 0, (void**)&pVtx, 0);

	// ��l
	D3DXVECTOR3 pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);

	// �e�|���S���̐ݒ�
	for (int nCnt = 0; nCnt < NUM_FEEDBACKPOLYGON; nCnt++)
	{
		// ���_���W�̐ݒ�
		pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

		// rhw�̐ݒ�(1.0f�ŌŒ�)
		pVtx[0].rhw =
		pVtx[1].rhw =
		pVtx[2].rhw =
		pVtx[3].rhw = 1.0f;

		// �����x��ݒ�
		float fAlpha = nCnt == 0 ? 1.0f : 0.65f;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);
		pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, fAlpha);

		//�e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_���W���X�V
		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxMT->Unlock();

#endif
	// �f�o�b�O�t�H���g������
	m_pDebug = new CDebugproc;
	m_pDebug->Init();

	// �����o�ϐ�
	m_nBullerTime = NULL;

	return S_OK;
}
//===============================
// �����_���[�I������
//===============================
void CRenderer::Uninit(void)
{
	if (m_pDebug != nullptr)
	{
		// �f�o�b�O�v���Z�X�̏I��
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}

	// �S�I�u�W�F�N�g�j��
	CObject::ReleaseAll();

	// �}���`�����_�����O�^�[�Q�b�g�pZ�o�b�t�@�̔j��
	if (m_pZBuffMT != nullptr)
	{
		m_pZBuffMT->Release();
		m_pZBuffMT = nullptr;
	}

	// ���_�o�b�t�@�̔j��
	if (m_pVtxMT != nullptr)
	{
		m_pVtxMT->Release();
		m_pVtxMT = nullptr;
	}

	// �쐬�����j��
	for (int nCnt = 0; nCnt < NUM_FEEDBACKPOLYGON; nCnt++)
	{
		// �e�N�X�`���j��
		if (m_apTextureMT[nCnt] != nullptr)
		{
			m_apTextureMT[nCnt]->Release();
			m_apTextureMT[nCnt] = nullptr;
		}

		// �����_�[�j��
		if (m_apRenderMT[nCnt] != nullptr)
		{
			m_apRenderMT[nCnt]->Release();
			m_apRenderMT[nCnt] = nullptr;
		}
	}

	// Direct3D�f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}
//===============================
// �����_���[�X�V����
//===============================
void CRenderer::Update(void)
{
	// �L�[�{�[�h�̃|�C���^
	CInputKeyboard* pInput = CManager::GetInputKeyboard();

	// �f�o�b�O���̍X�V����
	m_pDebug->Update();

	// �S�I�u�W�F�N�g�X�V����
	CObject::UpdateAll();

	m_nBullerTime--;

	if (m_nBullerTime <= 0)
	{
		m_isbuller = false;
	}

#ifdef _DEBUG

	// ���C���[�t���[���ݒ�
	if (pInput->GetTrigger(DIK_F3))
	{
		// ���C���[�t���[��ON
		OnWireFrame();
	}
	else if (pInput->GetTrigger(DIK_F4))
	{
		// ���C���[�t���[��OFF
		OffWireFrame();
	}

	//// �u���[�N��
	//if (pInput->GetTrigger(DIK_F5))
	//{
	//	SetBuller(true, 60);
	//}

#endif // _DEBUG
}
//===============================
// �����_���[�`�揈��
//===============================
void CRenderer::Draw(void)
{
	// ��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@&�X�e���V���o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// �ۑ��p�ϐ��錾
	LPDIRECT3DSURFACE9 pRenderWk;
	LPDIRECT3DTEXTURE9 pTextureWk;

	// �ϐ�
	LPDIRECT3DSURFACE9 pRenderDef, pZBuffDef;
	D3DVIEWPORT9 viewport;
	D3DXMATRIX mtxview, mtxprojection;

	// �Q�b�g
	m_pD3DDevice->GetRenderTarget(0, &pRenderDef);
	m_pD3DDevice->GetDepthStencilSurface(&pZBuffDef);
	m_pD3DDevice->GetViewport(&viewport);


	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);
	m_pD3DDevice->SetViewport(&m_viewportMT);

	m_pD3DDevice->SetRenderTarget(0, pRenderDef);
	m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);
	m_pD3DDevice->SetViewport(&viewport);

	// �`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{// �`�搬����

		if (m_isbuller)
		{
			// �^�[�Q�b�g�ݒ� ( �J�������W�Ɠ����ɂ��� )
			ChangeTarget(CManager::GetCamera()->GetPos(),CManager::GetCamera()->GetPosR(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));

			// ��ʃN���A�֐�
			m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), D3DCOLOR_RGBA(0, 0, 0, 225), 1.0f, 0);

		}

		// �S�I�u�W�F�N�g�`��
		CObject::DrawAll();

		// �V�[���擾
		CScene*pScene = CManager::Getscene();

		// null����Ȃ�������
		if (pScene != nullptr)
		{
			pScene->Draw();
		}

		if (m_isbuller)
		{
			// Texture[1]�Ԃ̃|���S����`��
			m_pD3DDevice->SetFVF(FVF_VERTEX_2D);
			m_pD3DDevice->SetStreamSource(0, m_pVtxMT, 0, sizeof(VERTEX_2D));
			m_pD3DDevice->SetTexture(0, m_apTextureMT[1]);
			m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

			// �����_�[�ݒ��߂�
			m_pD3DDevice->SetRenderTarget(0, pRenderDef);
			m_pD3DDevice->SetDepthStencilSurface(pZBuffDef);
			m_pD3DDevice->SetViewport(&viewport);
			m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxview);
			m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxprojection);

			// Texture[0]�̃|���S���`��
			m_pD3DDevice->SetFVF(FVF_VERTEX_2D);
			m_pD3DDevice->SetStreamSource(0, m_pVtxMT, 0, sizeof(VERTEX_2D));
			m_pD3DDevice->SetTexture(0, m_apTextureMT[0]);
			m_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

			// �e�N�X�`�������[�J�[�ɕۑ�����
			pTextureWk = m_apTextureMT[0];
			m_apTextureMT[0] = m_apTextureMT[1];
			m_apTextureMT[1] = pTextureWk;

			// �����_�[�ݒ�����[�J�[�ɕۑ�����
			pRenderWk = m_apRenderMT[0];
			m_apRenderMT[0] = m_apRenderMT[1];
			m_apRenderMT[1] = pRenderWk;
		 }


		// �t�H���g�Z�b�g
		m_pDebug->Print("FPS : %d\n", m_fps);
		// �f�o�b�O�t�H���g�̕`��
		m_pDebug->Draw(0, 0);

		// �t�F�[�h�`��
		CManager::GetFade()->Draw();

		// �`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(nullptr, nullptr, nullptr, nullptr);
}
//===============================
// �����_�[�^�[�Q�b�g�ύX�֐�
//===============================
void CRenderer::ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU)
{
	// �}�g���b�N�X�ϐ�
	D3DXMATRIX mtxprojection, mtxview;

	// �A�X�y�N�g��v�Z�p
	float fAsepct = NULL;

	// �����_�����O�^�[�Q�b�g��ݒ�
	m_pD3DDevice->SetRenderTarget(0, m_apRenderMT[0]);

	// Z�o�b�t�@��ݒ�
	m_pD3DDevice->SetDepthStencilSurface(m_pZBuffMT);

	// �r���[�|�[�g��ݒ�
	m_pD3DDevice->SetViewport(&m_viewportMT);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxview);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxview,
		&posV,
		&posR,
		&vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_VIEW, &mtxview);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxprojection);

	// �A�X�y�N�g��̐ݒ�
	fAsepct = (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT;

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxprojection,
		D3DXToRadian(45.0f),
		fAsepct,
		10.0f,
		3000.0f);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	m_pD3DDevice->SetTransform(D3DTS_PROJECTION, &mtxprojection);
}

//===============================
// �u���[�̐ݒ�
//===============================
void CRenderer::SetBuller(bool isBuller, const int nMaxbullerTime)
{
	// �l��ݒ�
	m_isbuller = isBuller;
	m_nBullerTime = nMaxbullerTime;
}

//===============================
// �f�o�C�X�擾����
//===============================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	// �f�o�C�X��Ԃ�
	return m_pD3DDevice;
}
//===============================
// FPS�\��
//===============================
void CRenderer::GetFps(int nFps)
{
	// ���
	m_fps = nFps;
}
//===============================
// ���C���[�t���[���N��
//===============================
void CRenderer::OnWireFrame()
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
}
//===============================
// ���C���[�t���[���I��
//===============================
void CRenderer::OffWireFrame()
{
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}
