#pragma once
#include "Vector3.h"
#include "EulerAngles.h"
#ifndef __QUATERNION_H_INCLUDEED__
#define __QUATERNION_H_INCLUDEED__


// ���ƣ���Ԫ��
// �����ߣ�cary
// ������ʵ����3D�б�ʾ��λ�Ƶ���Ԫ��
//		

class Quaternion
{
public:
	float x, y, z, w;

	//��Ϊ��Ԫ��Ԫ��
	void identity(){
		w = x = y = z = 0.0f;
	}

	void setQuaternionAboutX(float theta);
	void setQuaternionAboutY(float theta);
	void setQutaernionAboutZ(float theta);
	void setQutaernionAboutAxis(const Vector3& axis, float theta);

	//��ŷ���Ǽ������塪�����Ե���Ԫ��
	void setToRotationObjectToInertial(const EulerAngles& orientation);
	//��ŷ���Ǽ�����ԡ����������Ԫ��
	void setToRotationInertialToObject(const EulerAngles& orientation);

	//����* ʵ�ֲ��
	Quaternion operator *(const Quaternion& a) const;
	//����*= ʵ�ֲ�˲���ֵ
	Quaternion& operator *=(const Quaternion& a);

	//����
	void normalize();

	//��ת��
	float getRotationAngle() const;
	//��
	Vector3 getRotaionAxis() const;
};

//ȫ�֡���λ����Ԫ��
extern const Quaternion kQuaternionIdentity;

//��Ԫ�����
extern float dotProduct(const Quaternion& a, const Quaternion& b);

//�������Բ�ֵ
extern Quaternion slerp(const Quaternion& q0, const Quaternion& q1, float t);

//��Ԫ������
extern Quaternion conjugate(const Quaternion& q);

//��Ԫ����
extern Quaternion pow(const Quaternion& q, float exponent);

#endif // #ifndef __QUATERNION_H_INCLUDEED__