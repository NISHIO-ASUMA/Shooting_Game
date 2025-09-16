//=====================================
//
// �t�F�[�h���� [ fade.h ]
// Author: Asuma Nishio
// 
//=====================================

#ifndef _FADE_H_ // ���̃}�N����`������ĂȂ�������
#define _FADE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �O���錾
//**********************
class CScene;

//**********************
// �t�F�[�h�N���X���`
//**********************
class CFade
{
public:

	//**********************
	// �t�F�[�h��ԗ񋓌^
	//**********************
	enum FADE
	{
		FADE_NONE,	// �����Ȃ�
		FADE_IN,	// �t�F�[�h�C��
		FADE_OUT,	// �t�F�[�h�A�E�g
		FADE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CFade();
	~CFade();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetFade(CScene * pNewScene);

	// �Q�b�^�[
	FADE GetFade(void) { return m_fade; }

private:

	static constexpr float AlphaFade = 0.025f; // �t�F�[�h�ŉ��Z����l

	LPDIRECT3DVERTEXBUFFER9 m_pVtx; // ���_�o�b�t�@
	D3DXCOLOR m_col;				// �|���S���J���[
	FADE m_fade;					// �t�F�[�h�̗񋓌^�ϐ�
	CScene* m_pScene;				// �V�[���N���X�̃|�C���^
};

#endif