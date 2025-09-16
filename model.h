//====================================
//
// ���f������ [ model.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MODEL_H_ // ���̃}�N����`������ĂȂ�������
#define _MODEL_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// ���f���N���X�̒�`
//**********************
class CModel
{
public:
	//*********************
	// �p�[�c�̃^�C�v�񋓌^
	//********************
	enum PARTTYPE
	{
		PARTTYPE_NONE, // ������ނ�ݒ肵�Ȃ���
		PARTTYPE_HEAD, // ��
		PARTTYPE_CHEST, // ��
		PARTTYPE_LEFT_HAND, // ���r
		PARTTYPE_RIGHT_HAND,// �E�r
		PARTTYPE_LEFT_LEG, //����
		PARTTYPE_RIGHT_LEG,// �E��
		PARTTYPE_WEAPON,   // ����
		PARTTYPE_FOOT,
		PARTTYPE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CModel();
	~CModel();

	// �����o�֐�
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetParent(CModel* pModel);
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	void OffSetPos(D3DXVECTOR3 offpos) { m_offPos = offpos; }
	void OffSetRot(D3DXVECTOR3 offrot) { m_offRot = offrot; }
	void SetPartType(PARTTYPE nDestPartType) { m_parttype = nDestPartType; }

	// �Q�b�^�[
	D3DXMATRIX GetMtxWorld(void) { return m_mtxworld; }
	PARTTYPE GetPartType(void) const { return m_parttype; }

	// �t���O�����g
	bool IsPlayer() const { return m_isPlayer; }
	bool IsBoss() const { return m_isBoss; }
	void SetIsBoss(bool flag) { m_isBoss = flag; }
	void SetIsPlayer(bool flag) { m_isPlayer = flag; }

	// �ÓI�����o�֐�
	static CModel* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char* pFilename);

private:

	D3DXVECTOR3 m_pos, m_rot,m_offPos,m_offRot; // ���W,�p�x

	D3DXMATRIX m_mtxworld;	  // ���[���h�}�g���b�N�X
	CModel* m_pParent;		  // �e���f��

	LPD3DXMESH m_pMesh;	   // ���b�V�����
	LPD3DXBUFFER m_pBuffMat; // �}�e���A�����
	DWORD m_dwNumMat;		// �}�e���A����
	int* m_pTexture;		// �e�N�X�`���|�C���^

	PARTTYPE m_parttype;    // ���f���̎��

	bool m_isPlayer; // �v���C���[�ɑΉ��������f�����ǂ���
	bool m_isBoss;
};

#endif