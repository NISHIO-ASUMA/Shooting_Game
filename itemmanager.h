//============================================
//
// �A�C�e���Ǘ����� [ itemmanager.h ]
// Author : Asuma Nishio
//
//============================================

#ifndef _ITEMMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _ITEMMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �A�C�e���S�̂̊Ǘ��N���X���`
//*********************************
class CItemManager
{
public:
	
	// �R���X�g���N�^�E�f�X�g���N�^
	CItemManager();
	~CItemManager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:

	static constexpr int NUMPOINT = 4;											   // �o���|�C���g�̐�
	static constexpr const char* MODELNAME = "data\\MODEL\\STAGEOBJ\\Item_life.x"; // �I�u�W�F�N�g�t�@�C����

	//*************************
	// �A�C�e���o�����W���X�g
	//*************************
	D3DXVECTOR3 m_ActivePointPos[NUMPOINT] =
	{
		{100.0f,50.0f,-550.0f},
		{100.0f,50.0f,550.0f},
		{530.0f,50.0f,150.0f},
		{-530.0f,50.0f,-150.0f},
	};
};

#endif
