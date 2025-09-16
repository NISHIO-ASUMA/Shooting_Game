//====================================
//
// �X�R�A���� [ score.h ]
// Author: Asuma Nishio
// 
//=====================================

#ifndef _SCORE_H_ // ���̃}�N����`������ĂȂ�������
#define _SCORE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "number.h"
#include "object.h"

//*******************************************
// �X�R�A�N���X���`
//*******************************************
class CScore : public CObject
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	// �Z�b�^�[
	void SetTexture(void);

	// �Q�b�^�[
	D3DXVECTOR3 GetPos(void) { return m_pos; }

	// �ÓI�����o�֐�
	static CScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight);
	static void AddScore(int nValue);
	static void DecScore(void);
	static int GetScore(void) { return m_nScore; }
	static void SaveScore(void);
	static void SetScore(int nDestScore) { m_nScore = nDestScore; }

private: 
	static constexpr int NUM_SCORE = 8; // ����
	static constexpr int NUM_DIGIT = 10; // �\�����镪�������̒l

	static int m_nScore;			// �X�R�A�ێ��p
	static int m_nDecCount;			// ���Z������

	CNumber *m_apNumber[NUM_SCORE];	// �������̃i���o�[�̃|�C���^
	D3DXCOLOR m_col;				// �J���[
	D3DXVECTOR3 m_pos;				// ���W
	D3DXVECTOR3 m_rot;				// �p�x
	
	float m_fWidth;					// ����
	float m_fHeight;				// ����
	int m_nIdxTexture;				// �e�N�X�`���C���f�b�N�X
};
#endif