#include<math.h>
#include "MathUtil.h"
#include "Vector3.h"

// ���ƣ���ѧ������
// �����ߣ�cary
// ��������װһЩ��������ѧ��ʽ

const Vector3 kZeroVector(0.0f, 0.0f, 0.0f);

// ͨ�����ʵ���2pi�������Ƕ�������[-pi,pi]
float warpPi(float theta) {
	theta += kPi;
	theta -= floor(theta * k1Over2Pi) * k2Pi;
	theta -= kPi;
	return theta;
}

// "��ȫ" �����Ǻ���
// ��acose(x)��ͬ�������x������Χ��������Ϊ�ӽ�����Чֵ
// ����ֵ��[0,pi]����c�����еı�׼acos()�ĺ�����ͬ
extern float safeAcos(float x) {
	if (x <= -1.0f) {
		return kPi;
	}
	if (x >= 1.0f) {
		return 0.0f;
	}
	//ʹ�ñ�׼C����
	return acos(x);
}
