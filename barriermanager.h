//===================================================
//
// �o���A�I�u�W�F�N�g�̊Ǘ����� [ barriermanager.h ]
// Author : Asuma Nishio
//
//===================================================

#ifndef _BARRIERMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _BARRIERMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//************************************
// �O���錾
//************************************
class CBarrierDurability;

//************************************
// �o���A�I�u�W�F�N�g�Ǘ��N���X���`
//************************************
class CBarrierManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBarrierManager();
	~CBarrierManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void DamageBarrier(int nValue);

	// �Z�b�^�[
	void AddBarrier(int nValue, D3DXVECTOR3 playerPos, float fRadius);

	// �Q�b�^�[
	int GetNumBarrier() const { return m_nBarrierNum; }

private:

	static inline constexpr int MAX_GUARD = 3; // �ő�o���A��

	int m_nBarrierNum; // �o���A����
	CBarrierDurability* m_pBarrierObj[MAX_GUARD]; // �o���A�I�u�W�F�N�g�̃|�C���^

};

#endif