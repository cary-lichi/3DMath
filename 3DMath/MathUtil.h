#pragma once

#ifndef __MATHUTIL_H_INCLUDED__
#define __MATHUTIL_H_INCLUDED__

#include <math.h>

// ���ƣ���ѧ������
// �����ߣ�cary
// ��������װһЩ��������ѧ��ʽ

// �����pi�йصĳ���

const float kPi = 3.1415926f;
const float k2Pi = kPi * 2.0f;
const float kPiOver2 = kPi / 2.0f;
const float k1OverPi = 1.0f / kPi;
const float k1Over2Pi = 1.0f / k2Pi;
// ͨ�����ʵ���2pi�������Ƕ�������[-pi,pi]
extern float warpPi(float theta);
// "��ȫ" �����Ǻ���
// ��acose(x)��ͬ�������x������Χ��������Ϊ�ӽ�����Чֵ
// ����ֵ��[0,pi]����c�����еı�׼acos()�ĺ�����ͬ
extern float safeAcos(float x);
// ����Ƕȵ�sin��coseֵ
//��ĳЩƽ̨�ϣ������Ҫ������ֵ��ͬʱ����ȷֿ������
inline void sinCos(float* returnSin, float* returnCos, float theta) {
	*returnSin = sin(theta);
	*returnCos = cos(theta);
}

#endif //#ifndef __MATHUTIL_H_INCLUDED__
