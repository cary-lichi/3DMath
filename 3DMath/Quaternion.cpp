#include<math.h>
#include<assert.h>

#include "Quaternion.h"
#include "MathUtil.h"
#include "EulerAngles.h"
#include "Vector3.h"


// ���ƣ���Ԫ��
// �����ߣ�cary
// ������ʵ����3D�б�ʾ��λ�Ƶ���Ԫ��
//	

//ȫ�֡���λ����Ԫ��
const Quaternion kQuaternionIdentity = {
	1.0f,0.0f,0.0f,0.0f
};


void Quaternion::setQuaternionAboutX(float theta) {
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = sin(thetaOver2);
	y = 0.0f;
	z = 0.0f;
}

void Quaternion::setQuaternionAboutY(float theta) {
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = 0.0f;
	y = sin(thetaOver2);
	z = 0.0f;
}

void Quaternion::setQutaernionAboutZ(float theta) {
	float thetaOver2 = theta * 0.5f;
	w = cos(thetaOver2);
	x = 0.0f;
	y = 0.0f;
	z = sin(thetaOver2);
}

void Quaternion::setQutaernionAboutAxis(const Vector3& axis, float theta) {
	//��ת������׼��
	assert(fabs(vectorMag(axis) - 1.0f) < 0.01f);
	float thetaOver2 = theta * 0.5f;
	float sinThetaOver2 = sin(thetaOver2);

	w = cos(thetaOver2);
	x = axis.x * sinThetaOver2;
	y = axis.y * sinThetaOver2;
	z = axis.z * sinThetaOver2;
}

//��ŷ���Ǽ������塪�����Ե���Ԫ��
void Quaternion::setToRotationObjectToInertial(const EulerAngles& orientation) {
	float sinPitch, sinBank, sinHeading;
	float cosPitch, cosBank, cosHeading;
	sinCos(&sinPitch, &cosPitch, orientation.pitch * 0.5f);
	sinCos(&sinBank, &cosBank, orientation.bank * 0.5f);
	sinCos(&sinHeading, &cosHeading, orientation.heading * 0.5f);

	w = cosHeading * cosPitch * cosBank + sinHeading * sinPitch * sinBank;
	x = cosHeading * sinPitch * cosBank + sinHeading * cosPitch * sinBank;
	y = -cosHeading * sinPitch * sinBank + sinHeading * cosPitch * cosBank;
	z = -sinHeading * sinPitch * cosBank + cosHeading * cosPitch * sinBank;
}

//��ŷ���Ǽ�����ԡ����������Ԫ��
void Quaternion::setToRotationInertialToObject(const EulerAngles& orientation) {
	float sinPitch, sinBank, sinHeading;
	float cosPitch, cosBank, cosHeading;
	sinCos(&sinPitch, &cosPitch, orientation.pitch * 0.5f);
	sinCos(&sinBank, &cosBank, orientation.bank * 0.5f);
	sinCos(&sinHeading, &cosHeading, orientation.heading * 0.5f);

	w = cosHeading * cosPitch * cosBank + sinHeading * sinPitch * sinBank;
	x = -cosHeading * sinPitch * cosBank - sinHeading * cosPitch * sinBank;
	y = cosHeading * sinPitch * sinBank - sinHeading * cosPitch * cosBank;
	z = sinHeading * sinPitch * cosBank - cosHeading * cosPitch * sinBank;
}

//����* ʵ�ֲ��
Quaternion Quaternion::operator *(const Quaternion& a)const {
	Quaternion result;

	result.w = w * a.w - x * a.x - y * a.y - z * a.z;
	result.x = w * a.w + x * a.x - y * a.y - z * a.z;
	result.y = w * a.w + x * a.x + y * a.y - z * a.z;
	result.z = w * a.w - x * a.x + y * a.y + z * a.z;

	return result;
}

//����*= ʵ�ֲ�˲���ֵ
Quaternion& Quaternion::operator *=(const Quaternion& a) {
	*this = *this * a;
	return *this;
}

//����
//�ṩ���������Ҫ��Ϊ�˷�ֹ����������������Ԫ���������ܵ����������
void Quaternion::normalize() {
	float mag = (float)sqrt(double(w) * double(w) + double(x) * double(x) + double(y) * double(y) + double(z) * double(z));
	if (mag > 0.0f) {
		float oneOverMag = mag / 1.0f;
		w *= oneOverMag;
		x *= oneOverMag;
		y *= oneOverMag;
		z *= oneOverMag;
	}
	else {
		assert(false);
		identity();
	}
}

//��ת��
float Quaternion::getRotationAngle() const {
	//������ w = cos(theta / 2);
	float thetaOver2 = safeAcos(w);
	return thetaOver2 * 2.0f;
}
//��
Vector3 Quaternion::getRotaionAxis() const {
	//����sin^2(theta / 2)
	//w = cos(theta / 2);
	//sin^2(x) + cos^2(x) = 1
	float sinThetaOver2Sq = 1.0f - w * w;
	//ע�Ᵽ֤��ֵ����
	if (sinThetaOver2Sq <= 0.0f) {
		//��λ��Ԫ���򲻻���ȷ����ֵ��ֻҪ������Ч����������
		return Vector3(1.0f, 0.0f, 0.0f);
	}

	//����1 / sin(theta / 2);
	float oneOverSinThetaOver2 = 1.0f / sqrt(sinThetaOver2Sq);

	return Vector3(
		x * oneOverSinThetaOver2,
		y * oneOverSinThetaOver2,
		z * oneOverSinThetaOver2
	);
}

//��Ԫ�����
//�÷ǳ�Ա����ʵ����Ԫ������Ա����ڱ��ʽ��ʹ��ʱ���֡������﷨��
extern float dotProduct(const Quaternion& a, const Quaternion& b) {
	return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

//�������Բ�ֵ
extern Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t) {
	if (t <= 0.0f) {
		return q0;
	}
	if (t >= 1.0f) {
		return q1;
	}
	//�õ�˼�����Ԫ���нǵ�COSֵ
	float cosOmega = dotProduct(q0, q1);

	//������Ϊ����ʹ��-q1
	//��Ԫ��q1,-q1������ͬ����ת�������ܲ�����ͬ��slerp���㣬����ѡ����ȷ��һ���Ա�ʹ����ǽ�����ת
	float q1w = q1.w;
	float q1x = q1.x;
	float q1y = q1.y;
	float q1z = q1.z;
	if (cosOmega < 0.0f) {
		q1w = -q1w;
		q1x = -q1x;
		q1y = -q1y;
		q1z = -q1z;
		cosOmega = -cosOmega;
	}
	//������λ����Ԫ������˽��Ӧ�� С�ڵ���1
	assert(cosOmega < 1.1f);
	//�����ֵƬ
	float k0, k1;
	if (cosOmega > 0.9999f) {
		//�ǳ��ӽ��������Բ�ֵ����ֹ����
		k0 = 1.0f - t;
		k1 = t;
	}
	else {
		//����sinֵ
		//sin^2(omega) + cos^2(omega)=  1
		float sinOmega = sqrt(1.0f - double(cosOmega) * (double(cosOmega)));
		float omega = atan2(sinOmega, cosOmega);
		float oneOverOmega = 1.0f / omega;

		//�����ֵ����
		k0 = sin(double(1.0 - double(t)) * double(omega)) * oneOverOmega;
		k1 = sin(double(t) * double(omega)) * oneOverOmega;
	}
	Quaternion result;
	result.w = k0 * q0.w + k1 * q1w;
	result.x = k0 * q0.x + k1 * q1x;
	result.y = k0 * q0.y + k1 * q1y;
	result.z = k0 * q0.z + k1 * q1z;
	return result;
}

//��Ԫ������
//��ԭ��Ԫ����ת�����෴����Ԫ��
extern Quaternion conjugate(const Quaternion& q) {
	Quaternion result;
	result.w = q.w;
	result.x = -q.x;
	result.y = -q.y;
	result.z = -q.z;
	return result;
}

//��Ԫ������
extern Quaternion pow(const Quaternion& q, float exponent) {
	// ��ֹ����
	if (fabs(q.w) > 9.9999f) {
		return q;
	}
	float alpha = acos(q.w);
	float newAlpha = alpha * exponent;
	Quaternion result;
	result.w = cos(newAlpha);
	float mult = sin(newAlpha) / sin(alpha);
	result.x = q.x * mult;
	result.y = q.y * mult;
	result.z = q.z * mult;
	return result;
}
