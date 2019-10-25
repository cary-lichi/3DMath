#include "RotationMatrix.h"
#include "Vector3.h"
#include "EulerAngles.h"
#include "MathUtil.h"
#include "Quaternion.h"

// ���ƣ���ת����
// �����ߣ�cary
// ������ʵ����һ���򵥵�3X3���󣬽�������ת
//		�þ�������ǹ��Ե�����ı任��
//		���Ҫִ�����嵽���Եı任��Ӧ�ó�������ת��
//
//		���Ե�����ı任��
//				     | m11 m12 m13 |
//		[ ix iy iz ] | m21 m22 m23 | = [ ox oy oz ]
//					 | m31 m32 m33 |
//		��
//		| m11 m21 m31 | | ix |	 | ox |
//		| m12 m22 m32 |	| iy | = | oy |
//		| m13 m23 m33 |	| ix |	 | oz |
//		
//		���嵽���Եı任��
//				     | m11 m21 m31 |
//		[ ox oy oz ] | m12 m22 m32 | = [ ix iy iz ]
//					 | m13 m23 m33 |
//		��
//		| m11 m12 m13 | | ox |	 | ix |
//		| m21 m22 m23 |	| oy | = | iy |
//		| m31 m32 m33 |	| ox |	 | iz |

//��Ϊ��λ����
void RotationMatrix::identity() {
	m11 = 1.0f; m12 = 0.0f; m13 = 0.0f;
	m21 = 0.0f; m22 = 1.0f; m23 = 0.0f;
	m31 = 0.0f; m32 = 0.0f; m33 = 1.0f;
}

//��ŷ���ǹ������
void RotationMatrix::setup(const EulerAngles& orientation) {
	float sinh, cosh, sinp, cosp, sinb, cosb;
	sinCos(&sinh, &cosh, orientation.heading);
	sinCos(&sinp, &cosp, orientation.pitch);
	sinCos(&sinb, &cosb, orientation.bank);

	m11 = cosh * cosb + sinh + sinp, sinb;
	m12 = -cosh * sinb + sinh * sinp * cosb;
	m13 = sinh * cosp;

	m21 = sinb * cosp;
	m22 = cosb * cosp;
	m23 = -sinp;

	m31 = -sinh * cosb + cosh * sinp * sinb;
	m32 = sinb * sinh + cosh * sinp * cosb;
	m33 = cosh * cosp;
}

//���ݹ��ԡ���������ת��Ԫ���������
void RotationMatrix::formIntertialToObjectQuaternion(const Quaternion& q) {
	float x = q.x, y = q.y, z = q.z, w = q.w;
	float xx = x * x, xy = x * y, xz = x * z;
	float yy = y * y, yz = y * z, zz = z * z;
	float wx = w * x, wy = w * y, wz = w * z;

	m11 = 1.0f - 2.0f * (yy + zz);
	m12 = 2.0f * (xy + wz);
	m13 = 2.0f * (xz - wy);

	m21 = 2.0f * (xy - wz);
	m22 = 1.0f - 2.0f * (xx + zz);
	m23 = 2.0f * (yz + wx);

	m31 = 2.0f * (xz + wy);
	m32 = 2.0f * (yz - wx);
	m33 = 1.0f - 2.0f * (xx + yy);
}

//�������塪��������ת��Ԫ���������
void RotationMatrix::formObjectToIntertialQuaternion(const Quaternion& q) {
	float x = q.x, y = q.y, z = q.z, w = q.w;
	float xx = x * x, xy = x * y, xz = x * z;
	float yy = y * y, yz = y * z, zz = z * z;
	float wx = w * x, wy = w * y, wz = w * z;

	m11 = 1.0f - 2.0f * (yy + zz);
	m12 = 2.0f * (xy - wz);
	m13 = 2.0f * (xz + wy);

	m21 = 2.0f * (xy + wz);
	m22 = 1.0f - 2.0f * (xx + zz);
	m23 = 2.0f * (yz - wx);

	m31 = 2.0f * (xz - wy);
	m32 = 2.0f * (yz + wx);
	m33 = 1.0f - 2.0f * (xx + yy);
}

//���ԡ������������ת
Vector3 RotationMatrix::intertialToObject(const Vector3& v)const {
	return Vector3(
		m11 * v.x + m21 * v.y + m31 * v.z,
		m12 * v.x + m22 * v.y + m32 * v.z,
		m13 * v.x + m23 * v.y + m33 * v.z
	);
}

//���塪�����Ծ�����ת
Vector3 RotationMatrix::objectToIntertial(const Vector3& v)const {
	return Vector3(
		m11 * v.x + m12 * v.y + m13 * v.z,
		m21 * v.x + m22 * v.y + m23 * v.z,
		m31 * v.x + m32 * v.y + m33 * v.z
	);
}

