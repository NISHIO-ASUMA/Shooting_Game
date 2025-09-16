//====================================================
//
// �V�[���t�@�C���ǂݍ��ݏ��� [ sceneloader.h ]
// Author: Asuma Nishio
//
//====================================================

//**********************************
// �X�N���v�g�t�@�C���ǂݍ��ݏ���
//**********************************
class CSceneLoader
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CSceneLoader();
	~CSceneLoader();

	// �ÓI�����o�֐�
	static void SplitLoad(int nIdx);

private:

	// �t�@�C�����X�g
	static constexpr const char* m_aFileList[] = 
	{
		"data\\SceneText\\TitleObj.txt",// [0] �^�C�g��
		"data\\SceneText\\TutoObj.txt",	// [1] �`���[�g���A��
		"data\\SceneText\\GameObj.txt",	// [2] �Q�[��
	};
};

