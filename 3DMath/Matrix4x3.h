#pragma once
#ifndef __MATRIX4X3_H_INDECUDED__
#define __MATRIX4X3_H_INDECUDED__

class Vector3;
class EulerAngles;
class Quaternion;
class RotationMatrix;

enum AxisTypeEnum
{
	x,
	y,
	z
};

// ���ƣ�4X3����
// �����ߣ�cary
// ������ʵ��4X3�����ܹ�����κ�3D����任
//		

class Matrix4x3
{
public:
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;
	float tx, ty, tz;

	//��Ϊ��λ����
	void identity();

	//ֱ�ӷ���ƽ�Ʋ���
	//������ƽ�Ʋ��ֵĵ�������Ϊ��
	void zeroTranslation();
	//ƽ�Ʋ��ָ�ֵ
	void setTranslation(const Vector3& d);
	void setupTranslation(const Vector3& d);

	//����ִ�и��ռ�<����>�ֲ��ռ�任�ľ���
	void setupLocalToParent(const Vector3& pos, const EulerAngles& orient);
	void setupLocalToParent(const Vector3& pos, const RotationMatrix& orient);
	void setupParentToLocal(const Vector3& pos, const EulerAngles& orient);
	void setupParentToLocal(const Vector3& pos, const RotationMatrix& orient);

	//��������������ת�ľ���
	//axis:��ת�������
	//theta ��ת�Ļ��ȣ����ַ�����������
	//ƽ�Ʋ�������
	void setupRotate(AxisTypeEnum& axis, float theta);

	//��������������ת�ľ���
	//��ת��ͨ��ԭ�㣬��ת��Ϊ��λ����
	//theta ��ת�Ļ��ȣ����ַ�����������
	//ƽ�Ʋ�������
	//
	void setupRotate(const Vector3& axis, float theta);

	//������ת���󣬽�λ������Ԫ������
	void fromQuaternion(const Quaternion& q);

	//���������������ŵľ���
	void setupScale(const Vector3& s);

	//���������������ŵľ���
	void setuoSacleAlongAxis(const Vector3& axis, float k);

	//�����б����
	void setupShear(AxisTypeEnum axis, float s, float t);

	//����ͶӰ����ͶӰƽ���ԭ��,�Ҵ�ֱ�ڵ�λ����n
	void setupProject(const Vector3& n);

	//���췴�����
	void setupReflect(AxisTypeEnum axis, float k = 0.0f);

	//��������ƽ�淴��ľ���
	void setupReflect(const Vector3& n);
};

//�����* �����任������Ӿ��󣬳˷���˳����������ر任��˳�����
Vector3 operator* (const Vector3& p, const Matrix4x3& m);
Matrix4x3 operator* (const Matrix4x3& a, const Matrix4x3& b);


//�����*=�����ֺ�c++��׼�﷨��һ����
Vector3& operator*= (Vector3& p, const Matrix4x3& m);
Matrix4x3& operator*= (Matrix4x3& a, const Matrix4x3& b);

//����3x3���ֵ�����ʽֵ
float determinant(const Matrix4x3& m);

//����������
Matrix4x3 inverse(const Matrix4x3& m);

//��ȡ�����ƽ�Ʋ���
Vector3 getTranslation(const Matrix4x3& m);

//�Ӿ����л�ȡ��λ
//�Ӹ����󡪡��ֲ���������л�ȡ��λ
Vector3 getPositionFromParentToLocalMatrix(const Matrix4x3& m);
//�Ӿֲ��ء���������������л�ȡ��λ
Vector3 getPositionFromLocalToParentMatrix(const Matrix4x3& m);

#endif // #ifdef __MATRIX4X3_H_INDECUDED__
