#pragma once

#ifndef __AABB3_H_INCLUDED__
#define __AABB3_H_INCLUDED__

#ifndef __VECTOR3_H_INCLUDED
#include "Vector3.h"
#endif // #ifndef __VECTOR3_H_INCLUDED

class Matrix4x3;

// ���ƣ�AABB3D
// �����ߣ�cary
// ������3D�е��������α߽��AABB��
class AABB3
{
public:
	Vector3 min;
	Vector3 max;
	Vector3 size() const { return max - min; }
	float xSize() { return max.x - min.x; }
	float ySize() { return max.y - min.y; }
	float zSize() { return max.z - min.z; }
	Vector3 center() const { return (min + max) * .5f; }
	//��ȡ�˸������е�һ��
	Vector3 corner(int i)const;
	//���α߽�����
	//����ա����α߽��
	void empty();
	//����α߽������ӵ�
	void add(const Vector3& p);
	//����α߽�������AABB
	void add(const AABB3 &box);
	//�任���α߽��,�����µ�AABB
	void setToTransFormedBox(const AABB3& box, const Matrix4x3& m);
	//����/�ཻ�Բ���
	//���� true��������α߽�Ϊ��
	bool isEmpty() const;
	//����true��������ΰ����õ�
	bool contains(const Vector3& p) const;
	//���ؾ���߽���ϵ������
	Vector3 closestPointTo(const Vector3& p)const;
	//����true����������ཻ
	bool intersectsSphere(const Vector3& center, float radius)const;
	//�Ͳ������ߵ��ཻ�Բ��ԣ���������򷵻�ֵ����1
	//rayOrg ������� 
	//rayDelta ���߳��Ⱥͷ���
	//returnNoamal��ѡ���ཻ��
	float rayIntersect(const Vector3& rayOrg, const Vector3 rayDelta, Vector3* returnNoamal = 0)const;
	//�жϾ��α߽���ھ��ε���һ��
	//��ֹAABB��ƽ����ཻ�Լ��
	//����ֵ��
	// С��0  ���α߽����ȫ��ƽ��ı���
	// ����0  ���α߽����ȫ��ƽ�������
	// 0  ���α߽���ƽ���ཻ
	int classifyPlane(const Vector3& n, float d)const;
	//��ƽ��Ķ�̬�ཻ�Բ���
	//nΪƽ��ķ���������׼��������
	//planeD Ϊƽ�淽�� p*n=d �е�Dֵ
	//dir AABB�ƶ��ķ���
	//
	//����ƽ���Ǿ�ֹ��
	//���ؽ���Ĳ���ֵ�����ཻʱAABB�ƶ��ľ��룬���δ�ཻ�򷵻�һ������
	//
	//ֻ̽���ƽ��������ཻ
	// ����ֵ ��� ����1����δ�ܼ�ʱ����ƽ�棬��ʱ��Ҫ�����߽��м��
	float intersectPlane(const Vector3& n, float planeD, const Vector3& dir)const;

};

//���AABB���ཻ�ԣ��������true�������Է����ཻ���ֵ�AABB
bool intersectAABBs(const AABB3& box1, const AABB3& box2, AABB3* boxIntersect = 0);

//�����˶�AABB�;�ֹAABB�ཻʱ�Ĳ����㣬������ཻ�򷵻�ֵ����1
float intersectMovingAABB(const AABB3& stationaryBox, const AABB3& movingBox, const Vector3& d);

#endif // #ifndef __AABB3_H_INCLUDED__