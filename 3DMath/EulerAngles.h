#pragma once

// ���ƣ�ŷ����
// �����ߣ�cary
// ������ŷ���ǻ�����������ʵķ�װ
//		�������ڱ��� heading-pitch-bankŷ����ϵͳ

#ifndef __UELERANGLES_H_INCLUDED
#define __UELERANGLES_H_INCLUDED


class EulerAngles {
public:
	float heading;
	float pitch;
	float bank;

	EulerAngles() {}
	EulerAngles(float h, float p, float b) :heading(h), pitch(p), bank(b) {};

	//����
	void identity(){
		heading = pitch = bank = 0.0f;
	}

	//�任�ɡ����Ƽ���ŷ����
	void canonize();

	//����Ԫ��ת����ŷ����
	//�����塪��������Ԫ����ŷ����
	void fromObjectToIntertialQuaternion(const Quaternion& q);
	//�ӹ��ԡ���������Ԫ����ŷ����
	void fromIntertialToObjectQuaternion(const Quaternion& q);

	//�Ӿ���ת����ŷ����
	//ƽ�Ʋ��ֱ�ʡ�ԣ����Ҽ��������������
	//����������Ϊ���塪������ת������
	void formObjectToWorldMatrix(const Matrix4x3& m);
	//����������Ϊ���硪������ת������
	void formWorldToObjectMatrix(const Matrix4x3& m);

	//����ת����ת����ŷ����
	void fromRotationMatrix(const RotationMatrix& m);

private:
	//��pitch�任��[-pi/2-pi/2]֮��
	void warpPitchPiOver2();
};

//ȫ�ֵġ���λ��ŷ����
extern const EulerAngles kEulerAnglesIdentity;

#endif //#ifndef __UELERANGLES_H_INCLUDED
