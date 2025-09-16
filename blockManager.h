//==============================================
//
// �u���b�N�S�̂̊Ǘ����s�� [ blockmanager.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _BLOCKMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _BLOCKMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`
 
//*******************************
// �C���N���[�h�t�@�C���錾
//*******************************
#include "objectX.h"
#include "block.h"
#include <vector>

//********************************
// �u���b�N�}�l�[�W���[�N���X��`
//********************************
class CBlockManager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CBlockManager();
	~CBlockManager();

	// �����o�֐�
	HRESULT Init(const char * filename , D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);

	// �ÓI�����o�֐�
	static CBlock* Create(const char* pfileName, D3DXVECTOR3 pos, D3DXVECTOR3 rot,float Size);

private:
	static std::vector<CBlock*> m_blocks; // �z��
	static int m_nIdxCount;	// ���f���C���f�b�N�X�ԍ�

};

#endif // !_BLOCKMANAGER_H_


