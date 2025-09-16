//=========================================
//
// �^�C�g���v���C���[���� [ titleplayer.h ]
// Author: Asuma Nishio
//
//=========================================

#ifndef _TITLEPLAYER_H_ // ���̃}�N����`������ĂȂ�������
#define _TITLEPLAYER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//********************************
// �C���N���[�h�t�@�C���錾
//********************************
#include "object.h"
#include "model.h"
#include "motion.h"

//********************************
// �O���錾
//********************************
class CInputKeyboard;
class CShadowS;

//********************************************
// �^�C�g���v���C���[�I�u�W�F�N�g�N���X���`
//********************************************
class CTitlePlayer : public CObject
{
public:
	//***********************
	// �g�p���[�V����
	//***********************
	enum TITLEMOTION
	{
		TITLEMOTION_NEUTORAL,
		TITLEMOTION_ACTION,
		TITLEMOTION_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CTitlePlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CTitlePlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	// �ÓI�����o�֐�
	static CTitlePlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const int nIdxParson, const char* pFilename); 
	static CTitlePlayer* GetIdxPlayer(int Idx);

private:
	static inline constexpr int TITLE_MODEL = 19; // �K�w�\�����f����

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;  // �ړI�p

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[TITLE_MODEL]; // �g�����f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����̃|�C���^

	int m_nIdxPlayer;		// �v���C���[�̎��ʔԍ�
	const char* m_pFilename; // �ǂݍ��ރt�@�C����

};

#endif