//=============================================
//
// �C�[�W���O���� [ easing.cpp ]
// Author: Asuma Nishio
//
//=============================================

//***************************
// �C���N���[�h�t�@�C���錾
//***************************
#include "easing.h"

//===============================
// �R���X�g���N�^
//===============================
CEasing::CEasing()
{

}
//===============================
// �f�X�g���N�^
//===============================
CEasing::~CEasing()
{

}

//===============================
// �Z�b�^�[
//===============================
float CEasing::SetEase(int EaseFrame, int MaxEaseFrame)
{
	// �t���[�����ő�܂ōs������~�߂�
	if (EaseFrame >= MaxEaseFrame)
	{
		EaseFrame = MaxEaseFrame;
	}

	// t�����߂�
	float t = (float)EaseFrame / (float)MaxEaseFrame;

	// t�̒l��Ԃ�
	return t;
}

//===============================
// �C�[�W���O�̊ɂ₩�ȉ���
//===============================
float CEasing::EaseInsine(float t)
{
	return 1.0f - cos((t * D3DX_PI) * 0.5f);
}
//===============================
// �C�[�W���O�̊ɂ₩�Ȍ���
//===============================
float CEasing::EaseOutsine(float t)
{
	return sin((t * D3DX_PI) * 0.5f);
}
//===================================
// �ɂ₩�ȉ���������
//===================================
float CEasing::EaseInOutSine(float t)
{
	return -(cos(D3DX_PI * t) - 1.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseInQuad(float t)
{
	return t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutQuad(float t)
{
	return 1.0f - (1.0f - t) * (1.0f - t);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuad(float t)
{
	return (float)t < 0.5f ? 2.0f * t * t : 1.0f - pow(-2.0f * t + 2.0f, 2.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseInCubic(float t)
{
	return t * t * t;
}
//===================================
// 
//===================================
float CEasing::EaseOutCubic(float t)
{
	return 1.0f - pow(1.0f - t, 3.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutCubic(float t)
{
	return (float)t < 0.5f ? 4.0f * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 3.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseBounce(float t)
{
	if (t < (1.0f / 2.75f))  // �ŏ��̃o�E���h
	{
		return 20.0f * t * t;  // �����𒲐����āA�o�E���h������
	}
	else if (t < (2.0f / 2.75f))  // 2�Ԗڂ̃o�E���h
	{
		t -= (1.5f / 2.75f);
		return 20.0f * t * t + 0.75f;  // �����𒲐����āA�o�E���h������
	}
	else if (t < (2.5f / 2.75f))  // 3�Ԗڂ̃o�E���h
	{
		t -= (2.25f / 2.75f);
		return 20.0f * t * t + 0.9375f;  // �����𒲐����āA�o�E���h������
	}
	else  // �Ō�̃o�E���h
	{
		t -= (2.625f / 2.75f);
		return 20.0f * t * t + 0.984375f;  // �����𒲐����āA�o�E���h������
	}
}

//===================================
// 
//===================================
float CEasing::EaseOutQuart(float t)
{
	return 1.0f - pow(1.0f - t, 4.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuart(float t)
{
	return t < 0.5f ? 8.0f * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 4.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseOutQuint(float t)
{
	return 1.0f - pow(1.0f - t, 5.0f);
}
//===================================
// 
//===================================
float CEasing::EaseInOutQuint(float t)
{
	return (float)t < 0.5f ? 16.0f * t * t * t * t * t : 1.0f - pow(-2.0f * t + 2.0f, 5.0f) * 0.5f;
}

//===================================
// 
//===================================
float CEasing::EaseInBack(float t)
{
	const float s = 0.70158f;  // ��������x����
	return t * t * ((s + 1.0f) * t - s);  // ���]�̓���
}
//===================================
// 
//===================================
float CEasing::EaseOutBack(float t)
{
	const float s = 0.70158f;  // ��������x����
	t -= 1.0f;
	return (t * t * ((s + 1.0f) * t + s) + 1.0f);  // ���]�̓���
}
//===================================
// 
//===================================
float CEasing::EaseInOutBack(float t)
{
	const float s = 0.70158f * 1.525f;  // ��������x�����̒���

	if (t < 0.5f)
	{
		t *= 2.0f;
		return 0.5f * (t * t * ((s + 1.0f) * t - s));  // �O���͔��]�Ɖ���
	}
	else
	{
		t = t * 2.0f - 2.0f;
		return 0.5f * (t * t * ((s + 1.0f) * t + s) + 2.0f);  // �㔼�͔��]�ƌ���
	}

}

//===================================
// 
//===================================
float CEasing::EaseInElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // �J�n���_
	}
	if (t == 1.0f)
	{
		return 1.0f;  // �I�����_
	}
	const float p = 0.3f;  // �U������
	const float s = p * 0.25f;  // �U���̋���

	return (float)(-(pow(2.0f, 10.0f* (t -= 1.0f)) * sin((t - s) * (2.0f * D3DX_PI) / p)));  // �U���̓���
}
//===================================
// 
//===================================
float CEasing::EaseOutElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // �J�n���_
	}
	if (t == 1.0f)
	{
		return 1.0f;  // �I�����_
	}

	const float p = 0.3f;  // �U������
	const float s = p * 0.25f;  // �U���̋���

	return (float)(pow(2.0f, -10.0f * t) * sin((t - s) * (2.0f * D3DX_PI) / p) + 1.0f);  // �U���̓���

}
//===================================
// 
//===================================
float CEasing::EaseInOutElastic(float t)
{
	if (t == 0.0f)
	{
		return 0.0f;  // �J�n���_
	}
	if (t == 1.0f)
	{
		return 1.0f;  // �I�����_
	}
	const float p = 0.3f * 1.5f;  // �U������
	const float s = p * 0.25f;  // �U���̋���

	if (t < 0.5f)
	{
		return (float)(-0.5f * (pow(2.0f, 20.0f * t - 10.0f) * sin((20.0f * t - 11.125f) * (2.0f * D3DX_PI) / p)));
	}

	return (float)(pow(2.0f, -20.0f * t + 10.0f) * sin((20.0f * t - 11.125f) * (2 * D3DX_PI) / p) * 0.5f + 1.0f);

}
