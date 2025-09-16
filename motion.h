//=====================================
//
// ���[�V�������� [ motion.h ]
// Author: Asuma Nishio
//
//=====================================

#ifndef _MOTION_H_ // ���̃}�N����`������ĂȂ�������
#define _MOTION_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//**********************
// �C���N���[�h�t�@�C��
//**********************
#include "model.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

//*****************************
// ���[�V�����N���X���`
//*****************************
class CMotion
{
public:
	//***************************
	// �L�[�\���̐錾
	//***************************
	struct KEY
	{
		float fPosX;	// �ʒuX
		float fPosY;	// �ʒuY
		float fPosZ;	// �ʒuZ
		float fRotX;	// �p�xX
		float fRotY;	// �p�xY
		float fRotZ;	// �p�xZ
	};

	//***************************
	// �L�[���̍\���̐錾
	//***************************
	struct KEY_INFO
	{
		int nFrame;				// �t���[����
		std::vector<KEY> aKey; // ���I�ȃL�[��
	};

	//***************************
	// ���[�V�������̍\���̐錾
	//***************************
	struct INFO
	{
		bool bLoop;						// ���[�v���邩���Ȃ���
		int nNumKey;					// �L�[�̑���
		std::vector<KEY_INFO> aKeyInfo; // ���[�V�����̓��I�L�[�t���[��
	};

	// �R���X�g���N�^�E�f�X�g���N�^
	CMotion();
	~CMotion();

	// �����o�֐�
	void Update(CModel** ppModel, const int nMaxPart);
	void UpdateCurrentMotion(CModel** ppModel, int nModelCount);
	void UpdateBlend(CModel** ppModel, int nModelCount);
	void Debug(void);
	bool CheckFrame(int nStartMotion, int nEndMotion, int nMotionType);
	void NorRot(float* pRotX, float* pRotY, float* pRotZ);

	// �Z�b�^�[
	void SetMotion(int motiontype);
	void SetMotionNum(int nMotion) { m_nNumMotion = nMotion; }
	int SetModels(std::istringstream& iss, int nMaxParts);
	void SetModelFile(std::istringstream& iss, CModel** pModel, int nCnt);
	void SetParts(std::ifstream& file, CModel** pModel);
	void SetPartsMotion(std::ifstream& file, CMotion* pMotion, int nCntMotion);
	void SetKey(std::ifstream& file, CMotion* pMotion, int nCntMotion, int nCntKey);
	void SetKeyDate(std::istringstream& ss, const std::string& param, CMotion* pMotion, int nCntMotion, int nCntKey, int& posKeyIndex, int& rotKeyIndex);
	void SetMotion(int nMotionType, bool isBlend, int nBlendFrame, bool isBoss);
	void SetResetFrame(int nFrame) { m_nCounterMotion = nFrame;}

	// �Q�b�^�[
	int GetMotionType(void) { return m_motiontype; }
	bool GetFinishMotion(void) { return m_isFinishMotion; }

	// �ÓI�����o�֐�
	static CMotion* Load(const char* pFilename, const int nMaxParts,CModel ** pModel,int nDestMotions);

private: 
	std::vector<INFO> m_aMotionInfo; // ���[�V�������𓮓I�m��

	bool m_isLoopMotion;				// ���[�v���邩�ǂ���

	int m_nNumMotion;					// ���[�V�����̑���
	int m_nNumKey;						// �L�[�̑���
	int m_nKey;							// ���݂̃L�[No
	int m_nCounterMotion;				// ���[�V�����̃J�E���^�[
	int m_nNextKey;						// ���̃L�[
	int m_motiontype;					// ���[�V�����^�C�v
	int m_type;

	bool m_isBlendMotion;				// �u�����h�����邩�ǂ���
	bool m_isFinishMotion;				// ���[�V�������I��������ǂ���
	bool m_isFirstMotion;				// ���[�V�������n�܂����t���O

	int m_motiontypeBlend;				// �u�����h�̎��
	int m_nFrameBlend;					// �u�����h�̃t���[����
	int m_nCounterBlend;				// �u�����h�J�E���^�[
	int m_nKeyBlend;					// �u�����h���[�V�����̌��݂̃L�[
	int m_nNextKeyBlend;				// �u�����h���[�V�����̎��̃L�[

	int m_nNumModels;
	int m_nNumAllFrame;	  // �L�[���Ƃ̃t���[����
	int m_nAllFrameCount; // �S�̃t���[����
	bool m_isStopAction;

	static constexpr int NEUTRAL = 0; // �j���[�g�����ԍ�
};

#endif

