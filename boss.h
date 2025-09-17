//====================================
//
// �{�X���� [ boss.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _BOSS_H_ // ���̃}�N����`������ĂȂ�������
#define _BOSS_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//******************************
// �C���N���[�h�t�@�C��
//******************************
#include "object.h"
#include "model.h"
#include "motion.h"

//**********************
// �O���錾
//**********************
class CParameter;
class CStateMachine;
class CBossStateBace;

//**********************
// �{�X�N���X���`
//**********************
class CBoss : public CObject
{
public:
	//***************************
	// ���[�V�����񋓌^�錾
	//***************************
	enum TYPE
	{
		TYPE_NEUTRAL = 0,	// �j���[�g����
		TYPE_ACTION,		// �r�U��
		TYPE_IMPACT,		// �@�����Ռ��g
		TYPE_RUBBLE,		// ���I�U��
		TYPE_CIRCLE,		// �ガ����
		TYPE_ARMRIGHTLEFT,	// �U�艺�낵�U��
		TYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CBoss(int nPriority = static_cast<int>(CObject::PRIORITY::CHARACTOR));
	~CBoss();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	bool CollisionRightHand(D3DXVECTOR3* pPos);
	bool CollisionImpactScal(D3DXVECTOR3* pPos);
	bool CollisionCircle(D3DXVECTOR3* pPos, float fHitRadius);
	bool CollisionSwing(D3DXVECTOR3* pPos, float fHitRadius);

	void Hit(int nDamage,D3DXVECTOR3 HitPos);
	void ChangeState(CBossStateBace* pNewState, int Id);
	void RollToPlayer(void);
	void DecCoolTime(void) { if (m_nCoolTime > 0) m_nCoolTime--; }
	void SaveHp(void);

	// �Z�b�^�[
	void SetCoolTime(int nCooltime) { m_nCoolTime = nCooltime; }
	void SetWeekPoint(const D3DXVECTOR3 pos) { m_WeekPointPos = pos; }
	void SetMovePos(bool isFlags) { m_isSet = isFlags; }

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos;}
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	CParameter* GetParam(void) { return m_pParam; }
	CMotion* GetMotion(void) { return m_pMotion; }

	int GetCoolTime(void) const { return m_nCoolTime; }
	float GetSize(void) { return m_fSize; }

	bool GetIsSet(void) { return m_isSet; }

	// �ÓI�����o�֐�
	static CBoss* Create(D3DXVECTOR3 pos, float fSize,int nLife);
	static bool IsDaeth(void) { return m_isdaeth;}
	CModel*GetModelPartType(CModel::PARTTYPE modelpart);

private:

	static constexpr int NUMMODELS = 21; // �g�����f����
	static constexpr float WEEKPOINTSIZE = 100.0f;

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_WeekPointPos;
	D3DXMATRIX m_mtxworld;	// �}�g���b�N�X

	CModel* m_pModel[NUMMODELS]; // ���f���̃|�C���^
	CMotion* m_pMotion;		// ���[�V�����|�C���^
	CParameter* m_pParam;	// �p�����[�^�[�|�C���^
	CStateMachine* m_pState; // �X�e�[�g�|�C���^

	int m_type;				// ���[�V�����̎�ޕϐ�
	int m_nCoolTime;		// �N�[���^�C��
	int m_nCurrentMotion;

	float m_fSize;			// �T�C�Y
	bool m_isEvent;			// �C�x���g���s������
	bool m_isSet;				// �Z�b�g�|�W�V�����ɓ�������

	static bool m_isdaeth;
};

#endif
