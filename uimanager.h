//======================================
//
// UI�S�̂��Ǘ����鏈�� [ uimanager.h ]
// Author: Asuma Nishio
//
//======================================

#ifndef _UIMANAGER_H_ // ���̃}�N����`������ĂȂ�������
#define _UIMANAGER_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//****************************
// �C���N���[�h�t�@�C���錾
//****************************
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "ui.h"

//****************************
// UI�Ǘ��N���X���`
//****************************
class CUimanager
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CUimanager();
	~CUimanager();

	// �����o�֐�
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Load(const char* pFileName);

	// �Z�b�^�[
	void SetObjectUi(std::ifstream& file);

private:
	static int m_nIdxUi;				// UI�̃C���f�b�N�X�ԍ�
	static std::vector<CUi*>m_aUidata;  // UI�z��
};

#endif