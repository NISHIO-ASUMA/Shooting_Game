//=============================================
//
// �����蔻��̊Ǘ����s�� [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

#ifndef _COLLISION_H_ // ���̃}�N����`������ĂȂ�������
#define _COLLISION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//************************************
// �R���W�����N���X���`
//************************************
class CCollision
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CCollision();
	~CCollision();

	// �����o�֐�
	bool CollisionSphere(D3DXVECTOR3* pPos, D3DXVECTOR3* pDestPos, const float fMyRadius, const float fHitRadius);

private:

};

#endif // !_COLLISION_H_






