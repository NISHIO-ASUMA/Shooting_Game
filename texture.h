//=====================================
//
// �e�N�X�`������ [ texture.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _TEXTURE_H_ // ���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*****************************
// �e�N�X�`���Ǘ��N���X���`
//*****************************
class CTexture
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CTexture();
	~CTexture();

	// �����o�֐�
	HRESULT Load(void);
	void UnLoad(void);
	int Register(const char* pFileName);
	LPDIRECT3DTEXTURE9 GetAddress(int nIdx);

private:

	static inline constexpr int NUM_TEXTURE = 128;	// �ő�e�N�X�`����

	// �e�N�X�`���ǂݍ��ݔz����쐬
	const char* TexName[NUM_TEXTURE] =
	{
		"data\\TEXTURE\\explosion000.png",
		"data\\TEXTURE\\effect000.jpg",
		"data\\TEXTURE\\bullet002.png",
		"data\\TEXTURE\\num001.png",
		"data\\TEXTURE\\field000.jpeg",
		"data\\TEXTURE\\DomeTex.jpg",
		"data\\TEXTURE\\shadow000.jpg",
		"data\\TEXTURE\\lifegage.png",
		"data\\TEXTURE\\lifeframe.png",
		"data\\TEXTURE\\score001.png",
		"data\\TEXTURE\\PauseBack.png",
		"data\\TEXTURE\\titlemenu001.png",
		"data\\TEXTURE\\titilemenu_002.png",
		"data\\TEXTURE\\titlemenu_003.png",
		"data\\TEXTURE\\tutorial_menu.png",
		"data\\TEXTURE\\logo.png",
		"data\\TEXTURE\\Enterkey.png",
		"data\\TEXTURE\\boss_life.png",
		"data\\TEXTURE\\boss_frame.png",
		"data\\TEXTURE\\pausemenu_continue.png",
		"data\\TEXTURE\\pausemenu_retry.png",
		"data\\TEXTURE\\pausemenu_quit.png",
		"data\\TEXTURE\\Pause_ui.png",
		"data\\TEXTURE\\resultlogo.png",
		"data\\TEXTURE\\playerlife_frame000.png",
		"data\\TEXTURE\\playerlife_gage000.png",
		"data\\TEXTURE\\time000.png",
		"data\\TEXTURE\\alert.png",
		"data\\TEXTURE\\guard.png",
		"data\\TEXTURE\\model_GuardTex.png",
		"data\\TEXTURE\\laser.png",
		"data\\TEXTURE\\laser_gage.png",
		"data\\TEXTURE\\bosslife_frame.png",
		"data\\TEXTURE\\Boss_face.png",
		"data\\TEXTURE\\MeshPiler.png",
		"data\\TEXTURE\\MeshPiler1.jpg",
		"data\\TEXTURE\\Item_life.png",
		"data\\TEXTURE\\PointUi.png",
		"data\\TEXTURE\\title_menuselect.png",
		"data\\TEXTURE\\Billboard_startmenu.png",
		"data\\TEXTURE\\Laser_Icon.png",
		"data\\TEXTURE\\LoseResult.jpg",
		"data\\TEXTURE\\resultback.jpg",
		"data\\TEXTURE\\Normal_bullet.png",
		"data\\TEXTURE\\CameraAnimBox.png",
		"data\\TEXTURE\\ResultScore.png",
		"data\\TEXTURE\\number003.png",
		"data\\TEXTURE\\coron.png",
		"data\\TEXTURE\\RankBack.jpg",
		"data\\TEXTURE\\star.jpg",
		"data\\TEXTURE\\color.jpg",
		"data\\TEXTURE\\handeffect.jpg",
		"data\\TEXTURE\\alert_frame.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_move.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_Attack.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_Jump.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_JumpAttack.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_gauge.png",
		"data\\TEXTURE\\ComboMenu\\Tutorial_menu_free.png",
	};

	LPDIRECT3DTEXTURE9 m_apTexture[NUM_TEXTURE];	// �e�N�X�`���|�C���^
	static int m_nNumAll;							// �e�N�X�`���J�E���g�ϐ�
};

#endif