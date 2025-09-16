//=======================================
//
// ���U���g�X�R�A���� [ resultscore.h ]
// Author: Asuma Nishio
// 
//=======================================

#ifndef _RESULTSCORE_H_ // ���̃}�N����`������ĂȂ�������
#define _RESULTSCORE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "number.h"
#include "object.h"

//****************************
// ���U���g�X�R�A�N���X���`
//****************************
class CResultScore : public CObject
{
public:
	//****************************
	// ��ޒ�`
	//****************************
	enum TYPE
	{
		SCORE_GAME,
		SCORE_TIME,
		SCORE_LAST,
		SCORE_MAX
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CResultScore(int nPriority = static_cast<int>(CObject::PRIORITY::UI));
	~CResultScore();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Save(void);

	// �Z�b�^�[
	void SetTexture(void);
	void SetScore(int nResultValue) { m_nScore = nResultValue; }
	void SetTimeScore(int nResultValue) { m_nTimeScore = nResultValue; }
	void SetLastScore(int nResultValue, int nResultValue1) { m_nLastScore = nResultValue + nResultValue1; }

	int MathTimescore(void);

	// �ÓI�����o�֐�
	static CResultScore* Create(D3DXVECTOR3 pos, float fWidth, float fHeight,int nType);

private:
	static constexpr int NUM_RESULTSCORE = 5; // ����
	static constexpr int NUM_RESULTDIGIT = 10; // �\�����镪�������̒l
	static constexpr int NUM_SAVESCORE = 5;

	int m_nScore;			// �X�R�A�ێ��p
	int m_nDestScore;		// �ړI�̃X�R�A
	int m_nTimeScore;		// ���Ԃ̃X�R�A
	int m_nDestTimeScore;	// �ړI�̃^�C���X�R�A
	int m_nLastScore;		// �ŏI�ۑ��X�R�A
	int m_nDestLastScore;	// �ړI�̍ŏI�X�R�A
	int m_nType;			// ���

	CNumber* m_apNumber[NUM_RESULTSCORE];	// �������̃i���o�[�̃|�C���^
	D3DXVECTOR3 m_pos;		// ���W
	D3DXVECTOR3 m_DestPos;  // �ړI�̍��W
	float m_fWidth;			// ����
	float m_fHeight;		// ����

	float m_fScale;			// ���݂̊g�k�{��
	float m_fTargetScale;	// �ŏI�I�Ȋg�k�{��
	float m_fScaleSpeed;	// �k���X�s�[�h

	int m_nIdxTexture;		// �e�N�X�`���C���f�b�N�X
};

#endif