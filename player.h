//====================================
//
// �v���C���[���� [ player.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _PLAYER_H_ // ���̃}�N����`������ĂȂ�������
#define _PLAYER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// �O���錾
//**********************
class CShadow;
class CInputKeyboard;
class CJoyPad;
class CCamera;
class CParameter;
class CShadowS;
class CStateMachine;
class CPlayerStateBase;

//*************************
// �v���C���[�N���X���`
//*************************
class CPlayer : public CObject
{
public:
	//***********************************
	// �v���C���[���s�����[�V�����񋓌^
	//***********************************
	enum PLAYERMOTION
	{
		PLAYERMOTION_NEUTRAL,		// �j���[�g����
		PLAYERMOTION_MOVE,			// �ړ�
		PLAYERMOTION_ACTION,		// �A�N�V����
		PLAYERMOTION_JUMP,			// �W�����v
		PLAYERMOTION_LANDING,		// ���n
		PLAYERMOTION_JUMPATTACK,	// �W�����v�U��
		PLAYERMOTION_DAMAGE,		// �_���[�W
		PLAYERMOTION_GUARD,			// �K�[�h
		PLAYERMOTION_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CPlayer(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CPlayer();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void ChangeState(CPlayerStateBase* pNewState,int Id); // �X�e�[�g�ύX
	void UpdateAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestPos, CJoyPad* pPad); // �ʏ�U���X�V�֐�
	void UpdateMove(const D3DXVECTOR3 DestPos, CInputKeyboard* pInputKeyboard, CJoyPad* pPad);					  // �ړ��X�V�֐�
	void UpdateJumpAction(CInputKeyboard* pInputKeyboard, D3DXMATRIX pMtx, const D3DXVECTOR3 DestMove, CJoyPad* pPad);
	void UpdateGuard(void);
	void Collision(void);
	void StickState(void);

	D3DXVECTOR3 VecToBoss(const D3DXVECTOR3& pPos);
	D3DXVECTOR3 VecToCenter(const D3DXVECTOR3& pPos);

	void InitPos(float fAngle);
	void StartJump(void);
	void GravityScal(void);
	void HitDamage(int nDamage);

	// �Z�b�^�[
	void SetRotDest(D3DXVECTOR3 rotDest) { m_rotDest = rotDest; }
	void SetJump(bool isJump) { m_isJump = isJump; }
	void SetLanding(bool isLanding) { m_isLanding = isLanding; }
	void AddMove(void) { m_pos += m_move; }
	void SetValue(float fValue) { m_fValue = fValue; }
	void JumpMove(void) { m_move.y = m_fValue; }
	void SetIsDamege(bool isFlags) { m_isDecHp = isFlags; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }			// ���݂̍��W���擾
	D3DXVECTOR3 GetOldPos(void) { return m_posOld; }	// �ߋ��̍��W���擾
	D3DXVECTOR3 GetRot(void) { return m_rot; }			// ���݂̊p�x���擾
	D3DXVECTOR3 GetRotDest(void) { return m_rotDest; }	// �ړI�p���擾
	PLAYERMOTION GetNowMotion(void) const;

	CModel* GetModelPartType(CModel::PARTTYPE modelpart);
	CMotion* GetMotion(void) { return m_pMotion; }
	CParameter* GetParameter(void) { return m_pParameter; }
	CStateMachine* GetStateMachine() { return m_pStateMachine; }	// �v���C���[�̃X�e�[�g�}�V�����擾

	int GetType(void) { return m_type; }
	int GetPlayerIndex() const { return m_nIdxPlayer; }

	// �t���O�����g�֐�
	bool IsJumping() { return m_isJump; } 	// �W�����v��Ԃ̊m�F
	bool isMoveInputKey(CInputKeyboard* pKeyInput);
	bool isMovePadButton(CJoyPad* pPad);
	bool isAttackeyPress(CInputKeyboard* pKeyInput);
	bool isLanding(void) { return m_isJump; }
	bool GetLanding(void) { return m_isLanding; }
	bool GetIsDamege(void) { return m_isDecHp; }

	// �ÓI�����o�֐�
	static CPlayer* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nLife, const int nIdxParson, const char* pFilename); // ��������
	static bool IsDeath(void) { return m_isDeath; }
	static CPlayer* GetIdxPlayer(int Idx); // �C���f�b�N�X�ԍ��Ŏ擾

private:
	static inline constexpr int MAX_MODEL = 19; // �v���C���[�Ŏg�����f���̐�

	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_rotDest;  // �ړI�p

	D3DXVECTOR3 m_pos;		// �K�w�\���ݒ���W
	D3DXVECTOR3 m_posOld;	// �ߋ��̍��W���
	D3DXVECTOR3 m_rot;		// �p�x
	D3DXVECTOR3 m_Scal;
	D3DXMATRIX m_mtxworld;	// ���[���h�}�g���b�N�X

	CModel* m_apModel[MAX_MODEL]; // �g�����f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����̃|�C���^
	CShadow* m_pShadow;		// �e�N���X�̃|�C���^�ϐ�
	CParameter* m_pParameter; // �p�����[�^�[�N���X�|�C���^
	CShadowS* m_pShadowS;	// �X�e���V���V���h�E�N���X�|�C���^
	CStateMachine* m_pStateMachine;	// �X�e�[�g���N���X�̃|�C���^

	int m_type;				// ���[�V�����̎�ޕϐ�
	int m_nNumAll;			// ���f������
	int m_State;			// ��ԊǗ��J�E���^�[
	int m_nIdxTexture;		// �e�N�X�`��ID
	int m_nIdxPlayer;		// �v���C���[�̎��ʔԍ�

	bool m_isLanding;		// ���n����
	bool m_isJump;			// �W�����v����
	bool m_isMoving;		// �ړ��L�[����
	bool m_isAttack;		// �U������
	bool m_isShadow;
	bool m_isStateSynchro;
	bool m_isConectPad;
	bool m_isGuard;
	bool m_isDecHp;

	float m_fAngle;			// ���݂̊p�x
	float m_fValue;

	const char* m_pFilename; // �ǂݍ��ރt�@�C����

	static bool m_isDeath; // �ÓI

};

#endif