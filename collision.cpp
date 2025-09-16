//=============================================
//
// �����蔻��̊Ǘ����s�� [ collision.h ]
// Author: Asuma Nishio
// 
//==============================================

//*****************************
// �C���N���[�h�t�@�C��
//*****************************
#include "collision.h"

//==============================================
// �R���X�g���N�^
//==============================================
CCollision::CCollision()
{
	// �Ȃ�
}
//==============================================
// �f�X�g���N�^
//==============================================
CCollision::~CCollision()
{
	// ����
}
//==============================================
// ���`�����蔻��
//==============================================
bool CCollision::CollisionSphere(D3DXVECTOR3* pPos, D3DXVECTOR3* pDestPos,const float fMyRadius,const float fHitRadius)
{
	// �����̍������v�Z����
	float fDisX = pDestPos->x - pPos->x;
	float fDisY = pDestPos->y - pPos->y;
	float fDisZ = pDestPos->z - pPos->z;

	// ���a�̃T�C�Y���v�Z
	float fRadX = fMyRadius + fHitRadius;
	float fRadY = fMyRadius + fHitRadius;
	float fRadZ = fMyRadius + fHitRadius;

	// �������v�Z����
	float fDissAll = (fDisX * fDisX) + (fDisY * fDisY) + (fDisZ * fDisZ);
	float fRadAll = (fRadX + fRadY + fRadZ) * (fRadX + fRadY + fRadZ);

	// ���a���ɓ����Ă�����
	if (fDissAll <= fRadAll)
	{
		// �R���W���������Ԃ�
		return true;
	}

	// �͈͊O�œ������Ă��Ȃ��Ƃ�
	return false;
}
