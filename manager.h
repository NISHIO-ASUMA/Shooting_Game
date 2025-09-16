//====================================
//
// �}�l�[�W���[���� [ manager.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _MANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**************************  
// �C���N���[�h�t�@�C���錾
//**************************
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "debugproc.h"
#include "bullet.h"
#include "enemymanager.h"
#include "texture.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "blockManager.h"
#include "collision.h"
#include "meshcylinder.h"
#include "boss.h"
#include "scene.h"
#include "fade.h"

//**************************
// �}�l�[�W���[�N���X�錾
//**************************
class CManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CManager();
	~CManager();

	// �����o�֐�
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �ÓI�����o�֐�
	static CRenderer* GetRenderer(void) { return m_pRenderer; }
	static CInputKeyboard* GetInputKeyboard(void) { return m_pInputKeyboard; }
	static CJoyPad* GetJoyPad(void) { return m_pJoyPad; }
	static CSound* GetSound(void) { return m_pSound; }
	static CInputMouse* GetMouse(void) { return m_pInputMouse; }
	static CTexture* GetTexture(void) { return m_pTexture; }
	static CCamera* GetCamera(void) { return m_pCamera; }
	static CLight* GetLight(void) { return m_pLight; }
	static CCollision* GetCollision(void) { return m_pCollision; }
	static CScene* Getscene(void) { return m_pScene; }
	static CFade* GetFade(void) { return m_pFade; }

	static void SetScene(CScene * pNewScene);
	static CScene::MODE GetScene(void);

private:
	static CRenderer* m_pRenderer;			// �����_���[�N���X�̃|�C���^
	static CInputKeyboard* m_pInputKeyboard;// �L�[�{�[�h�N���X�̃|�C���^
	static CJoyPad* m_pJoyPad;				// �W���C�p�b�h�N���X�̃|�C���^
	static CSound* m_pSound;				// �T�E���h�I�u�W�F�N�g�̃|�C���^
	static CInputMouse* m_pInputMouse;		// �}�E�X�N���X�̃|�C���^
	static CTexture* m_pTexture;			// �e�N�X�`���N���X�̃|�C���^
	static CCamera* m_pCamera;				// �J�����N���X�̃|�C���^
	static CLight* m_pLight;				// ���C�g�N���X�̃|�C���^
	static CScene* m_pScene;				// �V�[���Ǘ��N���X�̃|�C���^
	static CFade* m_pFade;					// �t�F�[�h�N���X�̃|�C���^
	static CCollision* m_pCollision;		// �R���W�����N���X�ւ̃|�C���^
};
#endif