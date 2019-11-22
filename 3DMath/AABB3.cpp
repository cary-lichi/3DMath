#include "AABB3.h"
#include <assert.h>
#include <stdlib.h>
#include "AABB3.h"
#include "Matrix4x3.h"
#include <Windows.h>
#include <iostream>

using namespace std;

// ���ƣ�AABB3D
// �����ߣ�cary
// ������3D�е��������α߽��AABB��

//��ȡ�˸������е�һ��
// �޶��� [000,111]
// ��0λѡ�� min.x vs. max.x
// ��1λѡ�� min.y vs. max.y
// ��2λѡ�� min.z vs. max.z
Vector3 AABB3::corner(int i)const {
	assert(i >= 0);
	assert(i <= 7);
	return Vector3(
		(i & 1) ? max.x : min.x,
		(i & 2) ? max.y : min.y,
		(i & 4) ? max.z : min.z
	);
}

//����ա����α߽��
//��ֵ��Ϊ����ֵ/��Сֵ����վ��α߽��
void AABB3::empty() {
	const float kBigNumber = 1e37f;
	min.x = min.y = min.z = +kBigNumber;
	max.x = max.y = max.z = -kBigNumber;
}

//����α߽������ӵ�
void AABB3::add(const Vector3& p) {
	if (p.x < min.x)min.x = p.x;
	if (p.y < min.y)min.y = p.y;
	if (p.z < min.z)min.z = p.y;
	if (p.x > max.x)max.x = p.x;
	if (p.y > max.y)max.y = p.y;
	if (p.z > max.z)max.z = p.y;
}

//����α߽�������AABB
void AABB3::add(const AABB3& box) {

	if (box.min.x < min.x)min.x = box.min.x;
	if (box.min.y < min.y)min.y = box.min.y;
	if (box.min.z < min.z)min.z = box.min.y;
	if (box.max.x > max.x)max.x = box.max.x;
	if (box.max.y > max.y)max.y = box.max.y;
	if (box.max.z > max.z)max.z = box.max.y;
}

//�任���α߽��,�����µ�AABB
//��õ�һ��һ�����ߴ�ö��AABB
void AABB3::setToTransFormedBox(const AABB3& box, const Matrix4x3& m)
{
	if (box.isEmpty()) {
		empty();
		return;
	}
	//ƽ��
	min = max = getTranslation(m);
	//x
	if (m.m11 > 0.0f) {
		min.x += m.m11 * box.min.x;
		max.x += m.m11 * box.max.x;
	}
	else {
		min.x += m.m11 * box.max.x;
		max.x += m.m11 * box.min.x;
	}
	if (m.m21 > 0.0f) {
		min.x += m.m21 * box.min.y;
		max.x += m.m21 * box.max.y;
	}
	else {
		min.x += m.m21 * box.max.y;
		max.x += m.m21 * box.min.y;
	}
	if (m.m31 > 0.0f) {
		min.x += m.m31 * box.min.z;
		max.x += m.m31 * box.max.z;
	}
	else {
		min.x += m.m31 * box.max.z;
		max.x += m.m31 * box.min.z;
	}

	//y
	if (m.m12 > 0.0f) {
		min.y += m.m12 * box.min.x;
		max.y += m.m12 * box.max.x;
	}
	else {
		min.y += m.m12 * box.max.x;
		max.y += m.m12 * box.min.x;
	}
	if (m.m22 > 0.0f) {
		min.y += m.m22 * box.min.y;
		max.y += m.m22 * box.max.y;
	}
	else {
		min.y += m.m22 * box.max.y;
		max.y += m.m22 * box.min.y;
	}
	if (m.m32 > 0.0f) {
		min.y += m.m32 * box.min.z;
		max.y += m.m32 * box.max.z;
	}
	else {
		min.y += m.m32 * box.max.z;
		max.y += m.m32 * box.min.z;
	}

	//z
	if (m.m13 > 0.0f) {
		min.z += m.m13 * box.min.x;
		max.z += m.m13 * box.max.x;
	}
	else {
		min.z += m.m13 * box.max.x;
		max.z += m.m13 * box.min.x;
	}
	if (m.m23 > 0.0f) {
		min.z += m.m23 * box.min.y;
		max.z += m.m23 * box.max.y;
	}
	else {
		min.z += m.m23 * box.max.y;
		max.z += m.m23 * box.min.y;
	}
	if (m.m33 > 0.0f) {
		min.z += m.m33 * box.min.z;
		max.z += m.m33 * box.max.z;
	}
	else {
		min.z += m.m33 * box.max.z;
		max.z += m.m33 * box.min.z;
	}
}

//���� true��������α߽�Ϊ��
bool AABB3::isEmpty() const
{
	return (min.x > max.x) || (min.y > max.y) || (min.z > max.z);
}

//����true��������ΰ����õ�
bool AABB3::contains(const Vector3& p) const
{
	return (p.x >= min.x) && (p.x <= max.x)
		&& (p.y >= min.y) && (p.y <= max.y)
		&& (p.z >= min.z) && (p.z <= max.z);
}

//���ؾ���߽���ϵ������
Vector3 AABB3::closestPointTo(const Vector3& p) const
{
	//��ÿһά�Ͻ�p�����򡱾��α߽��
	Vector3 r;
	//x
	if (p.x < min.x) {
		r.x = min.x;
	}
	else if (p.x > max.x) {
		r.x = max.x;
	}
	else {
		r.x = p.x;
	}

	//y
	if (p.y < min.y) {
		r.y = min.y;
	}
	else if (p.y > max.y) {
		r.y = max.y;
	}
	else {
		r.y = p.y;
	}

	//z
	if (p.z < min.z) {
		r.z = min.z;
	}
	else if (p.z > max.z) {
		r.z = max.z;
	}
	else {
		r.z = p.z;
	}
	return r;
}

//����true����������ཻ
bool AABB3::intersectsSphere(const Vector3& center, float radius) const
{
	//�ҵ����α߽��������������ĵ�
	Vector3 closestPoint = closestPointTo(center);
	//������������ĵľ����Ƿ�С�ڰ뾶
	return distanceSquared(center, closestPoint) < radius * radius;
}

//�Ͳ������ߵ��ཻ�Բ��ԣ���������򷵻�ֵ����1
	//rayOrg ������� 
	//rayDelta ���߳��Ⱥͷ���
	//returnNoamal��ѡ���ཻ��
float AABB3::rayIntersect(const Vector3& rayOrg, const Vector3 rayDelta, Vector3* returnNoamal) const
{
	//���δ�ཻ�򷵻��������
	const float kNoIntersection = 1e30f;
	//�����ھ��α߽���ڵ�����������㵽ÿ����ľ���
	bool inside = true;
	float xt, xn;
	if (rayOrg.x < min.x) {
		xt = min.x - rayOrg.x;
		if (xt > rayDelta.x) {
			return kNoIntersection;
		}
		xt /= rayDelta.x;
		inside = false;
		xn = -1.0f;
	}
	else if (rayDelta.x > max.x) {
		xt = max.x - rayDelta.x;
		if (xt < rayDelta.x) {
			return kNoIntersection;
		}
		xt /= rayDelta.x;
		inside = false;
		xn = -1.0f;
	}
	else {
		xt = -1.0f;
	}

	float yt, yn;
	if (rayOrg.y < min.y) {
		yt = min.y - rayOrg.y;
		if (yt > rayDelta.y) {
			return kNoIntersection;
		}
		yt /= rayDelta.y;
		inside = false;
		yn = -1.0f;
	}
	else if (rayDelta.y > max.y) {
		yt = max.y - rayDelta.y;
		if (yt < rayDelta.y) {
			return kNoIntersection;
		}
		yt /= rayDelta.y;
		inside = false;
		yn = -1.0f;
	}
	else {
		yt = -1.0f;
	}

	float zt, zn;
	if (rayOrg.z < min.z) {
		zt = min.z - rayOrg.z;
		if (zt > rayDelta.z) {
			return kNoIntersection;
		}
		zt /= rayDelta.z;
		inside = false;
		zn = -1.0f;
	}
	else if (rayDelta.z > max.z) {
		zt = max.z - rayDelta.z;
		if (zt < rayDelta.z) {
			return kNoIntersection;
		}
		zt /= rayDelta.z;
		inside = false;
		zn = -1.0f;
	}
	else {
		zt = -1.0f;
	}

	if (inside) {
		if (returnNoamal != NULL) {
			*returnNoamal = -rayDelta;
			returnNoamal->normalize();
		}
		return 0.0f;
	}

	//ѡ����Զ��ƽ�桪�������ཻ�ĵط�
	int which = 0;
	float t = xt;
	if (yt > t) {
		which = 1;
		t = yt;
	}
	if (zt > t) {
		which = 2;
		t = zt;
	}

	switch (which)
	{
	case 0://��yzƽ���ཻ
	{
		float y = rayOrg.y + rayDelta.y * t;
		if (y<min.y || y>max.y) {
			return kNoIntersection;
		}

		float z = rayOrg.z + rayDelta.z * t;
		if (z<min.z || z>max.z) {
			return kNoIntersection;
		}
		if (returnNoamal != NULL) {
			returnNoamal->x = xn;
			returnNoamal->y = 0.0f;
			returnNoamal->z = 0.0f;
		}
	}
	break;
	case 1://��xzƽ���ཻ
	{
		float x = rayOrg.x + rayDelta.x * t;
		if (x<min.x || x>max.x) {
			return kNoIntersection;
		}

		float z = rayOrg.z + rayDelta.z * t;
		if (z<min.z || z>max.z) {
			return kNoIntersection;
		}
		if (returnNoamal != NULL) {
			returnNoamal->x = 0.0f;
			returnNoamal->y = yn;
			returnNoamal->z = 0.0f;
		}
	}
	break;
	case 2://��xyƽ���ཻ
	{
		float x = rayOrg.x + rayDelta.x * t;
		if (x<min.x || x>max.x) {
			return kNoIntersection;
		}

		float y = rayOrg.y + rayDelta.y * t;
		if (y<min.y || y>max.y) {
			return kNoIntersection;
		}

		if (returnNoamal != NULL) {
			returnNoamal->x = 0.0f;
			returnNoamal->y = 0.0f;
			returnNoamal->z = zn;
		}
	}
	break;
	default:
		break;
	}

	return t;
}

//�жϾ��α߽���ھ��ε���һ��
//��ֹAABB��ƽ����ཻ�Լ��
//����ֵ��
// С��0  ���α߽����ȫ��ƽ��ı���
// ����0  ���α߽����ȫ��ƽ�������
// 0  ���α߽���ƽ���ཻ
int AABB3::classifyPlane(const Vector3& n, float d) const
{
	//������С��������
	float minD, maxD;
	if (n.x > 0.0f) {
		minD = n.x * min.x;
		maxD = n.x * max.x;
	}
	else {
		minD = n.x * max.x;
		maxD = n.x * min.x;
	}

	if (n.y > 0.0f) {
		minD += n.y * min.y;
		maxD += n.y * max.y;
	}
	else {
		minD += n.y * max.y;
		maxD += n.y * min.y;
	}

	if (n.z > 0.0f) {
		minD += n.z * min.z;
		maxD += n.z * max.z;
	}
	else {
		minD += n.z * max.z;
		maxD += n.z * min.z;
	}

	if (minD >= d) {
		//ǰ��
		return +1;
	}

	if (maxD <= d) {
		//����
		return -1;
	}

	//���ƽ��
	return 0;
}
//��ƽ��Ķ�̬�ཻ�Բ���
//nΪƽ��ķ���������׼��������
//planeD Ϊƽ�淽�� p*n=d �е�Dֵ
//dir AABB�ƶ��ķ���
//
//����ƽ���Ǿ�ֹ��
//���ؽ���Ĳ���ֵ�����ཻʱAABB�ƶ��ľ��룬���δ�ཻ�򷵻�һ������
//
//ֻ̽���ƽ��������ཻ
float AABB3::intersectPlane(const Vector3& n, float planeD, const Vector3& dir) const
{
	//��������Ƿ�����
	assert(fabs(n * n - 1.0f) < .01);
	assert(fabs(dir * dir - 1.0f) < .01);
	//���δ�ཻ�򷵻��������
	const float kNoIntersection = 1e30f;
	//����нǣ�ȷ������ƽ��������ƶ�
	float dot = n * dir;
	if (dot >= 0.0f) {
		return kNoIntersection;
	}
	//��鷨������������С�����ֵ��minD�ǡ�������ǰ��ġ������Dֵ
	float minD, maxD;
	if (n.x > 0.0f) {
		minD = n.x * min.x;
		maxD = n.x * max.x;
	}
	else {
		minD = n.x * max.x;
		maxD = n.x * min.x;
	}
	
	if (n.y > 0.0f) {
		minD += n.y * min.y;
		maxD += n.y * max.y;
	}
	else {
		minD += n.y * max.y;
		maxD += n.y * min.y;
	}

	if (n.z > 0.0f) {
		minD += n.z * min.z;
		maxD += n.z * max.z;
	}
	else {
		minD += n.z * max.z;
		maxD += n.z * min.z;
	}

	//����Ƿ��Ѿ�ȫ����ƽ���һ��
	if (maxD <= planeD) {
		return kNoIntersection;
	}
	//����ǰ�涨������׼���߷���
	float t = (planeD - minD) / dot;
	if (t < 0.0f) {
		//��������
		return 0.0f;
	}
	//��� ����1����δ�ܼ�ʱ����ƽ�棬��ʱ��Ҫ�����߽��м��
	return t;
}

//���AABB���ཻ�ԣ��������true�������Է����ཻ���ֵ�AABB
bool intersectAABBs(const AABB3& box1, const AABB3& box2, AABB3* boxIntersect)
{
	//�ж��Ƿ����ص�
	if (box1.min.x > box2.max.x)return false;
	if (box1.min.y > box2.max.y)return false;
	if (box1.min.z > box2.max.z)return false;
	if (box1.max.x < box2.min.x)return false;
	if (box1.max.y < box2.min.y)return false;
	if (box1.max.z < box2.min.z)return false;
	//���ص��������ص����ֵ�AABB��
	if (boxIntersect != NULL) {
		boxIntersect->min.x = max(box1.min.x, box2.min.x);
		boxIntersect->min.y = max(box1.min.y, box2.min.y);
		boxIntersect->min.z = max(box1.min.z, box2.min.z);
		boxIntersect->max.x = min(box1.max.x, box2.max.x);
		boxIntersect->max.y = min(box1.max.y, box2.max.y);
		boxIntersect->max.z = min(box1.max.z, box2.max.z);
	}

	return true;
}

//�����˶�AABB�;�ֹAABB�ཻʱ�Ĳ����㣬������ཻ�򷵻�ֵ����1
float intersectMovingAABB(const AABB3& stationaryBox, const AABB3& movingBox, const Vector3& d)
{
	//���δ�ཻ�򷵻��������
	const float kNoIntersection = 1e30f;
	//��ʼ��ʱ�����䣬�԰�����Ҫ���ǵ�ȫ��ʱ���
	float tEnter = 0.0f;
	float tLeave = 1.0f;
	//����ÿһά���ص����֣��ٽ�����ص����ֺ�ǰ����ص������ཻ
	//�����һά���ص�����Ϊ���򷵻�(�����ཻ)
	//ÿһά�϶����뵱�����ص�
	//
	//
	//x
	if (d.x == 0.0f) {
		//X�����ص�����Ϊ��
		if ((stationaryBox.min.x > movingBox.max.x) || (stationaryBox.max.x < movingBox.min.x)) {
			return kNoIntersection;
		}
	}
	else
	{
		float oneOverD = 1.0f / d.x;
		//���㿪ʼ�Ӵ��ͷ����ʱ��
		float xEnter = (stationaryBox.min.x - movingBox.max.x) * oneOverD;
		float xLeave = (stationaryBox.max.x - movingBox.min.x) * oneOverD;
		//�������
		if (xEnter > xLeave) {
			swap(xEnter, xLeave);
		}
		//��������
		if (xEnter > tEnter) {
			tEnter = xEnter;
		}
		if (xLeave < tLeave) {
			tLeave = xLeave;
		}
		//�Ƿ��¿ռ��ص�
		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}

	//y
	if (d.y == 0.0f) {
		//y�����ص�����Ϊ��
		if ((stationaryBox.min.y > movingBox.max.y) || (stationaryBox.max.y < movingBox.min.y)) {
			return kNoIntersection;
		}
	}
	else
	{
		float oneOverD = 1.0f / d.y;
		//���㿪ʼ�Ӵ��ͷ����ʱ��
		float yEnter = (stationaryBox.min.y - movingBox.max.y) * oneOverD;
		float yLeave = (stationaryBox.max.y - movingBox.min.y) * oneOverD;
		//�������
		if (yEnter > yLeave) {
			swap(yEnter, yLeave);
		}
		//��������
		if (yEnter > tEnter) {
			tEnter = yEnter;
		}
		if (yLeave < tLeave) {
			tLeave = yLeave;
		}
		//�Ƿ��¿ռ��ص�
		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}

	//z
	if (d.z == 0.0f) {
		//z�����ص�����Ϊ��
		if ((stationaryBox.min.z > movingBox.max.z) || (stationaryBox.max.z < movingBox.min.z)) {
			return kNoIntersection;
		}
	}
	else
	{
		float oneOverD = 1.0f / d.z;
		//���㿪ʼ�Ӵ��ͷ����ʱ��
		float zEnter = (stationaryBox.min.z - movingBox.max.z) * oneOverD;
		float zLeave = (stationaryBox.max.z - movingBox.min.z) * oneOverD;
		//�������
		if (zEnter > zLeave) {
			swap(zEnter, zLeave);
		}
		//��������
		if (zEnter > tEnter) {
			tEnter = zEnter;
		}
		if (zLeave < tLeave) {
			tLeave = zLeave;
		}
		//�Ƿ��¿ռ��ص�
		if (tEnter > tLeave) {
			return kNoIntersection;
		}
	}
	return tEnter;
}
