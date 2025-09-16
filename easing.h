//=============================================
//
// �C�[�W���O���� [ easing.h ]
// Author: Asuma Nishio
//
//=============================================

#ifndef _EASING_H_ // ���̃}�N����`������ĂȂ�������
#define _EASING_H_ // 2�d�C���N���[�h�h�~�̃}�N����`

//*********************************
// �C�[�W���O�̃N���X��`
//*********************************
class CEasing
{
public:
	// �R���X�g���N�^�E�f�X�g���N�^
	CEasing();
	~CEasing();

	// �ÓI�����o�֐�
	static float EaseInsine(float t);
	static float EaseOutsine(float t);
	static float EaseInOutSine(float t);

	static float EaseInQuad(float t);	
	static float EaseOutQuad(float t);	
	static float EaseInOutQuad(float t);

	static float EaseInCubic(float t);	
	static float EaseOutCubic(float t);	
	static float EaseInOutCubic(float t);

	static float EaseBounce(float t);

	static float EaseOutQuart(float t);
	static float EaseInOutQuart(float t);

	static float EaseOutQuint(float t);
	static float EaseInOutQuint(float t);

	static float EaseInBack(float t);
	static float EaseOutBack(float t);
	static float EaseInOutBack(float t);

	static float EaseInElastic(float t);
	static float EaseOutElastic(float t);
	static float EaseInOutElastic(float t);

	// �Z�b�^�[
	static float SetEase(int EaseFrame, int MaxEaseFrame);

private:

};

#endif