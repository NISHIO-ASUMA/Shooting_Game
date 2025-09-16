//====================================
//
// �v���R���p�C���w�b�_�[ [ pch.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PCH_H_ // ���̃}�N����`������ĂȂ�������
#define _PCH_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include <windows.h>
#include "d3dx9.h"					// �`�揈���ɕK�v
#include "d3d9.h"
#define DIRECTINPUT_VERSION (0x0800)// �r���h���x���Ώ��p�̃}�N��
#include "dinput.h"					// ���͏����ɕK�v
#include "Xinput.h"					// �W���C�p�b�h�����ɕK�v
#include "xaudio2.h"
#include <time.h>
#include <Shlwapi.h>
#include <assert.h>					// �A�T�[�g�֐��w�b�_�[
#include <stdlib.h>
#include <cstdio>

//**************************
// ���C�u�����̃����N�錾
//**************************
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g(���i)�g�p�ɕK�v
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"xinput.lib")	// �W���C�p�b�h�����ɕK�v
#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"shlwapi.lib")

//**************************
// �}�N����`
//**************************
#define SCREEN_WIDTH (1280)		// �E�C���h�E�̕�
#define SCREEN_HEIGHT (720)		// �E�C���h�E�̍���
#define CLASS_NAME "WindowClass"		// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME "Circle Shot!"		// �E�C���h�E�̖��O
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)				// ���_�t�H�[�}�b�g[2D]
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL |  D3DFVF_DIFFUSE | D3DFVF_TEX1)  // ���W,�@��,�J���[,�e�N�X�`��
#define FVF_VERTEX_3D_MULTI (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX2) // ���W,�@��,�J���[,�}���`�e�N�X�`��

#define VECTOR3_NULL (D3DXVECTOR3(0.0f, 0.0f, 0.0f))		// ���W������
#define COLOR_BLACK (D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f))		// ��
#define COLOR_WHITE (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))		// ��
#define COLOR_RED	(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f))		// ��
#define COLOR_GREEN (D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f))		// ��
#define COLOR_YERROW (D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f))	// ���F
#define COLOR_BLUE	 (D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f))	// ��
#define COLOR_PURPLE (D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f))	// ��
#define COLOR_GLAY	 (D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f))	// �O���[
#define LASER		 (D3DXCOLOR(0.05f, 0.05f, 1.0f, 1.0f))	// ���[�U�[�G�t�F�N�g
#define COLOR_NULL	 (D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f))	// ���S����

#define MAX_WORD (256)		// �ő啶���z��

//**********************
// ���_���[2D]�̍\����
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

//**********************
// ���_���[3D]�̍\����
//**********************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

//*****************************
// ���_���[3D_�}���`]�̍\����
//*****************************
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
	D3DXVECTOR2 texM;	// �}���`�e�N�X�`��
}VERTEX_3D_MULTI;

#endif