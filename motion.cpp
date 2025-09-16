//====================================
//
// ���[�V�������� [ motion.cpp ]
// Author: Asuma Nishio
//
//=====================================

//**************************
// �C���N���[�h�t�@�C���錾
//**************************
#include "motion.h"
#include "template.h"
#include "player.h"
#include "boss.h"
#include "debugproc.h"

//==============================
// �R���X�g���N�^
//==============================
CMotion::CMotion()
{
	// �z��N���A
	m_aMotionInfo.clear();

	// �l�̃N���A
	m_isLoopMotion = false;
	m_nCounterMotion = NULL;
	m_nKey = NULL;
	m_nNumKey = NULL;
	m_nNumMotion = NULL;
	m_motiontype = NULL;
	m_type = NULL;
	m_nNextKey = NULL;

	m_motiontypeBlend = NULL;
	m_nFrameBlend = NULL;
	m_nCounterBlend = NULL;
	m_nKeyBlend = NULL;
	m_nNextKeyBlend = NULL;

	m_isBlendMotion = false;
	m_isFinishMotion = false;
	m_isFirstMotion = false;
	m_isStopAction = false;

	m_nNumModels = NULL;
	m_nAllFrameCount = NULL;
	m_nNumAllFrame = NULL;
}
//==============================
// �f�X�g���N�^
//==============================
CMotion::~CMotion()
{
	// ����
}
//==============================
// ���[�V�����ǂݍ��݊֐�
//==============================
CMotion* CMotion::Load(const char* pFilename,const int nMaxParts, CModel** pModel, int nDestMotions)
{
	// ���[�V�����N���X�̃C���X�^���X����
	CMotion* pMotion = new CMotion;

	// �t�@�C���ݒ�
	std::ifstream file(pFilename);

	// �t�@�C����O�`�F�b�N
	if (!file)
	{
		MessageBox(NULL, "�t�@�C���I�[�v�����s", pFilename, MB_OK);

		// �|�C���^�̔j��
		delete pMotion;

		// ���s���ʂ�Ԃ�
		return nullptr;
	}

	// ��s�ǂݍ���
	std::string line;

	// �g�p���[�J���ϐ�
	int nModel = 0;
	int nIdx = 0;
	int nCntMotion = 0;

	// ���̈����ɓǂݍ��ރ��[�V����������ݒ肵�Ă���̕�����m_amotionInfo�Ń��T�C�Y����
	pMotion->m_aMotionInfo.resize(nDestMotions);

	// �������ǂݑ�����
	while (std::getline(file, line))
	{
		// �g�[�N���ݒ�
		std::istringstream iss(line);
		std::string token;
		iss >> token;

		// "NUM_MODEL"�ǂݎ�莞
		if (token == "NUM_MODEL")
		{
			// ���f�����ݒ�
			nModel  = pMotion->SetModels(iss,nMaxParts);

			// �ǂݍ��񂾃��f������ۑ�����
			pMotion->m_nNumModels = nModel;

		}
		// "MODEL_FILENAME"�ǂݎ�莞
		else if (token == "MODEL_FILENAME")
		{
			// ���f���t�@�C���ǂݍ���
			pMotion->SetModelFile(iss, pModel, nIdx);

			// �C���f�b�N�X�J�E���g�����Z
			nIdx++;
		}
		// "PARTSSET"�ǂݎ�莞
		else if (token == "PARTSSET")
		{
			// �p�[�c���Ƃ̃Z�b�g
			pMotion->SetParts(file, pModel);
		}
		// "MOTIONSET"�ǂݎ�莞
		else if (token == "MOTIONSET")
		{
			// �p�[�c�̃��[�V�����̐ݒ�
			pMotion->SetPartsMotion(file, pMotion, nCntMotion);

			// ���[�V�����J�E���g�����Z
			nCntMotion++;
		}
		// "END_SCRIPT"�ǂݎ�莞
		else if (token == "END_SCRIPT")
		{
			break;
		}
	}

	// �t�@�C�������
	file.close();

	// �������ꂽ�|�C���^��Ԃ�
	return pMotion;
}
//=================================
// ���[�V�����Z�b�g
//=================================
void CMotion::SetMotion(int motiontype)
{
	// ������motiontype�ɓn���ꂽ�ԍ����擾����
	if (m_motiontype == motiontype)
	{
		// ������������
		return;
	}

	// ���
	m_motiontype = motiontype;
	m_nKey = 0;
	m_nCounterMotion = 0;
	m_nAllFrameCount = 0;
	m_isFinishMotion = false;
}
//======================================
// ���[�V�����Z�b�g��� (�u�����h����)
//======================================
void CMotion::SetMotion(int nMotionType, bool isBlend, int nBlendFrame,bool isBoss)
{
	// ������motiontype�ɓn���ꂽ�ԍ����擾����
	if (m_motiontype == nMotionType)
	{
		// ������������
		return;
	}

	// �u�����h���L����
	if (isBlend == true)
	{
		// �ŏ��̃��[�V�����u�����h���I����Ă���
		if (!m_isFirstMotion)
		{
			m_isFirstMotion = true;
			m_nKeyBlend = 0;				// 0����n�߂�
			m_nCounterBlend = 0;			// 0����n�߂�
		}

		m_isBlendMotion = isBlend;			// �u�����h�����邩�ǂ���
		m_nFrameBlend = nBlendFrame;		// �u�����h�̃t���[������
		m_motiontypeBlend = nMotionType;	// �u�����h���郂�[�V�����̃^�C�v����

		if (isBoss == false)
		{
			m_isFinishMotion = false;			// �I������𖳌���
		}

	}
	// ���[�V�����u�����h���Ȃ�
	else
	{
		// ������motiontype�ɓn���ꂽ�ԍ����擾����
		if (m_motiontype == nMotionType)
		{
			// ������������
			return;
		}

		// ���
		m_motiontype = nMotionType;
		m_nKey = 0;
		m_nCounterMotion = 0;
		m_nAllFrameCount = 0;
		m_isFinishMotion = false;
	}
}
//==============================
// ���[�V�����S�̍X�V����
//==============================
void CMotion::Update(CModel** ppModel, const int nMaxPart)
{// ���[�V�����^�C�v�̔ԍ��ŊY���̃��[�V�����X�V���邾���ɂ���

	// ���f�����i�[
	int nNumModel = nMaxPart;
	
	// ��O����
	if (nNumModel <= 0)
	{
		// �x���\��
		MessageBox(GetActiveWindow(), "���f�������݂��܂���", "�L�����N�^�[�G���[", MB_OK);

		// ���̏����ɓ���Ȃ��悤�ɂ���
		return;
	}

	// ���݃��[�V�����L�[�v�Z
	m_motiontype = Clump(m_motiontype, 0, m_nNumMotion);
	m_nNextKey = Wrap(m_nKey + 1, 0, m_aMotionInfo[m_motiontype].nNumKey - 1);

	// �Ō�̃L�[�ƃu�����h�̃L�[���v�Z
	int nLastKey = m_aMotionInfo[m_motiontype].nNumKey - 1;

	// �t���O�𐶐�
	bool isPlayer = false;
	bool isBoss = false;

	// �ő僂�f�����ŉ�
	for (int nCnt = 0; nCnt < nNumModel; nCnt++)
	{
		// ���f���̃|�C���^
		CModel* pModel = ppModel[nCnt];

		// nul�Ȃ�
		if (!pModel) continue;

		if (pModel->IsPlayer()) isPlayer = true; 	// �v���C���[���f�����ǂ�������
		if (pModel->IsBoss()) isBoss = true; 		// �{�X���f�����ǂ�������


		// �u�����h�J�n�Ȃ�
		if (m_isFirstMotion)
		{
			// �u�����h���[�V�����̍X�V
			UpdateBlend(ppModel, nCnt);
		}
		else
		{
			// ���݂̃��[�V�����X�V
			UpdateCurrentMotion(ppModel, nCnt);
		}
	}

	// �t���[���i�s����
	if (m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
	{
		// �J�E���^�[�����Z�b�g
		m_nCounterMotion = 0;

		// �L�[������������
		if (m_nKey < m_aMotionInfo[m_motiontype].nNumKey - 1)
		{
			// �L�[�����Z
			m_nKey++;
		}
		else if (m_nKey >= m_aMotionInfo[m_motiontype].nNumKey)
		{
			// �L�[�����Z�b�g
			m_nKey = 0;

			// �t���[�������Z�b�g
			m_nCounterMotion = 0;
		}
		else
		{
			// �ʏ탋�[�v
			m_nKey = Wrap(m_nKey + 1, 0, m_aMotionInfo[m_motiontype].nNumKey - 1);
		}
	}
	else
	{
		// �u�����h���J�n���Ă��Ȃ�������
		if (!m_isFirstMotion)
		{
			// �J�E���^�[�����Z
			m_nCounterMotion++;
		}

		// �S�̃t���[���J�E���g
		m_nAllFrameCount++;
	}

	// �u�����h���[�V�������n�܂�����
	if (m_isFirstMotion == true)
	{
		// �u�����h���[�V�����J�E���g���C���N�������g
		m_nCounterBlend++;
	}

	// ���[�V�����̏o�����̃u�����h���I������
	if (m_isFirstMotion == true && m_nCounterBlend >= m_nFrameBlend)
	{
		m_nFrameBlend = 0;

		// �t���O�����Ƃɖ߂�
		m_isFirstMotion = false;

		// ���[�V�������u�����h�������[�V�����ɂ���
		m_motiontype = m_motiontypeBlend;

		// �L�[�����Z�b�g
		m_nKey = 0;

		// �u�����h�����t���[������J�n
		m_nCounterMotion = 0;

		// �u�����h�t���[��������
		m_nCounterBlend = 0;
	}

	// �v���C���[�̃��[�V�������A�N�V������ ���� ���ʂ��Ă��郂�f�����v���C���[�Ȃ�
	if (isPlayer && (m_motiontype == CPlayer::PLAYERMOTION_ACTION || m_motiontype == CPlayer::PLAYERMOTION_GUARD))
	{
		// �I���t���O�𗧂Ă�
		m_isFinishMotion = true;

		// �Ō�̃L�[�Ŏ~�߂�
		m_nKey = m_aMotionInfo[m_motiontype].nNumKey - 2;

		// �t���[�����Ō�̃L�[�ɐݒ�
		m_nCounterMotion = m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame;

		// �����Ŋ֐��𔲂���
		return;
	}

	// ���n���[�V�����̏I������
	if (isPlayer && m_motiontype == CPlayer::PLAYERMOTION_LANDING)
	{
		// �Ō�̃L�[�ɒB���Ă��āA�J�E���^�[���I���t���[���𒴂��Ă�����
		if (m_nKey >= nLastKey -1&&
			m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
		{
			m_isFinishMotion = true;
		}
	}

	// �{�X�̎� ���� �Ō�̃L�[�̃t���[���ɓ��B���Ă�����
	if (isBoss)
	{
		// �Ō�̃L�[�ɒB���Ă��āA�J�E���^�[���I���t���[���𒴂��Ă�����
		if (m_nCounterMotion >= m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame)
		{
			m_isFinishMotion = true;

			m_nCounterMotion = 0;

			return;
		}
	}

	// �S�̃t���[���J�E���g�v�Z�p
	int nFrame = 0;

	// �L�[���Ƃ̃t���[���ŉ�
	for (int nCnt = 0; nCnt < m_aMotionInfo[m_motiontype].nNumKey; nCnt++)
	{
		// �S�̌v�Z�p�ɉ��Z
		nFrame += m_aMotionInfo[m_motiontype].aKeyInfo[nCnt].nFrame;
	}

	// �ő�l�����J�E���g���I�[�o�[������
	if (m_nAllFrameCount >= m_nNumAllFrame)
	{
		m_nAllFrameCount = 0;
	}

	// �S�̃t���[���v�Z
	m_nNumAllFrame = nFrame;
}
//======================================
// ���݂̃��[�V�����̍X�V�֐�
//======================================
void CMotion::UpdateCurrentMotion(CModel** ppModel, int nModelCount)
{
	// ���[�V�����f�[�^�̎擾�ϐ���錾
	const INFO& motionInfo = m_aMotionInfo[m_motiontype];
	const KEY_INFO& keyInfoNow = motionInfo.aKeyInfo[m_nKey];
	const KEY_INFO& keyInfoNext = motionInfo.aKeyInfo[m_nNextKey];

	// �C���f�b�N�X�͈̓`�F�b�N���I�[�o�[���Ă���ꍇ
	if (nModelCount >= keyInfoNow.aKey.size() || nModelCount >= keyInfoNext.aKey.size())
	{
		return; // ���̏�����ʂ��Ȃ�
	}

	// ���݂Ǝ��̃L�[�p�̕ϐ���錾����
	const KEY& NowKey = keyInfoNow.aKey[nModelCount];
	const KEY& NextKey = keyInfoNext.aKey[nModelCount];

	// �L�[��񂩂�ʒu�ƌ������Z�o
	D3DXVECTOR3 posMotion, rotMotion;

	// �p�x�ƍ��W�̍������v�Z
	posMotion.x = NextKey.fPosX - NowKey.fPosX;
	posMotion.y = NextKey.fPosY - NowKey.fPosY;
	posMotion.z = NextKey.fPosZ - NowKey.fPosZ;

	rotMotion.x = NextKey.fRotX - NowKey.fRotX;
	rotMotion.y = NextKey.fRotY - NowKey.fRotY; 
	rotMotion.z = NextKey.fRotZ - NowKey.fRotZ;

	// ���߂�l��ۑ�����ϐ���錾
	D3DXVECTOR3 Pos, Rot;

	// ��ԌW�����v�Z
	float fDis = static_cast<float>(m_nCounterMotion) / keyInfoNow.nFrame;

	// ��Ԍ��ʂ��Z�o
	Pos.x = NowKey.fPosX + posMotion.x * fDis;
	Pos.y = NowKey.fPosY + posMotion.y * fDis;
	Pos.z = NowKey.fPosZ + posMotion.z * fDis;

	Rot.x = NowKey.fRotX + rotMotion.x * fDis;
	Rot.y = NowKey.fRotY + rotMotion.y * fDis;
	Rot.z = NowKey.fRotZ + rotMotion.z * fDis;

	// ���f���̃p�[�c�ɐݒ�
	ppModel[nModelCount]->SetPos(Pos);
	ppModel[nModelCount]->SetRot(Rot);
}

//======================================
// �u�����h���[�V�����̍X�V�֐�
//======================================
void CMotion::UpdateBlend(CModel** ppModel, int nModelCount)
{
	// �u�����h�W�����v�Z
	float fBlendFrame = static_cast<float>(m_nCounterBlend) / static_cast<float>(m_nFrameBlend);
	float fRateMotion = static_cast<float>(m_nCounterMotion) / static_cast<float>(m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].nFrame);

	// ���݂̃L�[�Ǝ��̃L�[���擾
	const KEY& nowKey = m_aMotionInfo[m_motiontype].aKeyInfo[m_nKey].aKey[nModelCount];
	const KEY& nextKey = m_aMotionInfo[m_motiontype].aKeyInfo[m_nNextKey].aKey[nModelCount];

	const KEY& nowKeyBlend = m_aMotionInfo[m_motiontypeBlend].aKeyInfo[m_nKeyBlend].aKey[nModelCount];
	const KEY& nextKeyBlend = m_aMotionInfo[m_motiontypeBlend].aKeyInfo[m_nNextKeyBlend].aKey[nModelCount];

	//==========================
	// ���݃��[�V�����̕�Ԍv�Z
	//==========================
	D3DXVECTOR3 DiffRot = VECTOR3_NULL; // �p�x
	D3DXVECTOR3	CurrentRot = VECTOR3_NULL; // ���݊p�x

	// �p�x���v�Z����
	DiffRot.x = nextKey.fRotX - nowKey.fRotX;
	DiffRot.y = nextKey.fRotY - nowKey.fRotY;
	DiffRot.z = nextKey.fRotZ - nowKey.fRotZ;

	// ���݊p�x�ɓK�p
	CurrentRot.x = nowKey.fRotX + DiffRot.x * fRateMotion;
	CurrentRot.y = nowKey.fRotY + DiffRot.y * fRateMotion;
	CurrentRot.z = nowKey.fRotZ + DiffRot.z * fRateMotion;

	// ���W���v�Z
	D3DXVECTOR3 DiffPos = VECTOR3_NULL; // ���W
	D3DXVECTOR3	CurrentPos = VECTOR3_NULL; // ���ݍ��W

	// ���W�v�Z
	DiffPos.x = nextKey.fPosX - nowKey.fPosX;
	DiffPos.y = nextKey.fPosY - nowKey.fPosY;
	DiffPos.z = nextKey.fPosZ - nowKey.fPosZ;

	// ���ݍ��W�ɓK�p
	CurrentPos.x = nowKey.fPosX + DiffPos.x * fRateMotion;
	CurrentPos.y = nowKey.fPosY + DiffPos.y * fRateMotion;
	CurrentPos.z = nowKey.fPosZ + DiffPos.z * fRateMotion;

	//===============================
	// �u�����h���[�V�����̕�Ԍv�Z
	//===============================
	D3DXVECTOR3 DiffBlendRot = VECTOR3_NULL; // �p�x
	D3DXVECTOR3	BlendRot = VECTOR3_NULL;	 // �u�����h�p�x

	// �u�����h�p�x���v�Z
	DiffBlendRot.x = nextKeyBlend.fRotX - nowKeyBlend.fRotX;
	DiffBlendRot.y = nextKeyBlend.fRotY - nowKeyBlend.fRotY;
	DiffBlendRot.z = nextKeyBlend.fRotZ - nowKeyBlend.fRotZ;

	// �u�����h�̊p�x��K�p
	BlendRot.x = nowKeyBlend.fRotX + DiffBlendRot.x * fBlendFrame;
	BlendRot.y = nowKeyBlend.fRotY + DiffBlendRot.y * fBlendFrame;
	BlendRot.z = nowKeyBlend.fRotZ + DiffBlendRot.z * fBlendFrame;

	D3DXVECTOR3 DiffBlendPos = VECTOR3_NULL; // ���W
	D3DXVECTOR3	BlendPos = VECTOR3_NULL;	 // �u�����h���W

	// �u�����h���W���v�Z
	DiffBlendPos.x = nextKeyBlend.fPosX - nowKeyBlend.fPosX;
	DiffBlendPos.y = nextKeyBlend.fPosY - nowKeyBlend.fPosY;
	DiffBlendPos.z = nextKeyBlend.fPosZ - nowKeyBlend.fPosZ;

	// �u�����h�̍��W��K�p
	BlendPos.x = nowKeyBlend.fPosX + DiffBlendPos.x * fBlendFrame;
	BlendPos.y = nowKeyBlend.fPosY + DiffBlendPos.y * fBlendFrame;
	BlendPos.z = nowKeyBlend.fPosZ + DiffBlendPos.z * fBlendFrame;

	//===============================
	// ���f���̍��W,�p�x�ɓK�p
	//===============================

	// �ŏI�p�x,���W
	D3DXVECTOR3 LastRot = VECTOR3_NULL;
	D3DXVECTOR3 LastPos = VECTOR3_NULL;

	// �p�x�v�Z
	LastRot.x = CurrentRot.x + (BlendRot.x - CurrentRot.x) * fBlendFrame;
	LastRot.y = CurrentRot.y + (BlendRot.y - CurrentRot.y) * fBlendFrame;
	LastRot.z = CurrentRot.z + (BlendRot.z - CurrentRot.z) * fBlendFrame;

	// ���W�v�Z
	LastPos.x = CurrentPos.x + (BlendPos.x - CurrentPos.x) * fBlendFrame;
	LastPos.y = CurrentPos.y + (BlendPos.y - CurrentPos.y) * fBlendFrame;
	LastPos.z = CurrentPos.z + (BlendPos.z - CurrentPos.z) * fBlendFrame;

	//===============================
	// ���f���ɃZ�b�g
	//===============================
	ppModel[nModelCount]->SetPos(LastPos);
	ppModel[nModelCount]->SetRot(LastRot);
}

//======================================
// �f�o�b�O�t�H���g�֐�
//======================================
void CMotion::Debug(void)
{
	CDebugproc::Print("[���݃t���[���J�E���g] %d /  [ �ő僂�[�V�����t���[�� ] %d", m_nAllFrameCount, m_nNumAllFrame);
	CDebugproc::Draw(800, 320);

	CDebugproc::Print("[�u�����h�t���[��] %d / [�u�����h�J�E���g] %d", m_nFrameBlend,m_nCounterBlend);
	CDebugproc::Draw(800, 340);

	CDebugproc::Print("[ �L�[�� ] %d  / [ �ő�L�[��] %d ",m_nKey, m_aMotionInfo[m_motiontype].nNumKey);
	CDebugproc::Draw(800, 360);
}

//======================================
// ���f�����ǂݍ���
//======================================
int CMotion::SetModels(std::istringstream& iss,int nMaxParts)
{
	// ������ݒ�
	std::string eq;
	int nModel = 0;

	// �ǂݍ��񂾃��f������ݒ�
	iss >> eq >> nModel;

	// ��O����
	if (nModel > nMaxParts)
	{
		MessageBox(NULL, "�ő僂�f�����𒴂��Ă��܂�", "���f�����G���[", MB_OK);
		return 0;
	}

	// ���f������Ԃ�
	return nModel;
}
//======================================
// ���f���t�@�C���ǂݍ���
//======================================
void CMotion::SetModelFile(std::istringstream& iss, CModel** pModel, int nCnt)
{
	// �ǂݍ��ݗp������
	std::string eq, filename;

	// �t�@�C������ǂݍ��񂾂��̂�ݒ�
	iss >> eq >> filename;

	// ���f���̐�������
	CModel* pNewModel = CModel::Create(VECTOR3_NULL, VECTOR3_NULL, filename.c_str());

	// ���f���̃|�C���^�Ɋi�[
	pModel[nCnt] = pNewModel;
}
//======================================
// �p�[�c���Ƃ̐ݒ�
//======================================
void CMotion::SetParts(std::ifstream& file, CModel** pModel)
{
	// �ǂݍ��ݕ�����
	std::string line;

	// ���f���ԍ��Ɛe���f���̐ݒ�p�ϐ�
	int nIdx = -1, nParentIdx = -1;

	// ����p���W�Ɗp�x
	D3DXVECTOR3 pos = VECTOR3_NULL;
	D3DXVECTOR3 rot = VECTOR3_NULL;

	// �ǂݍ��݃��[�v
	while (std::getline(file, line))
	{
		std::istringstream partss(line);
		std::string cmd;
		partss >> cmd;

		// "INDEX"��ǂݎ����
		if (cmd == "INDEX")
		{
			// �C���f�b�N�X�̕ϐ��ɒl����
			std::string eq; 
			partss >> eq >> nIdx;
		}
		// "PARENT"��ǂݎ����
		else if (cmd == "PARENT")
		{
			// �e���f���ݒ�p�̕ϐ��ɒl����
			std::string eq;
			partss >> eq >> nParentIdx;

			// �C���f�b�N�X�͈͓̔��Ȃ�
			if (nIdx >= 0 && pModel[nIdx])
			{
				if (nParentIdx != -1)
				{// �e���f�������݂���
					pModel[nIdx]->SetParent(pModel[nParentIdx]);
				}
				else
				{// �e���f�������݂��Ȃ�
					pModel[nIdx]->SetParent(nullptr);
				}
			}	
		}
		// "POS"��ǂݎ����
		else if (cmd == "POS")
		{
			// �ǂݎ�������W����
			std::string eq; 
			partss >> eq >> pos.x >> pos.y >> pos.z;

			// �͈͓����`�F�b�N
			if (nIdx >= 0 && pModel[nIdx])
			{
				// ���f���̃I�t�Z�b�g���W�ɒl��ݒ�
				pModel[nIdx]->OffSetPos(pos);
			}
		}
		// "ROT"��ǂݎ����
		else if (cmd == "ROT")
		{
			std::string eq;
			std::string rest;
			partss >> eq;
			std::getline(partss, rest); // ������Ŏ擾

			// �R�����g���폜
			size_t Pos = rest.find('#');
			if (Pos != std::string::npos)
				rest = rest.substr(0, Pos);

			// �󔒂ŕ������� float �ɕϊ�
			std::istringstream iss(rest);

			iss >> rot.x >> rot.y >> rot.z;

			if (nIdx >= 0 && pModel[nIdx])
			{
				pModel[nIdx]->OffSetRot(rot);
			}
		}
		// "PARTTYPE"��ǂݎ����
		else if (cmd == "PARTTYPE")
		{
			// �ǂݎ������ނ�������
			std::string eq, partTypeStr;
			partss >> eq >> partTypeStr;

			// �C���f�b�N�X��0�ȏ� ���� ���f��������Ȃ�
			if (nIdx >= NULL && pModel[nIdx])
			{
				if (partTypeStr == "WEAPON") // ����̕���
				{ 
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_WEAPON); 
				}
				else if (partTypeStr == "RIGHTHAND") // �E��
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_RIGHT_HAND);
				}
				else if (partTypeStr == "LEFTHAND") // ����
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_LEFT_HAND);
				}
				else if (partTypeStr == "HEAD") // ��
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_HEAD);
				}
				else if (partTypeStr == "CHEST") // ��
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_CHEST);
				}
				else if (partTypeStr == "RIGHTFOOT") // ���̍b
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_RIGHT_LEG);
				}
				else if (partTypeStr == "LEFTFOOT") // ���̍b
				{
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_LEFT_LEG);
				}
				else 
				{
					// �����Ƃ�
					pModel[nIdx]->SetPartType(CModel::PARTTYPE_NONE); 
				}
			}
		}
		// "END_PARTSSET"��ǂݎ����
		else if (cmd == "END_PARTSSET")
		{
			// ������
			break;
		}
	}
}
//======================================
// �p�[�c���Ƃ̃��[�V�����ݒ�
//======================================
void CMotion::SetPartsMotion(std::ifstream& file, CMotion* pMotion, int nCntMotion)
{
	// �ǂݍ��ݗp1�s���̃o�b�t�@
	std::string line;

	// �L�[�Z�b�g���̃J�E���g�p�ϐ�
	int nCntKey = NULL;

	// ���[�V�����ݒ�̓ǂݎ�胋�[�v
	while (std::getline(file, line))
	{
		// �s�f�[�^�𕪉����ăg�[�N�������
		std::istringstream motionss(line);
		std::string token;
		motionss >> token;

		// "LOOP"��ǂݎ����
		if (token == "LOOP")
		{
			std::string eq;
			int loopFlag;
			motionss >> eq >> loopFlag;

			// "="��ǂݎ����
			if (eq == "=")
			{
				// ���[�V�������[�v�t���O��ݒ�
				pMotion->m_aMotionInfo[nCntMotion].bLoop = loopFlag;
			}
		}
		// "NUM_KEY"��ǂݎ����
		else if (token == "NUM_KEY")
		{
			// "="���
			std::string eq;
			
			// �L�[���ۑ�
			int numKeys;

			// �l���
			motionss >> eq >> numKeys;

			// nNumKey����
			pMotion->m_aMotionInfo[nCntMotion].nNumKey = numKeys;

			// ��̏����ł��̃��[�V�����̃L�[�S�̂���̏����ł킩��̂ł��̕��̃T�C�Y��ݒ�
			pMotion->m_aMotionInfo[nCntMotion].aKeyInfo.resize(numKeys);

			//	�L�[���̏���ɒB����܂�
			while (nCntKey < numKeys)
			{
				// aKeyInfo�̃T�C�Y���킩������L�[���Ƃɂ���p�[�c�̏���akey�ɃT�C�Y�Z�b�g�����Ĕ����m�ۂ��Ă�����
				pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].aKey.resize(m_nNumModels); // m_nNumModels�͍ő僂�f����

				// �L�[���̐ݒ�
				SetKey(file, pMotion, nCntMotion, nCntKey);

				// �C���N�������g���Đi�߂�
				nCntKey++;
			}
		}
		// "END_MOTIONSET"��ǂݎ����
		else if (token == "END_MOTIONSET")
		{
			nCntKey = 0;
			break;
		}
	}
}
//======================================
// ���[�V�����L�[�S�̂̐ݒ�
//======================================
void CMotion::SetKey(std::ifstream& file, CMotion* pMotion, int nCntMotion, int nCntKey)
{
	// �s�ǂݍ���
	std::string line;

	// �g�p�ϐ�
	int frame = 0;
	int posKeyIndex = 0, rotKeyIndex = 0;

	// �ǂ񂾂��t���O
	bool ReadKey = false;

	// FRAME �s�̓ǂݍ���
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string cmd, eq;
		ss >> cmd >> eq >> frame;

		// �ǂݎ���v��
		if (cmd == "FRAME" && eq == "=")
		{
			pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey].nFrame = frame;
			break;
		}
	}

	// �ǂݍ��݃��[�v
	while (std::getline(file, line))
	{
		if (line.find("END_KEYSET") != std::string::npos)
		{
			// �L�[�Z�b�g�I��
			break;
		}
		else if (line.find("KEY") != std::string::npos)
		{
			// �L����
			ReadKey = true;

			// while�p��
			continue;
		}
		else if (ReadKey)
		{
			std::istringstream ss(line);
			std::string param;
			ss >> param;

			if (param == "POS" || param == "ROT")
			{
				// �e�L�[���Ƃ̐ݒ�
				SetKeyDate(ss, param, pMotion, nCntMotion, nCntKey, posKeyIndex, rotKeyIndex);
			}
			else if (param == "END_KEY")
			{
				// �����𖳌���
				ReadKey = false;
			}
		}
	}
}
//======================================
// �L�[���Ƃ̏��ݒ�
//======================================
void CMotion::SetKeyDate(std::istringstream& ss, const std::string& param, CMotion* pMotion, int nCntMotion, int nCntKey, int& posKeyIndex, int& rotKeyIndex)
{
	// �ǂݍ��ݗp1�s���̃o�b�t�@
	std::string eq;

	// ����p�ϐ�
    D3DXVECTOR3 Vec = VECTOR3_NULL;

	// ���W����
    ss >> eq >> Vec.x >> Vec.y >> Vec.z;

	// "="��������
    if (eq != "=") return;

	// �L�[���ϐ��ɑ������
    KEY_INFO& keyInfo = pMotion->m_aMotionInfo[nCntMotion].aKeyInfo[nCntKey];

	// "POS"�ǂݎ�莞
	if (param == "POS") 
	{
		// �e���W�ɑ������
		keyInfo.aKey[posKeyIndex].fPosX = Vec.x;
		keyInfo.aKey[posKeyIndex].fPosY = Vec.y;
		keyInfo.aKey[posKeyIndex].fPosZ = Vec.z;

		// �L�[���J�E���g�����Z
		posKeyIndex++;
	}
	// "ROT"�ǂݎ�莞
	else if (param == "ROT")
	{
		// �e�p�[�c�̊p�x�ɑ��
		keyInfo.aKey[rotKeyIndex].fRotX = Vec.x;
		keyInfo.aKey[rotKeyIndex].fRotY = Vec.y;
		keyInfo.aKey[rotKeyIndex].fRotZ = Vec.z;

		// �L�[���J�E���g�����Z
		rotKeyIndex++;
	}
}
//======================================
// ���[�V�����t���[������
//======================================
bool CMotion::CheckFrame(int nStartMotion, int nEndMotion, int nMotionType)
{
	// Start��End�͈͓̔��Ȃ�
	if (m_nAllFrameCount >= nStartMotion && m_nAllFrameCount <= nEndMotion && m_motiontype == nMotionType)
		return true;

	// ����ȊO�̎�
	return false;
}
//======================================
// �p�x�̐��K��
//======================================
void CMotion::NorRot(float* pRotX, float* pRotY, float* pRotZ)
{
	// �p�x�̐��K��
	if (*pRotX > D3DX_PI)
	{
		*pRotX += -D3DX_PI * 2.0f;
	}
	else if (*pRotX < -D3DX_PI)
	{
		*pRotX += D3DX_PI * 2.0f;
	}

	if (*pRotY > D3DX_PI)
	{
		*pRotY += -D3DX_PI * 2.0f;
	}
	else if (*pRotY < -D3DX_PI)
	{
		*pRotY += D3DX_PI * 2.0f;
	}

	if (*pRotZ > D3DX_PI)
	{
		*pRotZ += -D3DX_PI * 2.0f;
	}
	else if (*pRotZ < -D3DX_PI)
	{
		*pRotZ += D3DX_PI * 2.0f;
	}
}
