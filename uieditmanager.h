//=================================================
//
// UI�G�f�B�^�[�V�[���Ǘ����� [ uieditmanager.h ]
// Author : Asuma Nishio
// 
// TODO : �Ƃō�Ƃ���
//
//=================================================

#ifndef _UIEDITMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _UIEDITMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************************
// �Ǘ��N���X���`
//**********************************
class CUiEditManager
{
public:
	//=====================
	// �����o���p�X�̎��
	//=====================
	enum SAVEPASS
	{
		SAVEPASS_TUTO,
		SAVEPASS_GAME,
		SAVEPASS_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CUiEditManager();
	~CUiEditManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Save(void);

	// �Z�b�^�[
	D3DXVECTOR3 SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 SetRot(D3DXVECTOR3 rot) { m_rot = rot; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos() const { return m_pos; }
	D3DXVECTOR3 GetRot() const { return m_rot; }

private:
	//*******************************
	// �t�@�C���p�X���i�[���郊�X�g
	//*******************************
	const char* FILELIST[SAVEPASS_MAX] =
	{
		"data\\Loader\\ui_tuto.txt",
		"data\\Loader\\ui_game.txt",
	};

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXMATRIX m_mtxworld;

	int m_nTypeIdx; // �C���f�b�N�X
	int m_nSelectIndex; // �I�𒆃I�u�W�F�N�g�̃C���f�b�N�X
	int m_nSavePassIdx;
	int m_nNumAll;		// ������

};
#endif

