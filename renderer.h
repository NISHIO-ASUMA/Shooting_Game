//=====================================
//
// �����_�����O���� [ renderer.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _RENDERER_H_ // ���̃}�N����`������ĂȂ�������
#define _RENDERER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "debugproc.h"

//*************************
// �����_���[�N���X���`
//*************************
class CRenderer
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CRenderer();
	~CRenderer();

	// �����o�֐�
	HRESULT Init(HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void OnWireFrame();
	void OffWireFrame();
	void ChangeTarget(D3DXVECTOR3 posV, D3DXVECTOR3 posR, D3DXVECTOR3 vecU);

	// �Z�b�^�[
	void SetSize(UINT uWidth, UINT uHeight) { m_Width = uWidth, m_Height = uHeight; }
	void SetBuller(bool isBuller, const int nMaxbullerTime);

	// �Q�b�^�[
	LPDIRECT3DDEVICE9 GetDevice(void);
	UINT GetWidth(void) { return m_Width; }
	UINT GetHeight(void) { return m_Height; }
	LPDIRECT3DTEXTURE9 GetTextureFeedMT(void) { return m_apTextureMT[0]; }
	bool GetBuller(void) { return m_isbuller; }

	// �ÓI�����o�֐�
	static CDebugproc* GetDebug(void) { return m_pDebug; }
	static void GetFps(int nFps);

private:
	static inline constexpr int NUM_FEEDBACKPOLYGON = 2; // �t�B�[�h�o�b�N�p�|���S��

	LPDIRECT3D9 m_pD3D;					// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECT3DDEVICE9 m_pD3DDevice;		// Direct3D�f�o�C�X�ւ̃|�C���^
	static CDebugproc* m_pDebug;		// �f�o�b�O
	static int m_fps;					// fps
	int m_nBullerTime;					// �p������
	bool m_isDeviceLost;				// �f�o�C�X���X�g�Ώ�
	bool m_isbuller;					// �u���[���ǂ���

	D3DPRESENT_PARAMETERS m_d3dpp;
	UINT m_Width;
	UINT m_Height;

	LPDIRECT3DSURFACE9 m_pRenderDef; // �}���`�^�[�Q�b�g�����_�����O�p�C���^�[�t�F�[�X�ۑ��p
	LPDIRECT3DSURFACE9 m_pZBuffDef;	 // �}���`�^�[�Q�b�g�����_�����O�pZ�o�b�t�@�ۑ��p

	LPDIRECT3DTEXTURE9 m_apTextureMT[NUM_FEEDBACKPOLYGON]; // �����_�����O�^�[�Q�b�g�p�e�N�X�`��
	LPDIRECT3DSURFACE9 m_apRenderMT[NUM_FEEDBACKPOLYGON];	 // �e�N�X�`�������_�����O�p�C���^�[�t�F�[�X
	LPDIRECT3DSURFACE9 m_pZBuffMT;	 // �e�N�X�`�������_�����O�pZ�o�b�t�@
	D3DVIEWPORT9 m_viewportMT;		 // �e�N�X�`�������_�����O�p�r���[�|�[�g

	LPDIRECT3DVERTEXBUFFER9 m_pVtxMT;  // �|���S���p���_�o�b�t�@

};

#endif