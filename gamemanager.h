//==========================================
//
// �Q�[���Ǘ����� [ gamemanager.h ]
// Author: Asuma Nishio
// 
//==========================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "meshcylinder.h"
#include "boss.h"
#include "block.h"
#include "time.h"
#include "uimanager.h"
#include "barriermanager.h"
#include "rubblemanager.h"

//*****************************
// �O���錾
//*****************************
class CItemManager;
class CPilerManager;

//*****************************
// �Q�[����ԊǗ��N���X���`
//*****************************
class CGameManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CGameManager();
	~CGameManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static CMeshCylinder* GetCylinder(void) { return m_pMeshCylinder; }
	static CBoss* GetBoss(void) { return m_pBoss; }
	static CTime* GetTime(void) { return m_pTime; }
	static CUimanager* GetUimanager(void) { return m_puimanager; }
	static CBarrierManager* GetBarrier(void) { return m_pBarrier; }
	static CRubbleManager* GetRubble(void) { return m_pRubble; }

private:
	static CMeshCylinder* m_pMeshCylinder;		// �V�����_�[
	static CBoss* m_pBoss;						// �{�X
	static CTime* m_pTime;						// �^�C�}�[
	static CUimanager* m_puimanager;			// UI�}�l�[�W���[
	static CBarrierManager* m_pBarrier;
	static CRubbleManager* m_pRubble;

	CItemManager* m_pItemManager;		// �A�C�e���}�l�[�W���[�|�C���^
	CPilerManager* m_pPilerManager;

};

