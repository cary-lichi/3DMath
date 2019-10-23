#include <math.h>
#include "EulerAngles.h"
#include "Quaternion.h"
#include "MathUtil.h"
#include "Matrix4x3.h"
#include "RotationMatrix.h"

// ���ƣ�ŷ����
// �����ߣ�cary
// ������ŷ���ǻ�����������ʵķ�װ
//		�������ڱ��� heading-pitch-bankŷ����ϵͳ

const EulerAngles kEulerAnglesIdentity(0.0f, 0.0f, 0.0f);

//�任�ɡ����Ƽ���ŷ����
void EulerAngles::canonize() {
	pitch = warpPi(pitch);
	warpPitchPiOver2();
	//����Ƿ�����������
	if (fabs(pitch) > kPiOver2 - 1e-4) {
		heading += bank;
		bank = 0.0f;
	}
	else {
		bank = warpPi(bank);
	}

	heading = warpPi(heading);
}

//��pitch�任��[-pi/2-pi/2]֮��
void EulerAngles::warpPitchPiOver2() {
	if (pitch < -kPiOver2) {
		pitch = -kPi - pitch;
		heading += kPi;
		bank += kPi;
	}
	else if (pitch > kPiOver2)
	{
		pitch = kPi - pitch;
		heading += kPi;
		bank += kPi;
	}
}

//�����塪��������Ԫ����ŷ����
void EulerAngles::fromObjectToIntertialQuaternion(const Quaternion& q) {
	//����sin(pitch)
	//m23 = -sin(pitch) = 2yz - 2wx
	float sinPicth = -2.0f * (q.y * q.z - q.w * q.x);
	//����Ƿ�����������
	if (fabs(sinPicth) > 0.9999f) {
		//�����Ϸ��������·���
		pitch = kPiOver2 * sinPicth;
		//heading = atan2(-xz + wy, 1/2 - y^2 - z^2);
		heading = atan2(-double(q.x) * double(q.z) + double(q.w) * double(q.y), 0.5f - double(q.y) * double(q.y) - double(q.z) * double(q.z));
		bank = 0.0f;
	}
	else {
		pitch = asin(sinPicth);
		//heading = atan2(xz + wy, 1/2 - x^2 - y^2);
		heading = atan2(double(q.x) * double(q.z) + double(q.w) * double(q.y), 0.5f - double(q.x) * double(q.x) - double(q.y) * double(q.y));
		//bank = atan2(xy + wz, 1/2 - x^2 - z^2);
		bank = atan2(double(q.x) * double(q.y) + double(q.w) * double(q.z), 0.5f - double(q.x) * double(q.x) - double(q.z) * double(q.z));
	}
}

//�ӹ��ԡ���������Ԫ����ŷ����
void EulerAngles::fromIntertialToObjectQuaternion(const Quaternion& q) {
	//����sin(pitch)
		//m23 = -sin(pitch) = 2yz + 2wx
	float sinPicth = -2.0f * (q.y * q.z + q.w * q.x);;
	//����Ƿ�����������
	if (fabs(sinPicth) > 0.9999f) {
		//�����Ϸ��������·���
		pitch = kPiOver2 * sinPicth;
		//heading = atan2(-xz - wy, 1/2 - y^2 - z^2);
		heading = atan2(-double(q.x) * double(q.z) - double(q.w) * double(q.y), 0.5f - double(q.y) * double(q.y) - double(q.z) * double(q.z));
		bank = 0.0f;
	}
	else {
		pitch = asin(sinPicth);
		//heading = atan2(xz - wy, 1/2 - x^2 - y^2);
		heading = atan2(double(q.x) * double(q.z) - double(q.w) * double(q.y), 0.5f - double(q.x) * double(q.x) - double(q.y) * double(q.y));
		//bank = atan2(xy - wz, 1/2 - x^2 - z^2);
		bank = atan2(double(q.x) * double(q.y) - double(q.w) * double(q.z), 0.5f - double(q.x) * double(q.x) - double(q.z) * double(q.z));
	}
}

//����������Ϊ���塪������ת������
void EulerAngles::formObjectToWorldMatrix(const Matrix4x3& m) {
	float sinPitch = -m.m32;

	//����Ƿ�����������
	if (fabs(sinPitch) > 9.9999f) {
		pitch = kPiOver2 * sinPitch;
		heading = atan2(-m.m23, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sinPitch);
		heading = atan2(m.m31, m.m33);
		bank = atan2(m.m21, m.m22);
	}
}

//����������Ϊ���硪������ת������
void EulerAngles::formWorldToObjectMatrix(const Matrix4x3& m) {
	float sinPitch = -m.m23;

	//����Ƿ�����������
	if (fabs(sinPitch) > 9.9999f) {
		pitch = kPiOver2 * sinPitch;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sinPitch);
		heading = atan2(m.m31, m.m33);
		bank = atan2(m.m21, m.m22);
	}
}

//����ת����ת����ŷ����
void EulerAngles::fromRotationMatrix(const RotationMatrix& m) {
	float sinPitch = -m.m23;

	//����Ƿ�����������
	if (fabs(sinPitch) > 9.9999f) {
		pitch = kPiOver2 * sinPitch;
		heading = atan2(-m.m31, m.m11);
		bank = 0.0f;
	}
	else {
		pitch = asin(sinPitch);
		heading = atan2(m.m31, m.m33);
		bank = atan2(m.m21, m.m22);
	}
}
