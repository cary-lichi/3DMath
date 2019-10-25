#pragma once
#ifndef _ROTATIONMATRIX_N_INCLUDED
#define _ROTATIONMATRIX_N_INCLUDED

class EulerAngles;
class Quaternion;
class Vector3;

// ���ƣ���ת����
// �����ߣ�cary
// ������ʵ����һ���򵥵�3X3���󣬽�������ת
//		

class RotationMatrix
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	//��Ϊ��λ����
	void identity();

	//����ָ�����������
	//��ŷ���ǹ������
	void setup(const EulerAngles& orientation);

	//������Ԫ��������󣬸���Ԫ����������ָ������ı任
	//���ݹ��ԡ���������ת��Ԫ���������
	void formIntertialToObjectQuaternion(const Quaternion& q);
	//�������塪��������ת��Ԫ���������
	void formObjectToIntertialQuaternion(const Quaternion& q);

	//ִ����ת
	//���ԡ������������ת
	Vector3 intertialToObject(const Vector3& v)const;
	//���塪�����Ծ�����ת
	Vector3 objectToIntertial(const Vector3& v)const;

};

#endif // #ifndef _ROTATIONMATRIX_N_INCLUDED