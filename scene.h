//====================================
//
// �V�[������ [ scene.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _SCENE_H_ // ���̃}�N����`������ĂȂ�������
#define _SCENE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �V�[���N���X���`
//******************************
class CScene 
{
public:
	//*************************
	// �V�[���̎�ޗ񋓌^
	//*************************
	enum MODE
	{
		MODE_NONE,		// ��������
		MODE_TITLE,		// �^�C�g��
		MODE_TUTORIAL,	// �`���[�g���A��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_LOSERESULT,// �������U���g
		MODE_RANKING,	// �����L���O
		MODE_EDIT,		// �z�u���[�h
		MODE_CAMERAEDIT,// �z�u���[�h
		MODE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CScene(MODE mode);
	virtual ~CScene();

	// �������z�֐�
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;

	// �Q�b�^�[
	MODE GetScene(void) const { return m_Scene; }

private:
	MODE m_Scene;	// �V�[���Ǘ��ϐ�
};

#endif
