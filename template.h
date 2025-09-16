//================================
//
// �ėp�����֐� [ template.h ]
// Author : Asuma Nishio
//
//================================

#ifndef _TEMPLATE_H_ // ���̃}�N����`������ĂȂ�������
#define _TEMPLATE_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// ���O���
//*********************************
namespace TEMPLATE
{
	constexpr float VALUE_FLOAT = 2.0f;
}

//*********************************
// �͈͓��v�Z�֐�
//*********************************
template <class T>T Clump(const T t, const T min, const T max)
{
	if (t > max) return max; // ��������������ݒ�
	if (t < min) return min; // �����ȉ��Ȃ牺���ݒ�
	return t;
}

//*********************************
// ���[�v�l�v�Z�֐�
//*********************************
template <class T>T Wrap(const T t, const T min, const T max)
{
	if (t > max) return min; // �����������ŏ��l��
	if (t < min) return max; // �����ȉ��Ȃ�ő�l��
	return t;
}

//*********************************
// �p�x���K���v�Z
//*********************************
template <class T>T NormalAngle(T Angle)
{
	// �p�x�̐��K������
	if (Angle > D3DX_PI) Angle -= D3DX_PI * TEMPLATE::VALUE_FLOAT;
	if (Angle < D3DX_PI) Angle += D3DX_PI * TEMPLATE::VALUE_FLOAT;
	return Angle;
}

//*********************************
// ���`��Ԋ֐�
//*********************************
template <class T>T Lerp(const T& a, const T& b, float t)
{
	return a + (b - a) * t;
}
#endif // !_TEMPLETE_H_
